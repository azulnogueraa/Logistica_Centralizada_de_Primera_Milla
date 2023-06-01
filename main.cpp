#include <iostream>
#include <fstream>
#include <vector>

#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "taxi_assignment_batching_solver.h"
#include "taxi_batching_modificado.h"
#include "ortools/graph/min_cost_flow.h"

int main(int argc, char** argv) {

    // Ejercicio 4:
    // Creemos un csv vacio...
    std::ofstream archivo("resultados.csv");

    // Escribamos los nombres de columna en el archivo
    archivo << "Nombre" << "," << "Tamaño de Muestra" << "," << "Función Objetivo Greedy" << "," << "Función Objetivo Batching" << "," << "Tiempo Greedy" << "," << "Tiempo Batching" << "," << "%Gap (Función Objetivo)" << "," << "%Gap (Tiempo de Resolución)" << std::endl;


    //vector con cada instancia a leer...
    std::vector<std::string> size_n =
    {"small_0", "small_1", "small_2", "small_3", "small_4", "small_5", "small_6", "small_7", "small_8", "small_9",  
    "medium_0", "medium_1", "medium_2", "medium_3", "medium_4", "medium_5", "medium_6", "medium_7", "medium_8", "medium_9",  
    "large_0", "large_1", "large_2", "large_3", "large_4", "large_5", "large_6", "large_7", "large_8", "large_9", 
    "xl_0", "xl_1", "xl_2", "xl_3", "xl_4", "xl_5", "xl_6", "xl_7", "xl_8", "xl_9"};

    //iteramos en cada size_n para sistematizar la obtención de resultados...
    for(int i = 0 ; i < size_n.size() ; i++){

        //completamos el path a cada archivo de instancia...
        std:: string filename = "input/" + size_n[i] + ".csv";

        TaxiAssignmentInstance instance(filename);
        std::cout << filename << std::endl;

        //Greedy Solver//
        GreedySolver g_solver(instance);
        g_solver.solve();

        double g_objective_value = g_solver.getObjectiveValue();

        double g_solution_time = g_solver.getSolutionTime();

        //Batching Solver//
        BatchingSolver b_solver(instance);
        b_solver.solve();

        double b_objective_value = b_solver.getObjectiveValue();

        double b_solution_time = b_solver.getSolutionTime();


        //Mejora relativa (%Gap) de Función Objetivo //
        double gap_ov = (g_objective_value - b_objective_value) / b_objective_value;

        //Mejora relativa (%Gap) de Tiempo de Resolución //
        double gap_t = (g_solution_time - b_solution_time) / b_solution_time;

        archivo << filename << "," << instance.n << "," << g_objective_value << "," << b_objective_value << "," << g_solution_time << "," << b_solution_time << "," << gap_ov << "," << gap_t << std::endl;

    }

    //Ejercicio 7:
    std::ofstream archivo2("resultados_nuevos.csv");

    // Escribamos los nombres de columna en el archivo
    archivo2 << "Nombre" << "," << "Función Objetivo Greedy" << "," << "Función Objetivo Taxi Batching" << "," << "Función Objetivo Batching Modificado" << "," << "Ratio Distancia Greedy" << "," << "Ratio Distancia Taxi Batching" << "," << "Ratio Distancia Batching Modificado" << std::endl;

    //iteramos en cada size_n para sistematizar la obtención de resultados...
    for(int i = 0 ; i < size_n.size() ; i++){

        //completamos el path a cada archivo de instancia...
        std:: string filename = "input/" + size_n[i] + ".csv";

        TaxiAssignmentInstance instance(filename);
        std::cout << filename << std::endl;

        //Greedy Solver//
        GreedySolver g_solver(instance);
        g_solver.solve();

        TaxiAssignmentSolution g_solution = g_solver.getSolution();
        double g_objective_value = g_solver.getObjectiveValue();

        // Ratio de distancia de Greedy:
        double g_dist_ratio_total = 0;
        int n_g = instance.n;
        double g_dist_ratio;
        for(int t = 0; t < instance.n; t++){
            int p_assigned = g_solution.getAssignedPax(t); 
            
            /*
            En los casos de que la distancia del viaje sea cero, decidimos filtrarlo y saturarlo en cero.
            Por esa razón, disminuimos la n para no contar este caso en el promedio. 
            */
            if(instance.pax_trip_dist[p_assigned] == 0){
                g_dist_ratio = 0;
                n_g = n_g - 1;
            }
            else{
                g_dist_ratio = ( instance.dist[t][p_assigned] / ( instance.pax_trip_dist[p_assigned])) * 100;            
            }


            //Suma de promedio total de ratios por instancia:
            // Promedio de Ratios por instancia:
            g_dist_ratio_total += g_dist_ratio;
        }

         double g_dist_ratio_promedio = g_dist_ratio_total / n_g;

        
        //Batching Solver//
        BatchingSolver b_solver(instance);
        b_solver.solve();

        TaxiAssignmentSolution b_solution = b_solver.getSolution();
        double b_objective_value = b_solver.getObjectiveValue();

        // Ratio de distancia de Batching:
        double b_dist_ratio_total = 0;
        int n_b = instance.n;
        double b_dist_ratio;
        for(int t = 0; t < instance.n; t++){
            int p_assigned = b_solution.getAssignedPax(t); 
            
            /*
            En los casos de que la distancia del viaje sea cero, decidimos filtrarlo y saturarlo en cero.
            Por esa razón, disminuimos la n para no contar este caso en el promedio. 
            */
            if(instance.pax_trip_dist[p_assigned] == 0){
                b_dist_ratio = 0;
                n_b = n_b - 1;
            }
            else{
                b_dist_ratio = ( instance.dist[t][p_assigned] / ( instance.pax_trip_dist[p_assigned])) * 100;            
            }


            //Suma de promedio total de ratios por instancia:
            // Promedio de Ratios por instancia:
            b_dist_ratio_total += b_dist_ratio;
        }

         double b_dist_ratio_promedio = b_dist_ratio_total / n_b;


        //Batching Solver Modificado//
        BatchingSolverModificado bm_solver(instance);
        bm_solver.solve();

        TaxiAssignmentSolution bm_solution = bm_solver.getSolution();
        double bm_objetive_value = bm_solver.getObjectiveValue();

        // Ratio de distancia de Batching Modificado:
        double bm_dist_ratio_total = 0;
        int n_bm = instance.n;
        double bm_dist_ratio;
        for(int t = 0; t < instance.n; t++){
            int p_assigned = bm_solution.getAssignedPax(t); 
            
            /*
            En los casos de que la distancia del viaje sea cero, decidimos filtrarlo y saturarlo en cero.
            Por esa razón, disminuimos la n para no contar este caso en el promedio. 
            */
            if(instance.pax_trip_dist[p_assigned] == 0){
                bm_dist_ratio = 0;
                n_bm = n_bm - 1;
            }
            else{
                bm_dist_ratio = ( instance.dist[t][p_assigned] / ( instance.pax_trip_dist[p_assigned])) * 100;            
            }

            //Suma de promedio total de ratios por instancia:
            // Promedio de Ratios por instancia:
            bm_dist_ratio_total += bm_dist_ratio;
        }

         double bm_dist_ratio_promedio = bm_dist_ratio_total / n_bm;




        archivo2 << filename << ","  << g_objective_value  << "," <<  b_objective_value  << ","  <<  bm_objetive_value << ","  << g_dist_ratio_promedio << "," << b_dist_ratio_promedio << "," << bm_dist_ratio_promedio << std::endl;

    }

    return 0;
    
}
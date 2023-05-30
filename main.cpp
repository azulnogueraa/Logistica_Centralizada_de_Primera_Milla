#include <iostream>
#include <fstream>
#include <vector>

#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "min_cost_flow_solver.h"
#include "taxi_assignment_batching_solver.h"
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

    return 0;
    
}
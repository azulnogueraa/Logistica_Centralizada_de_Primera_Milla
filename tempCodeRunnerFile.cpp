#include <iostream>
#include <fstream>
#include <vector>

#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"
#include "min_cost_flow_solver.h"
#include "taxi_assignment_batching_solver.h"

int main() {

    // Ejercicio 4:
    // Creemos un csv vacio...
    std::ofstream archivo("resultados.csv");

    // Escribamos los nombres de columna en el archivo
    archivo << "Nombre" << "," << "Tamaño de Muestra" << "," << "Greedy" << "," << "Batching" << "," << "%Gap" << std::endl;

    //vector de tamaños de muestra
    std::vector<std::string> muestra_size = {"small", "medium", "large", "xl"};

    //iteramos en los tamaños de las instancias...
    for(int s = 0; s <= muestra_size.size() ; s++){

        //primera parte de la instancia...
        std::string instancia = "input/" + muestra_size[s];

        //iteramos en las instancias de cada tamaño...
        for(int a == 0 ; a <= 9 ; a++){
            //segunda parte de la instancia...
            std::string filename = archivo + "_" + std::to_string(a) + ".csv";

            TaxiAssignmentInstance instance(filename);
            std::cout << filename << std::endl;

            //Greedy Solver//
            GreedySolver g_solver(instance);
            g_solver.solve();

            double g_objective_value = g_solver.getObjectiveValue();

            //Batching Solver//
            BatchingSolver b_solver(instance);
            b_solver.solve();

            double b_objective_value = b_solver.getObjectiveValue();

            //Mejora relativa (%Gap) //
            double gap = (g_objective_value - b_objective_value) / b_objective_value;

            archivo << filename << "," << instance.n << "," << g_objective_value << "," << b_objective_value << "," << gap << std::endl;
        }
    }

    // Cerramos el archivo
    archivo.close();

    return 0;
}
#include "greedy_solver.h"
#include "taxi_assignment_solution.h"
using namespace std;


GreedySolver::GreedySolver() {}

GreedySolver::GreedySolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void GreedySolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void GreedySolver::solve() {

    //inicializamos el cronometro que contara el tiempo de resolución Greedy...
    auto start = chrono::steady_clock::now();


    for (int p = 0; p < this->_instance.n; p++){

        //taxi con menor distancia a p
        int min_taxi = -1;

        //buscamos cualquier taxi sin asignar dentro de los restantes para cada pasajero y se lo asignamos temporalmente a min_taxi...
        while(min_taxi == -1){

            for(int t = 0; t < this->_instance.n; t++){

                //verificamos que el taxi no haya sido asignado a ningun otro pasajero...
                if(this->_solution.isTaxiAssigned(t) == false){
                    min_taxi = t;
                }
            }

        }

        double min_dist = this->_instance.dist[min_taxi][p];
        
        for (int t = 0; t < this->_instance.n ; t++){

            //si la distancia de un taxi al pasajero p es menor a min_dist y el taxi no esta asignado, cambiamos las variables...
            if ((this->_instance.dist[t][p] < min_dist) && (!this->_solution.isTaxiAssigned(t))){
                min_dist = this->_instance.dist[t][p];
                min_taxi = t;
            }

        }

        //guardamos para cada pasajero el taxi mas cercado (FCFS)...
        this->_solution.assign(min_taxi,p);

        //el valor objetivo equivale a la suma de las distancias recorridas por cada taxi hasta su pasajero asignado...
        this->_objective_value += this->_instance.dist[min_taxi][p];

    }

    //terminamos el cronometro...
    auto end = chrono::steady_clock::now();

    //tiempo de resolución equivale a: end - start
    chrono::duration<double, std::milli> duration = end - start;
    this->_solution_time = duration.count();

    //bibliografia de chrono: https://openwebinars.net/blog/como-usar-la-libreria-chrono-en-c/

}

double GreedySolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution GreedySolver::getSolution() const {
    return this->_solution;
}

int GreedySolver::getSolutionStatus() const {
    return this->_solution_status;
}

double GreedySolver::getSolutionTime() const {
    return this->_solution_time;
}


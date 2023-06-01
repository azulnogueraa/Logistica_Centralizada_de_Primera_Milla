#include "greedy_solver.h"
#include "taxi_assignment_solution.h"
#include <chrono>
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

    //inicializamos la solución a partir del n de la instancia del TaxiAssignmentSolution...
    this->_solution = TaxiAssignmentSolution(this->_instance.n);

    for (int p = 0; p < this->_instance.n; p++){

        //taxi con menor distancia a p
        int min_taxi = -1;

        //buscamos cualquier taxi sin asignar dentro de los restantes para cada pasajero y se lo asignamos temporalmente a min_taxi...
        for(int t = 0; t < this->_instance.n; t++){

            //verificamos que el taxi no haya sido asignado a ningun otro pasajero...
            if( min_taxi == -1 && this->_solution.isTaxiAssigned(t) == false ){
                min_taxi = t;
                break;
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

    //libreria de chrono: https://openwebinars.net/blog/como-usar-la-libreria-chrono-en-c/

    //Calculamos el distance ratio...
    double dist_viaje = 0;
    double dist_busqueda = 0;
    
    for( int t = 0; t < this->_instance.n; t++) {

        int pax_assigned = this->_solution.getAssignedPax(t);

        // if(this->_instance.pax_trip_dist)
        dist_busqueda += this->_instance.dist[t][pax_assigned];
        dist_viaje += this->_instance.pax_trip_dist[pax_assigned];    

    }
    
    this->_distance_ratio = (dist_busqueda / dist_viaje);

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

double GreedySolver::getDistanceRatio() const {
    return this->_distance_ratio;
}


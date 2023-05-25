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

    //auto solucion = TaxiAssignmentSolution(n);
    for (int p = 0; p < this->_instance.n; p++){
        
        int min_taxi = -1;

        //buscamos el primer taxi sin asignar dentro de los restantes para cada pasajero...
        while(min_taxi == -1){
            for(int t = 0; t < this->_instance.n; t++){
                if(this->_solution.isTaxiAssigned(t) == false){
                    min_taxi = t;
                }
            }
        }



        // double min = this->_instance.dist[0][p];
        
        // for (int t = 0; t < this->_instance.n ; t++){
        //     if ((this->_instance.dist[t][p] < min) && (!this->_solution.isTaxiAssigned(t))){
        //         min = this->_instance.dist[t][p];
        //         min_taxi = t;
        //     }
        // }
        // this->_solution.assign(min_taxi,p);
    }
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


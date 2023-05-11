#include "greedy_solver.h"
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
    for(int pasajero=0; pasajero<_instance.n; pasajero++){
        min_temp = _instance.dist[pasajero][0];
        for(int d=0; d<_instance.n; d++){
            if(_instance.dist[pasajero][d] < min_temp){
                min_temp = _instance.dist[pasajero][d];
            }
            
        }
    }

}

// min(c, k){
//     return min(c[0],min(c.pop, k-1) )
// }

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



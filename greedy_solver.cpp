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

    for(int taxi = 0 ; taxi < _instance.n ; taxi++){
        double min_temp = _instance.dist[0][0];
        int pax_min = 0;
        for(int pasajero=1 ; pasajero < _instance.n; pasajero++){
            if(_instance.dist[taxi][pasajero] < min_temp && !TaxiAssignmentSolution::isPaxAssigned(pasajero)){
                min_temp = _instance.dist[taxi][pasajero];
                pax_min = pasajero;
            }
        }
        TaxiAssignmentSolution::assign(taxi, pax_min);

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



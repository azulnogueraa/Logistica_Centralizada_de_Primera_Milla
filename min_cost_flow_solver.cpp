#include "min_cost_flow_solver.h"


MinCostFlowSolver::MinCostFlowSolver() {}

MinCostFlowSolver::MinCostFlowSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void MinCostFlowSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void MinCostFlowSolver::solve() {

    // Create the min cost network flow instance.
    this->_createMinCostFlowNetwork();

    // Obtain the solve the problem.
    int status = this->_min_cost_flow.Solve();

    // Obtain the solution, construct the corresponding object and record de desired parameters.
    if (status == operations_research::MinCostFlow::OPTIMAL) {
        std::cout << "Minimum cost flow: " << this->_min_cost_flow.OptimalCost() << std::endl;
        std::cout << "";
        std::cout << " Arc   Flow / Capacity  Cost" << std::endl;
        for (std::size_t i = 0; i < this->_min_cost_flow.NumArcs(); ++i) {
            int64_t flow = this->_min_cost_flow.Flow(i);
            if (flow == 0) continue;
            int64_t cost = this->_min_cost_flow.Flow(i) * this->_min_cost_flow.UnitCost(i);
            std::cout << this->_min_cost_flow.Tail(i) << " -> " << this->_min_cost_flow.Head(i)
                        << "  " << this->_min_cost_flow.Flow(i) << "  / "
                        << this->_min_cost_flow.Capacity(i) << "       " << cost << std::endl;
        }
    } else {
        std::cout << "Solving the min cost flow problem failed. Solver status: "
                << status << std::endl;
    }
}

double MinCostFlowSolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution MinCostFlowSolver::getSolution() const {
    return this->_solution;
}

int MinCostFlowSolver::getSolutionStatus() const {
    return this->_solution_status;
}

double MinCostFlowSolver::getSolutionTime() const {
    return this->_solution_time;
}

// Private methods

void MinCostFlowSolver::_createMinCostFlowNetwork() {

    // Initialize graph structures.
    int n = this->_instance.n;
    std::vector<int64_t> start_nodes(n*n, -1);
    std::vector<int64_t> end_nodes(n*n, -1);
    std::vector<int64_t> capacities(n*n, 1);
    std::vector<int64_t> unit_costs(n*n, -1);

    // Complete the graph structures. 
    // Origin vertices (taxis) indexed from 0...n-1. 
    // Destination vertices (paxs) indexed from n...2n-1
    // unit_cost of (i,j) = dist[i][j]
    int cnt = 0;
    for (int i = 0; i < this->_instance.n; i++) {
        for (int j = this->_instance.n; j < 2*this->_instance.n; j++) {
            // capacities are always 1, defined when initialized.
            start_nodes[cnt] = i;
            end_nodes[cnt] = j;
            unit_costs[cnt] = 10*this->_instance.dist[i][j - n];
            cnt++;
        }
    }

    // Create the supplies.
    // supplies[i] = 1 for taxis, i = 0,...,n-1.
    // supplies[i] = -1 for paxs, i = n,...,2n-1.
    std::vector<int64_t> supplies(2*n, 0);
    for (int i = 0; i < this->_instance.n; i++) {
        supplies[i] = 1;
        supplies[n + i] = -1;
    }

    // Create the digraph
    // Add each arc.
    for (int i = 0; i < start_nodes.size(); ++i) {
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(start_nodes[i], end_nodes[i], capacities[i], unit_costs[i]);
        if (arc != i) LOG(FATAL) << "Internal error";
    }

    // Add node supplies.
    for (int i = 0; i < supplies.size(); ++i) {
        this->_min_cost_flow.SetNodeSupply(i, supplies[i]);
    }

    for (int i = 0; i < n*n; i++) {
        std::cout << unit_costs[i] << " ";
    }
    std::cout << std::endl;
}

void MinCostFlowSolver::_createSolutionInfo() {

}



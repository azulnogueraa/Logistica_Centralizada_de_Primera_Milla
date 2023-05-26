#include "taxi_assignment_batching_solver.h"


BatchingSolver::BatchingSolver() {}

BatchingSolver::BatchingSolver(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
    this->_objective_value = 0;
    this->_solution_status = 0;
    this->_solution_time = 0;
}

void BatchingSolver::setInstance(TaxiAssignmentInstance &instance) {
    this->_instance = instance;
}

void BatchingSolver::solve() {

    //Inicializamos el cronómetro que contará el tiempo de resolución usando batching...
    auto start = chrono::steady_clock::now();
    
    // Create the min cost network flow instance.
    this->_createMinCostFlowNetwork();

    // Guardar el problema resuelto en _solution_status
    this->_solution_status = this->_min_cost_flow.Solve();

     // Obtain the solution, construct the corresponding object and record de desired parameters.
    if (status == operations_research::MinCostFlow::OPTIMAL) {
        
        for (size_t i = 0; i < this->_min_cost_flow.NumArcs(); ++i) {
            int64_t flow = this->_min_cost_flow.Flow(i);

            if (flow == 0) continue;

            int64_t cost = flow * this->_min_cost_flow.UnitCost(i);

            //Obtenemos para el taxi i el pasajero i.
            int t = this->_min_cost_flow.Tail(i);
            
            //Como para todo nodo i no existe un nodo j igual a i, los pasajeros estan inicializados con valores de n+1 a 2n. Para mantener la estructura de nuestro modelo, le restamos n a los nodos p. 
            int p = this->_min_cost_flow.Head(i) - this->_instance.n;

            //Agregamos la arista t->p a la solución.
            this->_solution.assign(t,p);

            //El valor objetivo equivale a la suma de los costos de las aristas t->p.
            this->_objective_value += this->_min_cost_flow.UniCost(i);

        }
    } else {
        std::cout << "Solving the min cost flow problem failed. Solver status: "
                << this->_solution_status << std::endl;
    }

    //Terminamos el cronómetro...
    auto end = chrono::steady_clock::now();

    //Tiempo de resolución equivale a: end - start
    chrono::duration<double, std::milli> duration = end - start;
    this->_solution_time = duration.count();

    //Bibliografia de chrono: https://openwebinars.net/blog/como-usar-la-libreria-chrono-en-c/

}

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

double BatchingSolver::getObjectiveValue() const {
    return this->_objective_value;
}

TaxiAssignmentSolution BatchingSolver::getSolution() const {
    return this->_solution;
}

int BatchingSolver::getSolutionStatus() const {
    return this->_solution_status;
}

double BatchingSolver::getSolutionTime() const {
    return this->_solution_time;
}



#include "taxi_assignment_batching_solver.h"


using namespace std;

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

    //Guardamos la solución en _solution...
    this->_solution = TaxiAssignmentSolution(this->_instance.n);
    
    //Se crea la red de flujo minimo de _instance...
    this->_createMinCostFlowNetwork();

    // Guardar el status en _solution_status
    this->_solution_status = this->_min_cost_flow.Solve();

     // Obtain the solution, construct the corresponding object and record de desired parameters.
    if (_solution_status == operations_research::MinCostFlow::OPTIMAL) {
        
        for (size_t i = 0; i < this->_min_cost_flow.NumArcs(); ++i) {
            int64_t flow = this->_min_cost_flow.Flow(i);

            if (flow == 0) continue;

            int64_t cost = flow * this->_min_cost_flow.UnitCost(i);

            //Obtenemos el taxi de la arista i...
            int t = this->_min_cost_flow.Tail(i);

            /*
            Como el solucionador del flujo de costo mínimo requiere que todos los nodos del grafo esten numerados de forma distintiva, 
             los nodos de los pasajeros estan inicializados con valores de n a 2n-1. Para mantener la estructura de nuestro modelo, 
             le restamos n a los nodos p.
            */

            //Obtenemos el pasajero de la  arista i...
            int p = this->_min_cost_flow.Head(i) - this->_instance.n;
            

            //Agregamos la arista t->p a la solución.
            this->_solution.assign(t,p);

        }
        
        //El valor objetivo equivale a la suma de los costos de las aristas t->p.
        //dividimos por diez para que queden los números originales.
        this->_objective_value = this->_min_cost_flow.OptimalCost() / 10.0;

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

// a continuación se crea el grafo modelado en el ejercicio 2
void BatchingSolver::_createMinCostFlowNetwork() {

    // Inicializamos las estructuras del grafo...
    int n = this->_instance.n;
    std::vector<int64_t> start_nodes(n*n, -1);
    std::vector<int64_t> end_nodes(n*n, -1);
    std::vector<int64_t> capacities(n*n, 1);
    std::vector<int64_t> unit_costs(n*n, -1);

    /*
    Completamos las estructuras del grafo. 
    - Los vertices que representan los taxis se indexan de 0 a n-1.
    - Los vertices que representan a los pasajeros se indexan de n a 2n-1.
    - Los costos de las aristas t->p son 10 * dist[t][p]
    */

    int cnt = 0;
    for (int i = 0; i < this->_instance.n; i++) {
        for (int j = this->_instance.n; j < 2*this->_instance.n; j++) {
            // Las capacidades son todas 1, definidas al inicializar.
            start_nodes[cnt] = i;
            end_nodes[cnt] = j;

            unit_costs[cnt] = 10 * this->_instance.dist[i][j - n];
            cnt++;
        }
    }

    // Creamos las supplies...
    // supplies[i] = 1 para taxis, i = 0,...,n-1.
    // supplies[i] = -1 para paxs, i = n,...,2n-1.
    std::vector<int64_t> supplies(2*n, 0);
    for (int i = 0; i < this->_instance.n; i++) {
        supplies[i] = 1;
        supplies[n + i] = -1;
    }

    // Crea el digrafo añadiendo cada arista...
    for (int i = 0; i < start_nodes.size(); ++i) {
        int arc = this->_min_cost_flow.AddArcWithCapacityAndUnitCost(start_nodes[i], end_nodes[i], capacities[i], unit_costs[i]);
        if (arc != i) LOG(FATAL) << "Internal error";
    }

    // Agregamos los supplies de cada nodo.
    for (int i = 0; i < supplies.size(); ++i) {
        this->_min_cost_flow.SetNodeSupply(i, supplies[i]);
    }

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


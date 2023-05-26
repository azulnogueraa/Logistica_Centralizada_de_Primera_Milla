#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "checker.h"
#include "greedy_solver.h"


int main(int argc, char** argv) {
    std::string filename = "input/small_1.csv";

    TaxiAssignmentInstance instance(filename);
    std::cout << filename << std::endl;

    TaxiAssignmentSolution solution(instance.n);


    //Greedy:

    GreedySolver solver(instance);

    solver.solve();

    std::cout << "val_obj_g: " << solver.getObjectiveValue() << std::endl;

    //Batching:

    BatchingSolver solver(instance);

    BatchingSolver.solve();

    std::cout << "val_obj_b: " << solver.getObjectiveValue() << std::endl;


    return 0;
}
#ifndef TAXI_ASSIGNMENT_MIN_COST_FLOW_SOLVER_H
#define TAXI_ASSIGNMENT_MIN_COST_FLOW_SOLVER_H

#include <cstdint>
#include <vector>
#include <iostream>
#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"
#include "ortools/graph/min_cost_flow.h"


class MinCostFlowSolver
{
	public:
        MinCostFlowSolver();
        MinCostFlowSolver(TaxiAssignmentInstance &instance);

        void setInstance(TaxiAssignmentInstance &instance);
        void solve();

        double getObjectiveValue() const;
        TaxiAssignmentSolution getSolution() const;
        int getSolutionStatus() const;
        double getSolutionTime() const;
        
        
	
	private:
        // Solver atributes.
        operations_research::SimpleMinCostFlow _min_cost_flow;
        
        void _createMinCostFlowNetwork();
        void _createSolutionInfo();

        // Instance, problem and results attributes
        TaxiAssignmentInstance _instance;
        TaxiAssignmentSolution _solution;
        double _objective_value;
        int _solution_status;
        double _solution_time;

};

#endif
#ifndef TAXI_ASSIGNMENT_CHECKER_H
#define TAXI_ASSIGNMENT_CHECKER_H

#include<vector>
#include<iostream>
#include "taxi_assignment_instance.h"
#include "taxi_assignment_solution.h"

enum FeasibilityConstraint {VALUES_IN_RANGE, PAX_UNIQUE, TAXI_UNIQUE};

class TaxiAssignmentChecker
{
	public:
        TaxiAssignmentChecker();

        bool checkFeasibility(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution);
        void getFeasibilityStatus();
        bool getSolutionCost(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution);
  

	
	private:
        int n_constraints = 3;
        std::vector<bool> _feasibility_status;

        bool _checkValuesInRange(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution);
        bool _checkPaxUnique(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution);
        bool _checkTaxiUnique(const TaxiAssignmentInstance &instance, const TaxiAssignmentSolution &solution);
};

#endif
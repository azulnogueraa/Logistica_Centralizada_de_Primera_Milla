#ifndef TAXI_ASSIGNMENT_SOLUTION_H
#define TAXI_ASSIGNMENT_SOLUTION_H

#include<vector>
#include<iostream>

class TaxiAssignmentSolution
{
	public:
        TaxiAssignmentSolution();
        TaxiAssignmentSolution(int n);

        int getN() const;
        void assign(int taxi, int pax);
        bool isTaxiAssigned(int taxi) const;
        bool isPaxAssigned(int pax) const;
        int getAssignedPax(int taxi) const;
        int getAssignedTaxi(int pax) const;

        friend std::ostream& operator<<(std::ostream& os, const TaxiAssignmentSolution& solution);

	
	private:
        int _n;
        std::vector<int> _taxi_assignment;
        std::vector<int> _pax_assignment;
};

#endif
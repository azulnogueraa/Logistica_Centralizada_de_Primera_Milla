#ifndef TAXI_ASSIGNMENT_INSTANCE_H
#define TAXI_ASSIGNMENT_INSTANCE_H

#include<vector>
#include<tuple>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

class TaxiAssignmentInstance
{
	public:
        TaxiAssignmentInstance();
        TaxiAssignmentInstance(std::string filename);
        void ReadFromFile(std::string filename);
        
        // number of taxis / passengers
        int n;
        // latlong information about taxis. Only relevant for visualization.
        std::vector<std::pair<double,double> > taxi_position;
        // latlong information about passengers. Only relevant for visualization.
        std::vector<std::pair<double,double> > pax_position;
        // vector with the distances of the trips. pax_trip_dist[i] contains the information
        // about the distance to be traveled by passenger i after being picked by a taxi.
        std::vector<double> pax_trip_dist;
        // vector with the fare estimations fir the passenger trips. 
        // pax_tot_fare[i] contains an estimation of the fare to be charger to the passenger i 
        // after being picked by a taxi.       
        std::vector<double> pax_tot_fare;
        // n x n distance matrix. dist[i][j] contains the distance that taxi i must travel to
        // pickup passenger j.
        std::vector<std::vector<double> > dist; 
	
	private:

};

#endif
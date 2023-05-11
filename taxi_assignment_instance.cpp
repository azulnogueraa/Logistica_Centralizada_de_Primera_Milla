#include "taxi_assignment_instance.h"

void split(std::string &str, char &delim, std::vector<std::string> &out) {
            // create a stream from the string  
            std::stringstream s(str);  
              
            std::string s2;  
            while (std::getline(s, s2, delim) )  
            {  
                out.push_back(s2); // store the string in s2  
            } 
}

TaxiAssignmentInstance::TaxiAssignmentInstance() {}

TaxiAssignmentInstance::TaxiAssignmentInstance(std::string filename) {

    this->ReadFromFile(filename);
}

void TaxiAssignmentInstance::ReadFromFile(std::string filename) {
    std::ifstream input_file(filename);

    // Read the number of taxis / passengers.
    input_file >> this->n;
    this->taxi_position = std::vector<std::pair<double, double> >(this->n);
    this->pax_position = std::vector<std::pair<double, double> >(this->n);
    this->pax_trip_dist = std::vector<double>(this->n);
    this->pax_tot_fare = std::vector<double>(this->n);
    this->dist = std::vector< std::vector<double> >(this->n, std::vector<double>(this->n));


    //Read taxis position.
    char delim = ',';
    for (int i = 0; i < this->n; i++) {
        std::string line;
        input_file >> line;
        std::vector<std::string> elems;
        split(line, delim, elems);

        // Assign the latlong
        this->taxi_position[i] = std::make_pair<double, double>(std::stod(elems[0]), std::stod(elems[1]));
        //std::cout << this->taxi_position[i].first << " " << this->taxi_position[i].second << std::endl;
    }

    // Read passenger information.
    for (int i = 0; i < this->n; i++) {
        std::string line;
        input_file >> line;
        std::vector<std::string> elems;
        split(line, delim, elems);
        this->pax_position[i] = std::make_pair<double, double>(std::stod(elems[0]), std::stod(elems[1]));
        this->pax_trip_dist[i] = std::stod(elems[2]);
        this->pax_tot_fare[i] = std::stod(elems[3]);
    }

    for (int i = 0; i < this->n; i++) {
        std::string line;
        input_file >> line;
        std::vector<std::string> elems;
        split(line, delim, elems);

        for (int j = 0; j < this->n; j++) {
            this->dist[i][j] = std::stod(elems[j]);
        }
    }
}
#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>
#include <vector>

struct Airport{
    string city;
    string name;
    string country;
    double longitude;
    double latitude;
    int id;
    vector<int> destinations;

    Airport(){
        this->city = "";
        this->name = "";
        this->country = "";
        this->longitude = 0.0;
        this->latitude = 0.0;
        this->id = 0;
    }
    ~Airport(){}

    void insertData(int idx, string data){
        switch (idx){
        case 0:
            this->city = data;
            break;
        
        case 1:
            this->name = data;
            break;
        
        case 2:
            this->country = data;
            break;
        
        case 3:
            this->longitude = stod(data);
            break;
        
        case 4:
            this->latitude = stod(data);
            break;
        
        case 5:
            this->id = stoi(data);
            break;
        
        case 6:
            this->destinations.push_back(stoi(data));
            break;

        default:
            break;
        }
    }
};


#endif
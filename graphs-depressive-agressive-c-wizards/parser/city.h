#ifndef CITY_H
#define CITY_H

#include <string>
#include <vector>

struct City{
    string city;
    double longitude;
    double latitude;
    int id;
    vector<int> destinations;

    City(){
        this->city = "";
        this->longitude = 0.0;
        this->latitude = 0.0;
        this->id = 0;
    }
    ~City(){}

    void insertData(int idx, string data){
        switch (idx){
        case 0:
            this->city = data;
            break;
        
        case 1:
            this->longitude = stod(data);
            break;
        
        case 2:
            this->latitude = stod(data);
            break;
        case 3:
            this->id = stoi(data);
            break;
        case 4:
            this->destinations.push_back(stoi(data));
            break;
        default:
            break;
        }
    }
};

#endif
#ifndef AIRPORTS_PARSER_H
#define AIRPORTS_PARSER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

#include "parser.h"
#include "airport.h"
#include "../undirected.h"
#include "../directed.h"

#define pi 3.14159265358979323846

class AirportsParser : public Parser
{
public:
private:
    unordered_map<int, Airport *> airports;

    float toRad(float degree)
    {
        return degree / 180 * pi;
    }

    float calculateDistance(float lat1, float long1, float lat2, float long2)
    {
        float dist;
        dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
        dist = acos(dist);
        dist = 6371 * dist;
        return dist;
    }

public:
    AirportsParser() {}
    ~AirportsParser()
    {
        for (auto it = this->airports.begin(); it != this->airports.end(); ++it)
        {
            delete it->second;
        }
    }

    unordered_map<int, float> calculateHeuristics(int destination)
    {
        unordered_map<int, float> heuristics;
        Airport *destAirport = this->airports[destination];
        float destLatitude = destAirport->latitude;
        float destLongitude = destAirport->longitude;
        float inLatitude;
        float inLongitude;
        for (auto itr = this->airports.begin(); itr != this->airports.end(); itr++)
        {
            inLatitude = itr->second->latitude;
            inLongitude = itr->second->longitude;
            float dist = calculateDistance(inLatitude, inLongitude, destLatitude, destLongitude);
            heuristics[itr->second->id] = dist;
        }
        return heuristics;
    }

    void clear() override
    {
        for (auto it = this->airports.begin(); it != this->airports.end(); ++it)
        {
            delete it->second;
        }
        this->airports.clear();
    }

    void readJSON()
    {
        if (!this->airports.empty())
        {
            this->clear();
        }
        string line;
        fstream file("./JSONs/airports.json");
        stringstream ss;
        string temp, dataStr;
        int stringSize;
        int count;
        if (!file.is_open())
        {
            throw "Could not read file";
        }
        while (file.is_open())
        {
            getline(file, line);
            ss << line;
            ss >> dataStr;
            ss.clear();
            if (dataStr[0] == ']')
            {
                break;
            }
            if (dataStr[0] == '{')
            {
                count = 0;
                Airport *airport = new Airport();
                while (true)
                {
                    getline(file, line);
                    ss << line;
                    ss >> dataStr;
                    if (dataStr[0] == '}')
                    {
                        break;
                    }
                    // Insert parsed data into struct
                    if (count < 6)
                    { // Insert any attribute except for destinations
                        ss >> dataStr;
                        // if any name is composed of 2 or more words
                        while (!ss.eof())
                        { // Concatenate the name
                            ss >> temp;
                            dataStr = dataStr + " " + temp;
                        }
                        stringSize = dataStr.size();
                        dataStr = dataStr.substr(1, stringSize - 3); // Remove the ',' and '"' charcaters
                        airport->insertData(count, dataStr);
                        count++;
                    }
                    else
                    { // Insert destinations
                        while (true)
                        {
                            // clear stringstream
                            ss.str("");
                            ss.clear();
                            getline(file, line);
                            ss << line;
                            ss >> dataStr;
                            if (dataStr[0] == ']')
                            {
                                break;
                            }
                            stringSize = dataStr.size();
                            if (dataStr[stringSize - 1] == ',')
                            {
                                dataStr = dataStr.substr(1, stringSize - 3);
                            }
                            else
                            {
                                dataStr = dataStr.substr(1, stringSize - 2);
                            }
                            airport->insertData(count, dataStr);
                        }
                    }
                    // clear stringstream
                    ss.str("");
                    ss.clear();
                }
                // clear stringstream
                ss.str("");
                ss.clear();
                this->airports[airport->id] = airport;
            }
        }
        file.close();
    }

    void uGraphMake(UndirectedGraph<string, double> &tempGraph) override
    {
        if (this->airports.empty())
        {
            throw "JSON must be read first";
        }
        for (auto itr = this->airports.begin(); itr != this->airports.end(); itr++)
        {
            double latitudeStart = itr->second->latitude;
            double longitudeStart = itr->second->longitude;
            int idStart = itr->second->id;
            tempGraph.insertVertex(idStart, itr->second->city + ", " + itr->second->name + ", " + itr->second->country);
            for (auto itr2 = itr->second->destinations.begin(); itr2 != itr->second->destinations.end(); itr2++)
            {
                int idEnd = *itr2;
                string dataEnd = this->airports[idEnd]->city + ", " + this->airports[idEnd]->name + ", " + this->airports[idEnd]->country;
                double latitudeEnd = this->airports[idEnd]->latitude;
                double longitudeEnd = this->airports[idEnd]->longitude;
                tempGraph.insertVertex(idEnd, dataEnd);
                tempGraph.createEdge(idStart, idEnd, calculateDistance(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd));
                if (std::find(this->airports[idEnd]->destinations.begin(), this->airports[idEnd]->destinations.end(), idStart) != this->airports[idEnd]->destinations.end())
                {
                    std::remove(this->airports[idEnd]->destinations.begin(), this->airports[idEnd]->destinations.end(), idStart);
                }
            }
        }
    }

    void dGraphMake(DirectedGraph<string, double> &tempGraph) override
    {
        if (this->airports.empty())
        {
            throw "JSON must be read first";
        }
        for (auto itr = this->airports.begin(); itr != this->airports.end(); ++itr)
        {
            Airport *airport = itr->second;
            double latitudeStart = airport->latitude;
            double longitudeStart = airport->longitude;
            int idStart = airport->id;
            tempGraph.insertVertex(idStart, airport->city + ", " + airport->name + ", " + airport->country);
            for (auto itr2 = airport->destinations.begin(); itr2 != airport->destinations.end(); ++itr2)
            {
                int destination = *itr2;
                int idEnd = destination;
                string dataEnd = this->airports[idEnd]->city + ", " + this->airports[idEnd]->name + ", " + this->airports[idEnd]->country;
                double latitudeEnd = this->airports[idEnd]->latitude;
                double longitudeEnd = this->airports[idEnd]->longitude;
                tempGraph.insertVertex(idEnd, dataEnd);
                tempGraph.createEdge(idStart, idEnd, calculateDistance(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd));
            }
        }
    }
};

#endif
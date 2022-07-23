#ifndef CITIES_PARSER_H
#define CITIES_PARSER_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "parser.h"
#include "city.h"

#define pi 3.14159265358979323846

class CitiesParser : public Parser
{
private:
    unordered_map<int, City *> cities;

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
    CitiesParser() {}
    ~CitiesParser()
    {
        for (auto it = this->cities.begin(); it != this->cities.end(); ++it)
        {
            delete it->second;
        }
    }

    unordered_map<int, float> calculateHeuristics(int destination)
    {
        unordered_map<int, float> heuristics;
        City *destCity = this->cities[destination];
        float destLatitude = destCity->latitude;
        float destLongitude = destCity->longitude;
        float inLatitude;
        float inLongitude;
        for (auto itr = this->cities.begin(); itr != this->cities.end(); itr++)
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
        for (auto it = this->cities.begin(); it != this->cities.end(); ++it)
        {
            delete it->second;
        }
        this->cities.clear();
    }

    void readJSON()
    {
        if (!this->cities.empty())
        {
            this->clear();
        }
        string line;
        fstream file("./JSONs/pe.json");
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
                City *city = new City();
                while (true)
                {
                    getline(file, line);
                    ss << line;
                    ss >> dataStr;
                    if (dataStr[0] == '}')
                    {
                        break;
                    }
                    if (count < 4)
                    {
                        ss >> dataStr;
                        // if any name is composed of 2 or more words
                        while (!ss.eof())
                        { // Concatenate the name
                            ss >> temp;
                            dataStr = dataStr + " " + temp;
                        }
                        stringSize = dataStr.size();
                        dataStr = dataStr.substr(1, stringSize - 3); // Remove the ',' and '"' charcaters
                        city->insertData(count, dataStr);
                        count++;
                    }
                    else
                    {
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
                            city->insertData(count, dataStr);
                        }
                    }
                    // clear stringstream
                    ss.str("");
                    ss.clear();
                }
                // clear stringstream
                ss.str("");
                ss.clear();
                this->cities[city->id] = city;
            }
        }
        file.close();
    }

    void uGraphMake(UndirectedGraph<string, double> &tempGraph) override
    {
        if (this->cities.empty())
        {
            throw "JSON must be read first";
        }
        for (auto itr = this->cities.begin(); itr != this->cities.end(); itr++)
        {
            double latitudeStart = itr->second->latitude;
            double longitudeStart = itr->second->longitude;
            int idStart = itr->second->id;
            tempGraph.insertVertex(idStart, itr->second->city);
            for (auto itr2 = itr->second->destinations.begin(); itr2 != itr->second->destinations.end(); itr2++)
            {
                int idEnd = *itr2;
                string dataEnd = this->cities[idEnd]->city;
                double latitudeEnd = this->cities[idEnd]->latitude;
                double longitudeEnd = this->cities[idEnd]->longitude;
                tempGraph.insertVertex(idEnd, dataEnd);
                tempGraph.createEdge(idStart, idEnd, calculateDistance(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd));
                if (std::find(this->cities[idEnd]->destinations.begin(), this->cities[idEnd]->destinations.end(), idStart) != this->cities[idEnd]->destinations.end())
                {
                    std::remove(this->cities[idEnd]->destinations.begin(), this->cities[idEnd]->destinations.end(), idStart);
                }
            }
        }
    }

    void dGraphMake(DirectedGraph<string, double> &tempGraph) override
    {
        if (this->cities.empty())
        {
            throw "JSON must be read first";
        }
        for (auto itr = this->cities.begin(); itr != this->cities.end(); itr++)
        {
            double latitudeStart = itr->second->latitude;
            double longitudeStart = itr->second->longitude;
            int idStart = itr->second->id;
            tempGraph.insertVertex(idStart, itr->second->city);
            for (auto itr2 = itr->second->destinations.begin(); itr2 != itr->second->destinations.end(); itr2++)
            {
                int idEnd = *itr2;
                string dataEnd = this->cities[idEnd]->city;
                double latitudeEnd = this->cities[idEnd]->latitude;
                double longitudeEnd = this->cities[idEnd]->longitude;
                tempGraph.insertVertex(idEnd, dataEnd);
                tempGraph.createEdge(idStart, idEnd, calculateDistance(latitudeStart, longitudeStart, latitudeEnd, longitudeEnd));
            }
        }
    }
};

#endif
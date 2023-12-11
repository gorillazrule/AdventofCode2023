// Day5_part1.cpp :


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <queue>

#include "relationshipMap.h"
#include "seedInfo.h"

using std::ifstream;
using std::string;
using std::vector;
using std::stringstream;
using std::priority_queue;

void getMap(string file, vector<relationshipMap>& map);
long long convert(vector<relationshipMap>& map, long long id);

int main()
{
    bool test = false;
    string prefix = "";
    if (test)
    {
        prefix = "J:\\VS Projects\\AdventofCode2023\\Day5_part1\\Tests\\";
    }
    //Start by loading all the relationship Maps
    vector<relationshipMap> seedToSoil;
    vector<relationshipMap> soilToFertilizer;
    vector<relationshipMap> fertilizerToWater;
    vector<relationshipMap> waterToLight;
    vector<relationshipMap> lightToTemperature;
    vector<relationshipMap> temperatureToHumidity;
    vector<relationshipMap> humidityToLocation;
    getMap(prefix + "seed-to-soil.txt", seedToSoil);
    getMap(prefix + "soil-to-fertilizer.txt", soilToFertilizer);
    getMap(prefix + "fertilizer-to-water.txt", fertilizerToWater);
    getMap(prefix + "water-to-light.txt", waterToLight);
    getMap(prefix + "light-to-temperature.txt", lightToTemperature);
    getMap(prefix + "temperature-to-humidity.txt", temperatureToHumidity);
    getMap(prefix + "humidity-to-location.txt", humidityToLocation);

    //Read through the seed list, and use it to propagate all information about each seed as it is read
    //and insert into priority queue

    priority_queue<seedInfo, vector<seedInfo>, std::greater<seedInfo>> almanac;

    ifstream infile;
    infile.open(prefix + "seeds.txt");
    string seed;
    while (infile >> seed)
    {
        long long id = stoll(seed);
        seedInfo entry;
        entry.seed = id;

        long long soil = convert(seedToSoil, id);
        entry.soil = soil;

        long long fertilizer = convert(soilToFertilizer, soil);
        entry.fertilizer = fertilizer;

        long long water = convert(fertilizerToWater, fertilizer);
        entry.water = water;

        long long light = convert(waterToLight, water);
        entry.light = light;

        long long temperature = convert(lightToTemperature, light);
        entry.temperature = temperature;

        long long humidity = convert(temperatureToHumidity, temperature);
        entry.humidity = humidity;

        long long location = convert(humidityToLocation, humidity);
        entry.location = location;

        almanac.push(entry);
    }
    

    std::cout << almanac.top().location;
}

void getMap(string file, vector<relationshipMap>& map)
{
    ifstream infile;
    infile.open(file);

    string line;
    while (getline(infile, line))
    {
        stringstream input(line);
        string destination;
        string source;
        string range;
        input >> destination;
        input >> source;
        input >> range;
        relationshipMap relations;
        relations.destination = stoll(destination);
        relations.source = stoll (source);
        relations.range = stoll(range);
        map.push_back(relations);
    }
    infile.close();
}

long long convert(vector<relationshipMap>& map, long long source)
{
    long long destination = -1;
    for (int i = 0; i < map.size(); ++i)
    {
        long long check = map.at(i).checkRange(source);
        if (check >= 0)
        {
            return check;
        }
    }

    if (destination == -1)
    {
        destination = source;
    }

    return destination;
}

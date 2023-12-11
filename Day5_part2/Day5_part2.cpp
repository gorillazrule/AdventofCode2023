// Day5_part2.cpp :

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <climits>
#include <algorithm>

#include "relationshipMap.h"

using std::ifstream;
using std::string;
using std::vector;
using std::stringstream;
using std::sort;

struct idRange
{
    long long start;
    long long end;
};

void getMap(string file, vector<relationshipMap>& map);
long long convert(vector<relationshipMap>& map, long long id);
vector<idRange> getSubranges(vector<relationshipMap>& map, idRange range);
vector<idRange> iterativeSubranges(vector<relationshipMap>& map, vector<idRange>& ranges);


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

    //Sort the relationship maps by source
    sort(seedToSoil.begin(), seedToSoil.end());
    sort(soilToFertilizer.begin(), soilToFertilizer.end());
    sort(fertilizerToWater.begin(), fertilizerToWater.end());
    sort(waterToLight.begin(), waterToLight.end());
    sort(lightToTemperature.begin(), lightToTemperature.end());
    sort(temperatureToHumidity.begin(), temperatureToHumidity.end());
    sort(humidityToLocation.begin(), humidityToLocation.end());


    //Read through the seed ranges, and use them to generate subranges for each map.

    ifstream infile;
    infile.open(prefix + "seeds.txt");
    string seed;
    string range;
    
    long long minLocation = LLONG_MAX;
    
    while (infile >> seed)
    {
        infile >> range;
        long long duration = stoll(range);
        long long id = stoll(seed);
        idRange seeds;
        seeds.start = id;
        seeds.end = id + duration - 1;
        //get vector of ranges of soils.
        vector<idRange> soils = getSubranges(seedToSoil, seeds);

        vector<idRange> fertilizers = iterativeSubranges(soilToFertilizer, soils);

        vector<idRange> waters = iterativeSubranges(fertilizerToWater, fertilizers);

        vector<idRange> lights = iterativeSubranges(waterToLight, waters);

        vector<idRange> temperatures = iterativeSubranges(lightToTemperature, lights);

        vector<idRange> humidities = iterativeSubranges(temperatureToHumidity, temperatures);

        vector<idRange> locations = iterativeSubranges(humidityToLocation, humidities);

        //check the locations for the minimum
        for (int i = 0; i < locations.size(); ++i)
        {
            if (locations.at(i).start < minLocation)
            {
                minLocation = locations.at(i).start;
            }
        }
    }

    std::cout << minLocation;
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
        relations.source = stoll(source);
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

vector<idRange> getSubranges(vector<relationshipMap>& map, idRange range)
{
    vector<idRange> subranges;

    idRange tempRange;
    tempRange.start = range.start;
    tempRange.end = range.end;
    for (int i = 0; i < map.size(); ++i)
    {
        long long mapSourceStart = map.at(i).source;
        long long mapSourceEnd = map.at(i).source + map.at(i).range;
        long long mapDestinationStart = map.at(i).destination;
        long long mapDestinationEnd = map.at(i).destination + map.at(i).range;
        //If the range ends before the map even starts, then mapping is 1 to 1
        if (tempRange.end < mapSourceStart)
        {
            subranges.push_back(tempRange);
            return subranges;
        }

        //if it starts outside the range of the map, but ends inside it, break it up, and convert the range that is inside
        //mapping
        if (tempRange.start < mapSourceStart && tempRange.end < mapSourceEnd)
        {
            tempRange.end = mapSourceStart - 1;
            subranges.push_back(tempRange);
            tempRange.start = mapSourceStart;
            tempRange.end = range.end;
            idRange converted;
            converted.start = mapDestinationStart;
            converted.end = mapDestinationStart + (tempRange.end - tempRange.start);
            subranges.push_back(converted);
            return subranges;
        }

        //if the range is entirely contained within a mapping
        if (tempRange.start >= mapSourceStart && tempRange.start < mapSourceEnd && tempRange.end < mapSourceEnd)
        {
            idRange converted;
            long long leftOffset = tempRange.start - mapSourceStart;
            long long rightOffset = tempRange.end - mapSourceStart;
            converted.start = mapDestinationStart + leftOffset;
            converted.end = mapDestinationStart + rightOffset;
            subranges.push_back(converted);
            return subranges;
        }

        //if the range starts within the mapping, but ends outside of it
        if (tempRange.start >= mapSourceStart && tempRange.start < mapSourceEnd && tempRange.end >= mapSourceEnd)
        {
            idRange converted;
            long long leftOffset = tempRange.start - mapSourceStart;
            converted.start = mapDestinationStart + leftOffset;
            converted.end = mapDestinationEnd -1;
            subranges.push_back(converted);
            tempRange.start = mapSourceEnd;
        }
        
        //if the range starts before the mapping, but ends after it
        if (tempRange.start < mapSourceStart && tempRange.end >= mapSourceEnd)
        {
            //Map the range 1 to 1 until you hit the start of the map
            tempRange.end = mapSourceStart - 1;
            subranges.push_back(tempRange);
            
            //Add the entirety of the map destination range
            idRange converted;
            converted.start = mapDestinationStart;
            converted.end = mapDestinationEnd -1;
            subranges.push_back(converted);

            //Set the tempRange beginning to the end of the map range, and fix the end.
            tempRange.start = mapSourceEnd;
            tempRange.end = range.end;

        }
    }

    //If we get through all of the mappings, and the subranges hasn't been returned yet, that means the range extends outside
    //all mappings. The remainder is mapped 1 to 1

    subranges.push_back(tempRange);
    return subranges;
}

vector<idRange> iterativeSubranges(vector<relationshipMap>& map, vector<idRange>& ranges)
{
    vector<idRange> newRanges;
    for (int i = 0; i < ranges.size(); ++i)
    {
        vector<idRange> temp = getSubranges(map, ranges.at(i));
        newRanges.insert(newRanges.end(), temp.begin(), temp.end());
    }
    return newRanges;
}

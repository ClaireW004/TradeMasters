#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "fileRead.h"
using namespace std;

unordered_map<string, string> parseCountryFile(const string& filePath) {
    unordered_map<string, string> country_map;
    ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return country_map;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string country_code, country_name_abbreviation;

        getline(ss, country_code, ',');
        getline(ss, country_name_abbreviation, ',');


        country_map[country_code] = country_name_abbreviation;
    }

    file.close();
    return country_map;
}
bool isProductCodeInCSV(const string& filename, const string& productCode) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == string::npos) {
            continue;
        }

        string code = line.substr(0, commaPos);
        if (code == productCode) {
            return true;
        }
    }

    file.close();
    return false;
}

class AdjacencyList {
public:
    map<string, vector<pair<string, string>>> graph;
    map<float,vector<string>> outputMap;

    string testOutput;
    unordered_map<string, string> country_map = parseCountryFile("country_codes_V202401b.csv");

    void add_keys(string importer, string exporter1, string price) {
        if(graph.find(importer) == graph.end()) {

        }
        graph[importer].push_back(make_pair(exporter1, price));

        if (graph.find(exporter1) == graph.end()) {
            graph[exporter1] = {};
        }
    }

    void traverseList(string key){
        for (auto pair : graph[key]) {
            if (graph[key].size() == 0){
                cout << "Country is not importing certain good from other countries!" << endl;
                return;
            }

            outputMap[stof(pair.second)].push_back(pair.first);
            //std::cout << country_map[pair.first] << " -> " << pair.second << std::endl;
        }
        for (auto key : outputMap){
            for (auto value: key.second){
                cout << country_map[value] << " --> " << key.first << endl;
            }
        }
    }

    void clean(){

    }
};


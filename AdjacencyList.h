#pragma once
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "fileRead.h"
using namespace std;

class AdjacencyList {
private:
    map<string, vector<pair<string, string>>> graph;
    map<float,vector<string>> outputMap;
public:
    void add_keys(const string& importer, const string& exporter1, const string& price);
    void traverseList(const string& inputCountryName, unordered_map<string, string> countryMapCodeToName, unordered_map<string, string> countryMapNameToCode);
};
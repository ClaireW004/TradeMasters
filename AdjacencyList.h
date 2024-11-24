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

unordered_map<string, string> parseCountryFile(const string& filePath);
bool isProductCodeInCSV(const string& filename, const string& productCode);

class AdjacencyList {
public:
    map<string, vector<pair<string, string>>> graph;
    map<float,vector<string>> outputMap;

    string testOutput;
    unordered_map<string, string> country_map = parseCountryFile("country_codes_V202401b.csv");

    void add_keys(string importer, string exporter1, string price);
    void traverseList(string key);
    void clean();
};


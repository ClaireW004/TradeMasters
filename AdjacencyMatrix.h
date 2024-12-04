#pragma once
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "fileRead.h"
using namespace std;

class AdjacencyMatrix {
private:
    vector<string> countries;
    int num_countries = 895;
    vector<vector<float>> matrix;
public:
    AdjacencyMatrix() {
        matrix = vector<vector<float>>(num_countries, vector<float>(num_countries, -1.0f));
    }
    int countryToIndex(string countryCode);
    string indexToCountry(int index);
    void addTradeRelation(string importCountry, string exportCountry, float productUnitCost);
    void traverseMatrix(int importerCode);

};
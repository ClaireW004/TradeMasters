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

//    void traverseMatrix(string importCountry) {
//        int index = countryToIndex(importCountry);
//        vector<float> values = matrix[index];
//        for (int i = 0; i < matrix.size(); i++) {
//            if (i == index) {
//                string exportCountry = indexToCountry(i);
//                for (int j = 0; j < matrix[i].size(); j++) {
//                    cout << exportCountry << " --> " << to_string(j) << endl;
//                }
//            }
//        }
//    }
};
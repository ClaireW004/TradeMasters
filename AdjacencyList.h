#pragma once
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "fileRead.h"
using namespace std;

class AdjacencyList {
public:

    map<string, vector<pair<string, string>>> graph;
    map<float,vector<string>> outputMap;


public:
    string testOutput;
    unordered_map<string, string> country_map = parseCountryFile("country_codes_V202401b.csv");

    void add_keys(string import, string export1, string price) {
        if(graph.find(import) == graph.end()) {

        }
        graph[import].push_back(make_pair(export1, price));

        if(graph.find(export1) == graph.end()) {

            graph[export1] = {};
        }
    }
    void traverse(string key){
        for (auto pair : graph[key]) {
            if(graph[key].size()==0){
                cout<<"Country is not importing certain good from other countries!"<<endl;
                return;
            }

            outputMap[stof(pair.second)].push_back(pair.first);
            //std::cout << country_map[pair.first] << " -> " << pair.second << std::endl;
        }
        for(auto key:outputMap){
            for(auto value: key.second){
                cout<<country_map[value]<<"-->"<<key.first<<endl;
            }
        }
    }

    void clean(){

    }




};


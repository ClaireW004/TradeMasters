#include "AdjacencyList.h"

//this function adds each trade from the "BACI_HS22_Y2022_V202401b_final.csv" file into the adjacency list
//with the importer as the key and a pair of exporting country and value of the trade as the value
void AdjacencyList::add_keys(const string& importer, const string& exporter1, const string& price) {
    if(graph.find(importer) == graph.end()) {
        graph[importer] = {};
    }
    graph[importer].push_back(make_pair(exporter1, price));
}

//this function goes through the entire adjacency list
void AdjacencyList::traverseList(const string& inputCountryName, unordered_map<string, string> countryMapCodeToName, unordered_map<string, string> countryMapNameToCode){
    outputMap.clear();
    string countryCode = countryMapNameToCode[inputCountryName];
    //goes through each exporter, price pair for the user-selected importing country
    for (const auto& pair : graph[countryCode]) {
        if (graph[countryCode].empty()){
            cout << "Country is not importing certain good from other countries!" << endl;
            return;
        }
        //creates the outputMap which stores the unit-cost and exporter
        outputMap[stof(pair.second)].push_back(pair.first);
    }
    //for each key in the output map and each unit-price, the country name and unit-cost of the
    //trade is output for the user
    for (const auto& key : outputMap){
        for (const auto& value: key.second){
            cout << countryMapCodeToName[value] << " --> " << key.first << endl;
        }
    }
}

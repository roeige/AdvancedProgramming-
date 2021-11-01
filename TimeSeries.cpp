//
// Created by itay2 on 31/10/2021.
//

#include "TimeSeries.h"
#include <iostream>
#include <string>
using std::string;
using std::vector;
using std::getline;

/**
 * This is the main builder of TimeSeries. is creat a new table from csv file.
 * @param fileName
 */
TimeSeries::TimeSeries(char *fileName) {
    std::fstream myfile;
    //open file and read mode.
    myfile.open(fileName, std::ios::in);
    if (myfile.is_open()) {
        string line;
        int first_line = 1;
        //go through the lines.
        while (getline(myfile, line)) {
            //if it's the first line - we added the data to br the headline of the vector.
            if (first_line) {
                createKeysFromLine(line);
                first_line = 0;
            //if we creat before to the table vector - we just add the data to the existing vectors by order.
            } else {
                addValuesFromLine(line);
            }
        }
    }
    myfile.close();
}

/**
 * This function creat new vectors to the table. the first data in the vectors is the given data.
 * @param line
 */
void TimeSeries::createKeysFromLine(string line) {
    size_t pos = 0;
    string token;
    string delimiter = ",";

    //we split the line and add the data to new vectors and push them into the feature_table.
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        feature_names.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    //we add one more vector because the last token finished without ',' - so we need to add it anyway.
    feature_names.push_back(token);
}

/**
 * This function add values to the existing table by the order they been given.
 * @param line
 */
void TimeSeries::addValuesFromLine(string line) {
    int pos = 0;

    if(0 == feature_table.size()) {
        if(0 == feature_names.size()) {

        } else {
            for (auto & i : feature_names) {
                int counter = line.find(',',pos);
                string temp = line.substr(pos, counter);
                double double_temp = stoi(temp,)
                i.push_back(temp);
                line.erase(pos, counter + 1);
            }
        }
    }

    for (auto & i : feature_names) {
        int counter = line.find(',',pos);
        string temp = line.substr(pos, counter);
        i.push_back(temp);
        line.erase(pos, counter + 1);
    }
}

/**
 * This function return
 * @return const vector<vector<string> >
 */
vector<vector<double> > TimeSeries::getFeatureTable() const{
    return feature_table;
}

vector<std::string> TimeSeries::getNameTable() const{
    return feature_names;
}

int TimeSeries::size() const {
    return feature_table.size();
}
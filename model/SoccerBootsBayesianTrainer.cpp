//
// Created by 허온 on 2026. 2. 7..
//

#include "SoccerBootsBayesianTrainer.h"
#include <cmath>
#include <set>

using namespace std;

void SoccerBootsBayesianTrainer::calculatePriors() {
    map<string, int> newBootsCount;
    vector<int> counts;

    double allBootsCount = 0;
    for(auto d : data) {
        string bootsName = d.getText("boots_name");
        newBootsCount[bootsName]++;
        allBootsCount++;
    }

    for(const auto& [name, count] : newBootsCount) {
        priors[name] = count / allBootsCount;
    }
    bootsCount = newBootsCount;
}

void SoccerBootsBayesianTrainer::calculateCategoryLikelihoods() {
    for(auto& d : data) {
        string bootsName = d.getText("boots_name");

        for(auto& [variableKey, _] : SoccerPlayerBoots::textKeys)
            addTextCategory(bootsName, variableKey, d.getText(variableKey));

        for(auto& [variableKey, _] : SoccerPlayerBoots::listKeys) {
            vector<string> values = d.getList(variableKey);
            addListCategory(bootsName, variableKey, values);
        }
    }
}

void SoccerBootsBayesianTrainer::addTextCategory(const string& bootsName, const string& feature, const string& value) {
    categoryLikelihoods[bootsName][feature][value]++;
}

void SoccerBootsBayesianTrainer::addListCategory(const string& bootsName, const string& feature, const vector<string>& values) {
    for(auto& v : values) {
        categoryLikelihoods[bootsName][feature][v]++;
        listCategoryTotalWords[bootsName]++;
    }
}

void SoccerBootsBayesianTrainer::calculateNumLikelihoods() {
    map<string, map<string, vector<double>>> bootsFeatureValues;

    for(auto& d : data) {
        string bootsName = d.getText("boots_name");

        for(auto& [variableKey, _] : SoccerPlayerBoots::numKeys)
            bootsFeatureValues[bootsName][variableKey].push_back(d.getNum(variableKey));
    }

    for(auto& [bootsName, featureMap] : bootsFeatureValues)
        for(auto& [feature, values] : featureMap) {
            double avg = mean(values);
            double var = variance(values);

            addNumeric(bootsName, feature, avg, var);
        }

}

double SoccerBootsBayesianTrainer::mean(const vector<double>& values) {
    double sum = 0;
    for(auto& v : values)
        sum += v;

    return sum / (int) values.size();
}

double SoccerBootsBayesianTrainer::variance(const vector<double>& values) {
    double avg = mean(values);
    double sum = 0;
    for(auto& v : values)
        sum += pow(v - avg, 2);

    return sum / (int) values.size();
}

void SoccerBootsBayesianTrainer::addNumeric(const string& bootsName, const string& feature, const double& avg, const double& var) {
    numericLikelihoods[bootsName][feature] = {avg, var};
}

vector<string> SoccerBootsBayesianTrainer::getBootsNames() {
    set<string> bootsNames;
    for(auto& d : data) {
        bootsNames.insert(d.getText("boots_name"));
    }

    return {bootsNames.begin(), bootsNames.end()};
}

map<string, int> SoccerBootsBayesianTrainer::getBootsCount() {
    if(bootsCount.empty()) {
        for(auto& d : data) {
            string bootsName = d.getText("boots_name");
            bootsCount[bootsName]++;
        }
    }
    return bootsCount;
}

map<string, int> SoccerBootsBayesianTrainer::getListCategoryCount() {
    map<string, set<string>> featureCategories;
    if(listCategoryCount.empty()) {
        for(auto& d : data) {
            for(auto& k : SoccerPlayerBoots::listKeys) {
                vector<string> values = d.getList(k.first);

                for(auto& v : values) {
                    featureCategories[k.first].insert(v);
                }
            }
        }

        for(auto& [key, values] : featureCategories) {
            listCategoryCount[key] = (int)values.size();
        }
    }

    return listCategoryCount;
}

map<string, double> SoccerBootsBayesianTrainer::getPriors() {
    return priors;
}

map<string, map<string, pair<double, double>>> SoccerBootsBayesianTrainer::getNumericLikelihoods() {
    return numericLikelihoods;
}

map<string, map<string, map<string, int>>> SoccerBootsBayesianTrainer::getCategoryLikelihoods() {
    return categoryLikelihoods;
}

map<string, int> SoccerBootsBayesianTrainer::getListCategoryTotalWords() {
    return listCategoryTotalWords;
}
//
// Created by 허온 on 2026. 2. 7..
//

#include "SoccerBootsBayesianTrainer.h"
#include <cmath>
#include <set>

using namespace std;

map<string, double> SoccerBootsBayesianTrainer::calculatePriors(const vector<SoccerPlayerBoots>& data) {
    map<string, double> priors;
    map<string, int> bootsCount;
    vector<int> counts;

    double allBootsCount = 0;
    for(auto d : data) {
        string bootsName = d.getText("boots_name");
        bootsCount[bootsName]++;
        allBootsCount++;
    }

    for(const auto& [name, count] : bootsCount) {
        priors[name] = count / allBootsCount;
    }

    return priors;
}

map<string, int> SoccerBootsBayesianTrainer::countBoots(const vector<SoccerPlayerBoots> &data) {
    map<string, int> bootsCount;

    for(auto d : data) {
        string bootsName = d.getText("boots_name");
        bootsCount[bootsName]++;
    }

    return bootsCount;
}

map<string, map<string, map<string, int>>> SoccerBootsBayesianTrainer::calculateCategoryLikelihoods(const vector<SoccerPlayerBoots>& data) {
    map<string, map<string, map<string, int>>> categoryLikelihoods;
    for(auto& d : data) {
        string bootsName = d.getText("boots_name");

        for(auto& [variableKey, _] : SoccerPlayerBoots::textKeys)
            categoryLikelihoods[bootsName][variableKey][d.getText(variableKey)]++;

        for(auto& [variableKey, _] : SoccerPlayerBoots::listKeys) {
            vector<string> values = d.getList(variableKey);
            for(auto& v : values)
                categoryLikelihoods[bootsName][variableKey][v]++;
        }
    }

    return categoryLikelihoods;
}

map<string, int> SoccerBootsBayesianTrainer::extractListCategoryTotalWords(const vector<SoccerPlayerBoots> &data) {
    map<string, int> listCategoryTotalWords;

    for(auto& d : data) {
        string bootsName = d.getText("boots_name");

        for(auto& [variableKey, _] : SoccerPlayerBoots::listKeys)
            listCategoryTotalWords[bootsName] += d.getList(variableKey).size();
    }

    return listCategoryTotalWords;
}

map<string, map<string, pair<double, double>>> SoccerBootsBayesianTrainer::calculateNumLikelihoods(const vector<SoccerPlayerBoots>& data) {
    map<string, map<string, pair<double, double>>> numericLikelihoods;
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

            numericLikelihoods[bootsName][feature] = {avg, var};
        }

    return numericLikelihoods;
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

vector<string> SoccerBootsBayesianTrainer::extractBootsNames(const vector<SoccerPlayerBoots>& data) {
    set<string> bootsNames;
    for(auto& d : data) {
        bootsNames.insert(d.getText("boots_name"));
    }

    return {bootsNames.begin(), bootsNames.end()};
}

map<string, int> SoccerBootsBayesianTrainer::extractListCategoryCount(const vector<SoccerPlayerBoots>& data) {
    map<string, int> listCategoryCount;

    for(auto& d : data) {
        for(auto& k : SoccerPlayerBoots::listKeys) {
            vector<string> values = d.getList(k.first);
            listCategoryCount[k.first] = (int)values.size();
        }
    }

    return listCategoryCount;
}

SoccerBootsBayesianModel SoccerBootsBayesianTrainer::fit(const vector<SoccerPlayerBoots>& data) {
    map<string, double> priors = calculatePriors(data);
    map<string, int> bootsCount = countBoots(data);
    map<string, int> listCategoryCount = extractListCategoryCount(data);
    map<string, map<string, pair<double, double>>> numericLikelihoods = calculateNumLikelihoods(data);
    map<string, map<string, map<string, int>>> categoryLikelihoods = calculateCategoryLikelihoods(data);
    map<string, int> listCategoryTotalWords = extractListCategoryTotalWords(data);
    vector<string> bootsNames = extractBootsNames(data);

    return SoccerBootsBayesianModel(bootsNames, bootsCount, listCategoryCount, listCategoryTotalWords,
                                    priors, numericLikelihoods, categoryLikelihoods);
}
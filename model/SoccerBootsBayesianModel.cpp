//
// Created by 허온 on 2026. 2. 17..
//

#include "SoccerBootsBayesianModel.h"

map<string, double> SoccerBootsBayesianModel::getPriors() const {
    return priors;
}

map<string, map<string, pair<double, double>>> SoccerBootsBayesianModel::getNumericLikelihoods() const {
    return numericLikelihoods;
}

map<string, map<string, map<string, int>>> SoccerBootsBayesianModel::getCategoryLikelihoods() const {
    return categoryLikelihoods;
}

map<string, int> SoccerBootsBayesianModel::getListCategoryTotalWords() const {
    return listCategoryTotalWords;
}

vector<string> SoccerBootsBayesianModel::getBootsNames() const {
    return bootsNames;
}

map<string, int> SoccerBootsBayesianModel::getBootsCount() const {
    return bootsCount;
}

map<string, int> SoccerBootsBayesianModel::getListCategoryCount() const {
    return listCategoryCount;
}
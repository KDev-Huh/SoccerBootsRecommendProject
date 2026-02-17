//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H

#include <map>
#include <string>
#include <vector>
#include "data/SoccerPlayerBoots.h"
#include "SoccerBootsBayesianModel.h"

using namespace std;

class SoccerBootsBayesianTrainer {
private:
    static vector<string> extractBootsNames(const vector<SoccerPlayerBoots>& data);
    static map<string, int> extractListCategoryCount(const vector<SoccerPlayerBoots>& data);

    static map<string, double> calculatePriors(const vector<SoccerPlayerBoots>& data);
    static map<string, int> countBoots(const vector<SoccerPlayerBoots>& data);
    static map<string, int> extractListCategoryTotalWords(const vector<SoccerPlayerBoots>& data);
    static map<string, map<string, map<string, int>>> calculateCategoryLikelihoods(const vector<SoccerPlayerBoots>& data);
    static map<string, map<string, pair<double, double>>> calculateNumLikelihoods(const vector<SoccerPlayerBoots>& data);

    static double mean(const vector<double>& values);
    static double variance(const vector<double>& values);

public:
    SoccerBootsBayesianModel fit(const vector<SoccerPlayerBoots>& data);
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H

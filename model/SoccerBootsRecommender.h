//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H

#include <string>
#include <map>
#include "SoccerBootsBayesianModel.h"

using namespace std;

class SoccerBootsRecommender {
private:
    SoccerBootsBayesianModel model;

    static pair<string, double> calculateResult(const map<string, double>& results);
    double calculateTextLikelihoods(const string& bootsName, const string& key, const string& value);
    double calculateNumLikelihoods(const string& bootsName, const string& key, const double& value);
    double calculateListLikelihoods(const string& bootsName, const string& key, const vector<string>& value);
    double calculateGaussian(const double& x, const double& m, const double& v);
    static double calculateLogGaussian(const double& x, const double& m, const double& v);
public:
    SoccerBootsRecommender(SoccerBootsBayesianModel model): model(model) {};

    pair<string, double> predict(
            const vector<pair<string, string>>& textInputs,
            const vector<pair<string, double>>& numInputs,
            const vector<pair<string, vector<string>>>& listInputs
    );
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H

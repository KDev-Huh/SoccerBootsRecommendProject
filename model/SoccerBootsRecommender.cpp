//
// Created by 허온 on 2026. 2. 7..
//

#include "SoccerBootsRecommender.h"
#include <cmath>

pair<string, double> SoccerBootsRecommender::predict(
        const vector<pair<string, string>>& textInputs,
        const vector<pair<string, double>>& numInputs,
        const vector<pair<string, vector<string>>>& listInputs
) {
    map<string, double> results;

    for(auto& bootsName : bootsNames) {
        double bayesResult = log(priors[bootsName]);

        // text
        for(auto& [key, value] : textInputs) {
            double textLikelihood = calculateTextLikelihoods(bootsName, key, value);
            if(textLikelihood == 0) {
                bayesResult = -INFINITY;
                // -INFINITY에 아무리 더해도 의미 없어서 break;
                break;
            }
            bayesResult += log(textLikelihood);
        }

        // num
        for(auto& [key, value] : numInputs)
            bayesResult += calculateNumLikelihoods(bootsName, key, value);

        // list
        for(auto& [key, value] : listInputs)
            bayesResult += calculateListLikelihoods(bootsName, key, value);

        results[bootsName] = bayesResult;
    }

    return calculateResult(results);
}

pair<string, double> SoccerBootsRecommender::calculateResult(const map<string, double>& results) {
    string bastBootsName;
    double maxScore = -INFINITY;
    double totalEvidence = 0.0;

    for(auto& [bootsName, score] : results) {
        if(score > maxScore) {
            bastBootsName = bootsName;
            maxScore = score;
        }

        totalEvidence += exp(score);
    }

    double possibilityProbability = exp(maxScore) / totalEvidence;

    return {bastBootsName, possibilityProbability};
}

double SoccerBootsRecommender::calculateTextLikelihoods(const string& bootsName, const string& key, const string& value) {
    return ((double) categoryLikelihoods[bootsName][key][value]) / bootsCount[bootsName];
}

double SoccerBootsRecommender::calculateNumLikelihoods(const std::string &bootsName, const std::string &key, const double &value) {
    double avg = numericLikelihoods[bootsName][key].first;
    double var = numericLikelihoods[bootsName][key].second;

    return calculateLogGaussian(value, avg, var);
}

// x: 사용자 입력값, m: 평균, v: 분산
double SoccerBootsRecommender::calculateGaussian(const double& x, const double& m, const double& v) {
    // 분산이 0인 경우(모든 데이터가 똑같을 때) 에러 방지
    if (v == 0) return (x == m) ? 1.0 : 0.0;

    // 공식: (1 / sqrt(2 * pi * v)) * exp(- (x - m)^2 / (2 * v))
    double exponent = exp(-pow(x - m, 2) / (2 * v));
    double coefficient = 1.0 / sqrt(2 * M_PI * v);

    return coefficient * exponent;
}

// 로그 가우시안
double SoccerBootsRecommender::calculateLogGaussian(const double& x, const double& m, const double& v) {
    if (v == 0) return (x == m) ? 0.0 : -1e9; // 로그에서는 0이 매우 작은 음수

    double term1 = -0.5 * log(2 * M_PI * v);
    double term2 = -pow(x - m, 2) / (2 * v);

    return term1 + term2;
}

double SoccerBootsRecommender::calculateListLikelihoods(const std::string &bootsName, const std::string &key, const vector<std::string> &value) {
    double likelihoods = 0;

    for(auto& v : value) {
        int numerator = categoryLikelihoods[bootsName][key][v] + 1;
        int denominator = listCategoryTotalWords[bootsName] + listCategoryCount[key];

        // 라플라스 스무딩 적용
        double prob = (double)numerator / (double)denominator;
        likelihoods += log(prob);
    }

    return likelihoods;
}
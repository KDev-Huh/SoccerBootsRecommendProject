//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H

#include <map>
#include <string>
#include <vector>
#include "data/SoccerPlayerBoots.h"

using namespace std;

class SoccerBootsBayesianTrainer {
private:
    vector<SoccerPlayerBoots> data;
    map<string, double> priors;

    // 해당 축구화 신는 사람들의 인원
    map<string, int> bootsCount;
    // 각 리스트 컬럼 별 값 갯수
    map<string, int> listCategoryCount;

    // [축구화이름][스탯이름] = {평균, 분산}
    map<string, map<string, pair<double, double>>> numericLikelihoods;
    // 예: ["머큐리얼"]["position"]["FW"] = 45회
    // 예: ["머큐리얼"]["strengths"]["Speed"] = 30회
    map<string, map<string, map<string, int>>> categoryLikelihoods;
    // [축구화이름] = 43회 해당 모델의 총 단어 수 (리스트 안에 있는 단어)
    map<string, int> listCategoryTotalWords;

    void addListCategory(const string& bootsName, const string& feature, const vector<string>& values);
    void addTextCategory(const string& bootsName, const string& feature, const string& value);
    void addNumeric(const string& bootsName, const string& feature, const double& avg, const double& var);

    double mean(const vector<double>& values);
    double variance(const vector<double>& values);
public:
    SoccerBootsBayesianTrainer(const vector<SoccerPlayerBoots>& data)
            : data(data) {};

    void calculatePriors();
    // text, list
    void calculateCategoryLikelihoods();
    void calculateNumLikelihoods();
    vector<string> getBootsNames();
    map<string, int> getBootsCount();
    map<string, int> getListCategoryCount();

    map<string, double> getPriors();
    map<string, map<string, pair<double, double>>> getNumericLikelihoods();
    map<string, map<string, map<string, int>>> getCategoryLikelihoods();
    map<string, int> getListCategoryTotalWords();
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANTRAINER_H

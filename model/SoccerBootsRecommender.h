//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H

#include <string>
#include <map>

using namespace std;

class SoccerBootsRecommender {
private:
    // 전확률
    map<string, double> priors;
    // [축구화이름][스탯이름] = {평균, 분산}
    map<string, map<string, pair<double, double>>> numericLikelihoods;
    // 예: ["머큐리얼"]["position"]["FW"] = 45회
    // 예: ["머큐리얼"]["strengths"]["Speed"] = 30회
    map<string, map<string, map<string, int>>> categoryLikelihoods;
    // [축구화이름] = 43회 해당 모델의 총 단어 수 (리스트 안에 있는 단어)
    map<string, int> listCategoryTotalWords;

    // 결과 축구화 리스트
    vector<string> bootsNames;
    // 해당 축구화 신는 사람들의 인원
    map<string, int> bootsCount;
    // 각 리스트 컬럼 별 값 갯수
    map<string, int> listCategoryCount;

    pair<string, double> calculateResult(const map<string, double>& results);
    double calculateTextLikelihoods(const string& bootsName, const string& key, const string& value);
    double calculateNumLikelihoods(const string& bootsName, const string& key, const double& value);
    double calculateListLikelihoods(const string& bootsName, const string& key, const vector<string>& value);
    double calculateGaussian(const double& x, const double& m, const double& v);
    double calculateLogGaussian(const double& x, const double& m, const double& v);
public:
    SoccerBootsRecommender(
            const map<string, double>& priors,
            const map<string, map<string, pair<double, double>>>& numericLikelihoods,
            const map<string, map<string, map<string, int>>>& categoryLikelihoods,
            const map<string, int>& listCategoryTotalWords,
            const vector<string>& bootsNames,
            const map<string, int>& bootsCount,
            const map<string, int>& listCategoryCount
    )
    : priors(priors), numericLikelihoods(numericLikelihoods), categoryLikelihoods(categoryLikelihoods), listCategoryTotalWords(listCategoryTotalWords), bootsNames(bootsNames), bootsCount(bootsCount), listCategoryCount(listCategoryCount) {};

    pair<string, double> predict(
            const vector<pair<string, string>>& textInputs,
            const vector<pair<string, double>>& numInputs,
            const vector<pair<string, vector<string>>>& listInputs
    );
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSRECOMMENDER_H

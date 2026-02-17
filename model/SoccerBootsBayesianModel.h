//
// Created by 허온 on 2026. 2. 17..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANMODEL_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANMODEL_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class SoccerBootsBayesianModel {
private:
    // 결과 축구화 리스트
    vector<string> bootsNames;
    // 해당 축구화 신는 사람들의 인원
    map<string, int> bootsCount;
    // 각 리스트 컬럼 별 값 갯수
    map<string, int> listCategoryCount;
    // [축구화이름] = 43회 해당 모델의 총 단어 수 (리스트 안에 있는 단어)
    map<string, int> listCategoryTotalWords;

    map<string, double> priors;
    // [축구화이름][스탯이름] = {평균, 분산}
    map<string, map<string, pair<double, double>>> numericLikelihoods;
    // 예: ["머큐리얼"]["position"]["FW"] = 45회
    // 예: ["머큐리얼"]["strengths"]["Speed"] = 30회
    map<string, map<string, map<string, int>>> categoryLikelihoods;

public:
    SoccerBootsBayesianModel(
            const vector<string>& bootsNames,
            const map<string, int>& bootsCount,
            const map<string, int>& listCategoryCount,
            const map<string, int>& listCategoryTotalWords,
            const map<string, double>& priors,
            const map<string, map<string, pair<double, double>>>& numericLikelihoods,
            const map<string, map<string, map<string, int>>>& categoryLikelihoods
    )
    : bootsNames(bootsNames), priors(priors), bootsCount(bootsCount), listCategoryCount(listCategoryCount),
    numericLikelihoods(numericLikelihoods), categoryLikelihoods(categoryLikelihoods), listCategoryTotalWords(listCategoryTotalWords) {};

    [[nodiscard]] map<string, double> getPriors() const;
    [[nodiscard]] map<string, map<string, pair<double, double>>> getNumericLikelihoods() const;
    [[nodiscard]] map<string, map<string, map<string, int>>> getCategoryLikelihoods() const;
    [[nodiscard]] map<string, int> getListCategoryTotalWords() const;
    [[nodiscard]] vector<string> getBootsNames() const;
    [[nodiscard]] map<string, int> getBootsCount() const;
    [[nodiscard]] map<string, int> getListCategoryCount() const;
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERBOOTSBAYESIANMODEL_H

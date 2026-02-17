//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTS_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTS_H

#include <string>
#include <map>

using namespace std;

class SoccerPlayerBoots {
private:
    map<string, double> numericStats;
    map<string, string> textStats;
    map<string, vector<string>> listStats;
public:
    const static vector<pair<string, string>> textKeys;
    const static vector<pair<string, string>> numKeys;
    const static vector<pair<string, string>> listKeys;

    void addNumeric(const string& key, const double& value);
    void addText(const string& key, const string& value);
    void addList(const string& key, string listStr);

    [[nodiscard]] double getNum(const string& key) const;
    [[nodiscard]] string getText(const string& key) const;
    [[nodiscard]] vector<string> getList(const string& key) const;
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTS_H


//
// Created by 허온 on 2026. 2. 7..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTSDATACSVREADER_H
#define SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTSDATACSVREADER_H

#include "data/SoccerPlayerBoots.h"

class SoccerPlayerBootsDataCsvReader {
private:
    vector<SoccerPlayerBoots> playerBoots;
public:
    void readCsvData(const vector<string>& paths);
    vector<SoccerPlayerBoots> getPlayerBoots();
};


#endif //SOCCER_BOOTS_BAYES_PROJECT_SOCCERPLAYERBOOTSDATACSVREADER_H

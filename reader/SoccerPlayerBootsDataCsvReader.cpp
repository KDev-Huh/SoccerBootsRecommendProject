//
// Created by 허온 on 2026. 2. 7..
//

#include "SoccerPlayerBootsDataCsvReader.h"
#include "rapidcsv.h"

void SoccerPlayerBootsDataCsvReader::readCsvData(const vector<string>& paths) {
    for(const string& path : paths) {
        rapidcsv::Document doc(path);

        // 전체 행 수만큼 반복
        for (size_t i = 0; i < doc.GetRowCount(); ++i) {
            SoccerPlayerBoots p;

            // 텍스트 데이터 삽입
            for(auto& [variableKey, dataKey] : SoccerPlayerBoots::textKeys)
                p.addText(variableKey, doc.GetCell<string>(dataKey, i));

            // 수치 데이터 삽입
            for(auto& [variableKey, dataKey] : SoccerPlayerBoots::numKeys)
                p.addNumeric(variableKey, doc.GetCell<double>(dataKey, i));

            // 리스트 데이터 삽입
            for(auto& [variableKey, dataKey] : SoccerPlayerBoots::listKeys)
                p.addList(variableKey, doc.GetCell<string>(dataKey, i));

            if (!p.getText("boots_name").empty()) {
                playerBoots.push_back(p);
            }
        }
    }
}

vector<SoccerPlayerBoots> SoccerPlayerBootsDataCsvReader::getPlayerBoots() {
    return playerBoots;
}
//
// Created by 허온 on 2026. 2. 7..
//

#include <sstream>
#include "SoccerPlayerBoots.h"

const vector<pair<string, string>> SoccerPlayerBoots::textKeys{
        {"player_name",         "player_name"},
        {"player_nationality",  "player_nationality"},
        {"player_positions",    "player_positions"},
        {"boots_name",          "BootsName"},
        {"player_shirt_number", "player_shirt_number"},
};

const vector<pair<string, string>> SoccerPlayerBoots::numKeys{
        {"player_age",    "player_age"},
        {"player_height", "player_height"},
        {"apps",          "Apps"},
        {"mins",          "Mins"},
        {"goals",         "Goals"},
        {"assists",       "Assists"},
        {"yel",           "Yel"},
        {"red",           "Red"},
        {"spg",           "SpG"},
        {"ps",            "PS"},
        {"aerials_won",   "AerialsWon"},
        {"motm",          "MotM"},
        {"rating",        "Rating"},
        {"tackles",       "Tackles"},
        {"inter",         "Inter"},
        {"fouls",         "Fouls"},
        {"offsides",      "Offsides"},
        {"clear",         "Clear"},
        {"drb",           "Drb"},
        {"blocks",        "Blocks"},
        {"own_g",         "OwnG"},
        {"key_p",         "KeyP"},
        {"fouled",        "Fouled"},
        {"off",           "Off"},
        {"disp",          "Disp"},
        {"uns_tch",       "UnsTch"},
        {"avg_p",         "AvgP"},
        {"crosses",       "Crosses"},
        {"long_b",        "LongB"},
        {"thr_b",         "ThrB"},
};

const vector<pair<string, string>> SoccerPlayerBoots::listKeys{
        {"strengths", "strengths"},
        {"weaknesses", "weaknesses"},
        {"player_style", "player_style"}
};

void SoccerPlayerBoots::addNumeric(const string& key, const double& value) {
    numericStats[key] = value;
}

void SoccerPlayerBoots::addText(const string& key, const string& value) {
    textStats[key] = value;
}

void SoccerPlayerBoots::addList(const string& key, string listStr) {
    // [ ] ' , 문자들을 제거하고 콤마로 분리하는 간단한 로직
    for(char &c : listStr)
        if(c == '[' || c == ']' || c == '\'') c = ' ';

    stringstream ss(listStr);
    string segment;
    while (getline(ss, segment, ',')) {
        // 앞뒤 공백 제거 후 추가
        segment.erase(0, segment.find_first_not_of(" "));
        segment.erase(segment.find_last_not_of(" ") + 1);
        if(!segment.empty()) listStats[key].push_back(segment);
    }
}

double SoccerPlayerBoots::getNum(const string& key) {
    return numericStats[key];
}

string SoccerPlayerBoots::getText(const string& key) {
    return textStats[key];
}

vector<string> SoccerPlayerBoots::getList(const string& key) {
    return listStats[key];
}
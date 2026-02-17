//
// Created by 허온 on 2026. 2. 17..
//

#include "RecommendationController.h"

#include <string>
#include <vector>
#include <utility>

using namespace std;

RecommendationController::RecommendationController(SoccerBootsRecommender& recommender)
    : recommender_(recommender) {}

void RecommendationController::addCorsHeaders(crow::response& res) {
    res.add_header("Access-Control-Allow-Origin", "*");
    res.add_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.add_header("Access-Control-Allow-Headers", "Content-Type");
}

crow::response RecommendationController::handleOptions(const crow::request& /*req*/) const {
    auto res = crow::response(200);
    addCorsHeaders(res);
    return res;
}

crow::response RecommendationController::handlePost(const crow::request& req) {
    const auto body = crow::json::load(req.body);

    if (!body) {
        auto res = crow::response(400);
        addCorsHeaders(res);
        return res;
    }

    // 텍스트 입력 파싱
    vector<pair<string, string>> textInputs;
    for (const auto& item : body["textInputs"]) {
        textInputs.emplace_back(item["key"].s(), item["value"].s());
    }

    // 수치 입력 파싱
    vector<pair<string, double>> numInputs;
    for (const auto& item : body["numInputs"]) {
        numInputs.emplace_back(item["key"].s(), item["value"].d());
    }

    // 리스트 입력 파싱
    vector<pair<string, vector<string>>> listInputs;
    for (const auto& item : body["listInputs"]) {
        vector<string> values;
        for (const auto& v : item["value"]) {
            values.push_back(v.s());
        }
        listInputs.emplace_back(item["key"].s(), std::move(values));
    }

    const auto [bootsName, probability] = recommender_.predict(textInputs, numInputs, listInputs);

    crow::json::wvalue resBody;
    resBody["boots"] = bootsName;
    resBody["prob"]  = probability;

    auto res = crow::response{resBody};
    addCorsHeaders(res);
    return res;
}

void RecommendationController::registerRoutes(crow::SimpleApp& app) {
    // CORS 프리플라이트 요청 처리
    CROW_ROUTE(app, "/recommend/soccer-boots")
        .methods("OPTIONS"_method)
        ([this](const crow::request& req) {
            return handleOptions(req);
        });

    // 축구화 추천 요청 처리
    CROW_ROUTE(app, "/recommend/soccer-boots")
        .methods("POST"_method)
        ([this](const crow::request& req) {
            return handlePost(req);
        });
}

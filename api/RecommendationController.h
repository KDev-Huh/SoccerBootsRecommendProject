//
// Created by 허온 on 2026. 2. 17..
//

#ifndef SOCCER_BOOTS_BAYES_PROJECT_RECOMMENDATIONCONTROLLER_H
#define SOCCER_BOOTS_BAYES_PROJECT_RECOMMENDATIONCONTROLLER_H

#include <crow.h>
#include "model/SoccerBootsRecommender.h"

class RecommendationController {
private:
    SoccerBootsRecommender& recommender_;

    static void addCorsHeaders(crow::response& res);

    // [[nodiscard]]는 반환값 사용 강제함
    [[nodiscard]] crow::response handleOptions(const crow::request& req) const;
    crow::response handlePost(const crow::request& req);

public:
    explicit RecommendationController(SoccerBootsRecommender& recommender);

    void registerRoutes(crow::SimpleApp& app);
};

#endif //SOCCER_BOOTS_BAYES_PROJECT_RECOMMENDATIONCONTROLLER_H

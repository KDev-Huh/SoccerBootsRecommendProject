#include <iostream>
#include "reader/SoccerPlayerBootsDataCsvReader.h"
#include "model/SoccerBootsBayesianTrainer.h"
#include "model/SoccerBootsRecommender.h"
#include <crow.h>

int main() {
    vector<string> paths{
        "../datasets/germany-bundesliga-players_boots.csv",
        "../datasets/premier-league-players_boots.csv",
        "../datasets/spain-laliga-players_boots.csv"
    };

    SoccerPlayerBootsDataCsvReader reader;

    reader.SoccerPlayerBootsDataCsvReader::readCsvData(paths);
    vector<SoccerPlayerBoots> playerBoots = reader.getPlayerBoots();

    SoccerBootsBayesianTrainer trainer(playerBoots);
    trainer.calculatePriors();
    trainer.calculateNumLikelihoods();
    trainer.calculateCategoryLikelihoods();

    SoccerBootsRecommender recommender(
            trainer.getPriors(),
            trainer.getNumericLikelihoods(),
            trainer.getCategoryLikelihoods(),
            trainer.getListCategoryTotalWords(),
            trainer.getBootsNames(),
            trainer.getBootsCount(),
            trainer.getListCategoryCount()
    );

    crow::SimpleApp app;

    CROW_ROUTE(app, "/recommend/soccer-boots")
            .methods("POST"_method)
                    ([&recommender](const crow::request& req){

                        auto body = crow::json::load(req.body);

                        if (!body)
                            return crow::response(400);

                        vector<pair<string,string>> textInputs;

                        for (auto& item : body["textInputs"]) {
                            string key   = item["key"].s();
                            string value = item["value"].s();

                            textInputs.emplace_back(key, value);
                        }

                        vector<pair<string,double>> numInputs;

                        for (auto& item : body["numInputs"]) {
                            string key   = item["key"].s();
                            double value = item["value"].d();

                            numInputs.emplace_back(key, value);
                        }

                        vector<pair<string, vector<string>>> listInputs;

                        for (auto& item : body["listInputs"]) {

                            string key = item["key"].s();
                            vector<string> values;

                            for (auto& v : item["value"]) {
                                values.push_back(v.s());
                            }

                            listInputs.emplace_back(key, values);
                        }

                        pair<string, double> result = recommender.predict(textInputs, numInputs, listInputs);

                        crow::json::wvalue res;
                        res["boots"] = result.first;
                        res["prob"]  = result.second;

                        return crow::response{res};
                    });

    app.port(8080).multithreaded().run();

    return 0;
}

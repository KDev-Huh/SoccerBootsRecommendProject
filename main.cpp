#include <iostream>
#include "reader/SoccerPlayerBootsDataCsvReader.h"
#include "model/SoccerBootsBayesianTrainer.h"
#include "model/SoccerBootsRecommender.h"

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

    // Test prediction with sample data (similar to Mohamed Salah style)
    vector<pair<string, string>> textInputs = {};

    vector<pair<string, double>> numInputs = {
        {"player_age", 30.0},
        {"player_height", 175.0},
        {"goals", 35.0},
        {"assists", 20.0},
        {"rating", 7.5}
    };

    vector<pair<string, vector<string>>> listInputs = {
        {"strengths", {"Key passes", "Finishing", "Through balls"}},
        {"weaknesses", {"Defensive contribution"}},
        {"player_style", {"Likes to cut inside", "Plays the ball off the ground often"}}
    };

    pair<string, double> result = recommender.predict(textInputs, numInputs, listInputs);

    cout << "Recommended Boots: " << result.first << endl;
    cout << "Probability: " << result.second << endl;

    return 0;
}

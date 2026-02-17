#include "reader/SoccerPlayerBootsDataCsvReader.h"
#include "model/SoccerBootsBayesianTrainer.h"
#include "model/SoccerBootsRecommender.h"
#include "api/ApiServer.h"
#include "api/RecommendationController.h"

int main() {
    // 1. 데이터 로드
    const std::vector<std::string> datasetPaths{
        "../datasets/germany-bundesliga-players_boots.csv",
        "../datasets/premier-league-players_boots.csv",
        "../datasets/spain-laliga-players_boots.csv"
    };

    SoccerPlayerBootsDataCsvReader reader;
    reader.readCsvData(datasetPaths);

    // 2. 베이지안 모델 학습
    SoccerBootsBayesianTrainer trainer(reader.getPlayerBoots());
    trainer.calculatePriors();
    trainer.calculateNumLikelihoods();
    trainer.calculateCategoryLikelihoods();

    // 3. 추천기 생성
    SoccerBootsRecommender recommender(
        trainer.getPriors(),
        trainer.getNumericLikelihoods(),
        trainer.getCategoryLikelihoods(),
        trainer.getListCategoryTotalWords(),
        trainer.getBootsNames(),
        trainer.getBootsCount(),
        trainer.getListCategoryCount()
    );

    // 4. API 서버 설정 및 실행
    RecommendationController controller(recommender);

    ApiServer server(8080);
    controller.registerRoutes(server.getApp());
    server.run();

    return 0;
}

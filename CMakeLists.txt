cmake_minimum_required(VERSION 3.29)
project(soccer_boots_bayes_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(soccer_boots_bayes_project main.cpp
        reader/SoccerPlayerBootsDataCsvReader.cpp
        reader/SoccerPlayerBootsDataCsvReader.h
        data/SoccerPlayerBoots.cpp
        data/SoccerPlayerBoots.h
        model/SoccerBootsBayesianTrainer.cpp
        model/SoccerBootsBayesianTrainer.h
        model/SoccerBootsRecommender.cpp
        model/SoccerBootsRecommender.h)

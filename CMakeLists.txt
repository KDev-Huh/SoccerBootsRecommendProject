cmake_minimum_required(VERSION 3.29)
project(soccer_boots_bayes_project)

set(CMAKE_CXX_STANDARD 20)

# Project include directories
include_directories(${CMAKE_SOURCE_DIR})

# Crow include 디렉토리 추가
include_directories(${CMAKE_SOURCE_DIR}/Crow/include)

# Find ASIO (installed via Homebrew)
find_path(ASIO_INCLUDE_DIR asio.hpp HINTS /opt/homebrew/include /usr/local/include)
if(ASIO_INCLUDE_DIR)
    include_directories(${ASIO_INCLUDE_DIR})
endif()

# Crow에서 필요한 threads 라이브러리 찾기
find_package(Threads REQUIRED)

add_executable(soccer_boots_bayes_project main.cpp
        reader/SoccerPlayerBootsDataCsvReader.cpp
        reader/SoccerPlayerBootsDataCsvReader.h
        data/SoccerPlayerBoots.cpp
        data/SoccerPlayerBoots.h
        model/SoccerBootsBayesianTrainer.cpp
        model/SoccerBootsBayesianTrainer.h
        model/SoccerBootsRecommender.cpp
        model/SoccerBootsRecommender.h)

# threads 라이브러리 링크
target_link_libraries(soccer_boots_bayes_project Threads::Threads)
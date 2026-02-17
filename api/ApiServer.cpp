//
// Created by 허온 on 2026. 2. 17..
//

#include "ApiServer.h"

ApiServer::ApiServer(int port)
    : port_(port) {}

crow::SimpleApp& ApiServer::getApp() {
    return app_;
}

void ApiServer::run() {
    app_.port(port_).multithreaded().run();
}

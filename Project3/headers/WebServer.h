#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer
{
public:
    WebServer();
    bool isRunning();
    void assignRequest(Request request);
    void tick();
    Request getCurrRequest();

private:
    bool running;
    int time_remaining;
    Request curr_request;
};

#endif
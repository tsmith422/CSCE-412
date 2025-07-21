#include "../headers/WebServer.h"

WebServer::WebServer()
    : running(false), time_remaining(0),
      curr_request("", "", 0), processed_count(0) {}

void WebServer::assignRequest(Request req)
{
    curr_request = req;
    time_remaining = req.time;
    running = true;
}

void WebServer::tick()
{
    if (running)
    {
        time_remaining--;
        if (time_remaining <= 0)
        {
            running = false;
            processed_count++;
        }
    }
}

bool WebServer::isRunning()
{
    return running;
}

Request WebServer::getCurrRequest()
{
    return curr_request;
}

int WebServer::getProcessedRequestCount()
{
    return processed_count;
}

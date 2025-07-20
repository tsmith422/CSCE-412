#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <vector>

class LoadBalancer
{
public:
    LoadBalancer();
    void distributeLoad();

private:
    std::vector<WebServer> servers;
    RequestQueue requestQueue;
    int time;
};

#endif
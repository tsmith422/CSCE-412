#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <fstream>
#include <vector>

class LoadBalancer
{
public:
    LoadBalancer(int num_servers);
    ~LoadBalancer();

    void addRequest(Request request);
    void assignRequests();
    void tick();
    void simulate(int total_cycles, int request_chance, std::ostream &logfile);
    int getQueueSize();
    int getServerCount();
    int getBusyServerCount();
    int getTotalProcessedRequests();

private:
    std::vector<WebServer *> servers;
    RequestQueue requestQueue;
    int time;
};

#endif
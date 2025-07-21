#include "../headers/LoadBalancer.h"
#include "../headers/utility.h"
#include <iostream>
using namespace std;

LoadBalancer::LoadBalancer(int num_servers) : time(0)
{
    for (int i = 0; i < num_servers; ++i)
    {
        servers.push_back(new WebServer());
    }
}

LoadBalancer::~LoadBalancer()
{
    for (WebServer *server : servers)
    {
        delete server;
    }
}

void LoadBalancer::addRequest(Request req)
{
    requestQueue.enqueue(req);
}

void LoadBalancer::assignRequests()
{
    for (WebServer *server : servers)
    {
        if (!server->isRunning() && !requestQueue.isEmpty())
        {
            server->assignRequest(requestQueue.dequeue());
        }
    }
}

void LoadBalancer::tick()
{
    for (WebServer *server : servers)
    {
        server->tick();
    }
    time++;
}

void LoadBalancer::simulate(int total_cycles, int new_request_chance)
{
    for (int cycle = 0; cycle < total_cycles; ++cycle)
    {
        assignRequests();
        tick();

        if ((rand() % 100) < new_request_chance)
        {
            addRequest(generateRandomRequest());
            // cout << "New request added at cycle " << cycle << endl;
        }

        if (cycle % 500 == 0)
        {
            cout << "Cycle: " << cycle
                 << " | Queue Size: " << getQueueSize()
                 << " | Active Servers: " << getServerCount()
                 << endl;
        }
    }
}

int LoadBalancer::getQueueSize()
{
    return requestQueue.size();
}

int LoadBalancer::getServerCount()
{
    return servers.size();
}

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

void LoadBalancer::simulate(int total_cycles, int new_request_chance, ostream &logfile)
{
    logfile << "Cycle | Queue Size | Busy Servers | Total Servers | Total Processed Requests\n";
    logfile << "----------------------------------------------------------------------\n";

    // Simulate with logging every 500 cycles
    for (int cycle = 0; cycle <= total_cycles; ++cycle)
    {
        assignRequests();
        tick();

        if ((rand() % 100) < new_request_chance)
        {
            addRequest(generateRandomRequest());
        }

        if (cycle % 500 == 0)
        {
            logfile << cycle << " | "
                    << getQueueSize() << " | "
                    << getBusyServerCount() << " | "
                    << getServerCount() << " | "
                    << getTotalProcessedRequests() << "\n";
        }
    }

    logfile << "\nSimulation complete.\n";
    logfile << "Final Queue Size: " << getQueueSize() << "\n";
    logfile << "Total Requests Processed: " << getTotalProcessedRequests() << "\n";
}

int LoadBalancer::getQueueSize()
{
    return requestQueue.size();
}

int LoadBalancer::getServerCount()
{
    return servers.size();
}

int LoadBalancer::getBusyServerCount()
{
    int busy_count = 0;
    for (WebServer *server : servers)
    {
        if (server->isRunning())
        {
            busy_count++;
        }
    }
    return busy_count;
}

int LoadBalancer::getTotalProcessedRequests()
{
    int total = 0;
    for (WebServer *server : servers)
    {
        total += server->getProcessedRequestCount();
    }
    return total;
}

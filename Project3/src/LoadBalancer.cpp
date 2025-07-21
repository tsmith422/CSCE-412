#include "../headers/LoadBalancer.h"
#include "../headers/utility.h"
#include <iostream>
using namespace std;

/**
 * @brief Constructs a LoadBalancer with a given number of web servers.
 * @param num_servers The number of web servers to create.
 */
LoadBalancer::LoadBalancer(int num_servers) : time(0)
{
    for (int i = 0; i < num_servers; ++i)
    {
        servers.push_back(new WebServer());
    }
}

/**
 * @brief Destructor that cleans up dynamically allocated web servers.
 */
LoadBalancer::~LoadBalancer()
{
    for (WebServer *server : servers)
    {
        delete server;
    }
}

/**
 * @brief Adds a new request to the request queue.
 * @param req The request to add.
 */
void LoadBalancer::addRequest(Request req)
{
    requestQueue.enqueue(req);
}

/**
 * @brief Assigns available servers with requests from the queue.
 *
 * Each idle server is assigned the next available request in the queue.
 */
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

/**
 * @brief Advances the simulation by one clock cycle.
 *
 * Calls tick() on all servers and increments the internal simulation time.
 */
void LoadBalancer::tick()
{
    for (WebServer *server : servers)
    {
        server->tick();
    }
    time++;
}

/**
 * @brief Runs the full load balancer simulation for a given number of cycles.
 *
 * Simulates server processing, request assignment, and random new request generation.
 * Logs the system state every 500 cycles to the provided log stream.
 *
 * @param total_cycles The total number of clock cycles to simulate.
 * @param new_request_chance The percentage chance (0-100) of a new request arriving each cycle.
 * @param logfile The output stream where simulation logs will be written.
 */
void LoadBalancer::simulate(int total_cycles, int new_request_chance, ostream &logfile)
{
    logfile << "Cycle | Queue Size | Busy Servers | Total Servers | Total Processed Requests\n";
    logfile << "----------------------------------------------------------------------\n";

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

/**
 * @brief Gets the current size of the request queue.
 * @return The number of requests waiting in the queue.
 */
int LoadBalancer::getQueueSize()
{
    return requestQueue.size();
}

/**
 * @brief Gets the total number of web servers managed by this load balancer.
 * @return The number of web servers.
 */
int LoadBalancer::getServerCount()
{
    return servers.size();
}

/**
 * @brief Gets the number of currently busy (processing) web servers.
 * @return The number of busy servers.
 */
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

/**
 * @brief Gets the total number of requests processed by all web servers.
 * @return The cumulative number of processed requests.
 */
int LoadBalancer::getTotalProcessedRequests()
{
    int total = 0;
    for (WebServer *server : servers)
    {
        total += server->getProcessedRequestCount();
    }
    return total;
}

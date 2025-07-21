/**
 * @file LoadBalancer.cpp
 * @brief Implements the LoadBalancer class for managing request distribution and server scaling.
 */

#include "../headers/LoadBalancer.h"
#include "../headers/utility.h"
#include <iostream>
using namespace std;

/**
 * @brief Constructs the LoadBalancer with the specified number of web servers.
 * @param num_servers Number of web servers to initialize.
 */
LoadBalancer::LoadBalancer(int num_servers) : time(0), rejected_requests(0)
{
    for (int i = 0; i < num_servers; ++i)
    {
        servers.push_back(new WebServer());
    }
}

/**
 * @brief Destructor. Cleans up all dynamically allocated web servers.
 */
LoadBalancer::~LoadBalancer()
{
    for (WebServer *server : servers)
    {
        delete server;
    }
}

/**
 * @brief Adds a new request to the queue if space is available.
 *        Increments rejected_requests counter if the queue is full.
 * @param req The Request to add.
 */
void LoadBalancer::addRequest(Request req)
{

    if (requestQueue.size() > 1000)
    {
        rejected_requests++;
    }
    else
    {
        requestQueue.enqueue(req);
    }
}

/**
 * @brief Assigns queued requests to idle web servers.
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
 * @brief Advances the simulation by one clock cycle by ticking all servers and incrementing internal time.
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
 * @brief Runs the simulation for total_cycles, generating new requests based on new_request_chance.
 *        Scales servers dynamically and logs status every 500 cycles.
 * @param total_cycles Number of simulation cycles.
 * @param new_request_chance Percentage chance (0-100) of generating a new request each cycle.
 * @param logfile Output stream to write simulation logs.
 */
void LoadBalancer::simulate(int total_cycles, int new_request_chance, ostream &logfile)
{
    logfile << "Starting Queue Size: " << getQueueSize() << "\n\n";
    logfile << "Cycle | Queue Size | Active Servers | Inactive Servers | Total Servers | Rejected Requests | Processed Requests\n";
    logfile << "----------------------------------------------------------------------------------------------------------------\n";

    for (int cycle = 0; cycle <= total_cycles; ++cycle)
    {
        assignRequests();
        tick();
        scaleServers();

        if ((rand() % 100) < new_request_chance)
        {
            addRequest(generateRandomRequest());
        }

        if (cycle % 250 == 0)
        {
            logfile << cycle << " | "
                    << getQueueSize() << " | "
                    << getBusyServerCount() << " | "
                    << getInactiveServerCount() << " | "
                    << getServerCount() << " | "
                    << getRejectedRequests() << " | "
                    << getTotalProcessedRequests() << "\n";
        }
    }

    logfile << "\nSimulation complete.\n";
    logfile << "Final Queue Size: " << getQueueSize() << "\n";
    logfile << "Total Requests Processed: " << getTotalProcessedRequests() << "\n";
    logfile << "Range for Task Times: [10, 19]\n";
}

/**
 * @brief Returns the current number of requests waiting in the queue.
 * @return Size of the request queue.
 */
int LoadBalancer::getQueueSize()
{
    return requestQueue.size();
}

/**
 * @brief Returns the total number of web servers.
 * @return Number of servers managed.
 */
int LoadBalancer::getServerCount()
{
    return servers.size();
}

/**
 * @brief Counts how many servers are currently processing requests.
 * @return Number of busy servers.
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
 * @brief Returns total requests processed by all servers.
 * @return Total number of processed requests.
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

/**
 * @brief Returns the total number of rejected requests due to queue overflow.
 * @return Number of rejected requests.
 */
int LoadBalancer::getRejectedRequests()
{
    return rejected_requests;
}

/**
 * @brief Calculates the number of inactive (idle) servers.
 * @return Number of inactive servers.
 */
int LoadBalancer::getInactiveServerCount()
{
    return getServerCount() - getBusyServerCount();
}

/**
 * @brief Dynamically adds or removes servers based on current queue size to maintain balance.
 *        Adds a server if queue size is above 500 and under max server limit (20).
 *        Removes an idle server if queue size below 100 and above min server limit (5).
 */
void LoadBalancer::scaleServers()
{
    int queue_size = getQueueSize();

    if (queue_size > 500 && servers.size() < 20)
    {
        servers.push_back(new WebServer());
    }
    else if (queue_size < 100 && servers.size() > 5)
    {
        for (auto it = servers.begin(); it != servers.end(); ++it)
        {
            if (!(*it)->isRunning())
            {
                delete *it;
                servers.erase(it);
                break;
            }
        }
    }
}

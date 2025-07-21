/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class which manages a queue of requests and a pool of web servers.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <fstream>
#include <vector>

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes incoming web requests to multiple web servers.
 *
 * The LoadBalancer manages a queue of incoming requests, a dynamic pool of web servers,
 * and tracks statistics such as rejected requests and processed requests.
 * It supports scaling the number of servers based on the load.
 */
class LoadBalancer
{
public:
    /**
     * @brief Constructs a LoadBalancer with a specified number of web servers.
     * @param num_servers The initial number of web servers to create.
     */
    LoadBalancer(int num_servers);

    /**
     * @brief Destructor. Cleans up dynamically allocated web servers.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a new request to the request queue.
     *        If the queue is full, increments rejected request count instead.
     * @param request The Request object to be added.
     */
    void addRequest(Request request);

    /**
     * @brief Assigns queued requests to idle web servers.
     */
    void assignRequests();

    /**
     * @brief Advances the simulation by one clock cycle.
     *        Updates all servers and increments internal time.
     */
    void tick();

    /**
     * @brief Runs the simulation for a given number of clock cycles.
     *        Randomly adds new requests based on request chance.
     *        Logs status to the provided output stream at intervals.
     * @param total_cycles Total number of cycles to simulate.
     * @param request_chance Percentage chance of generating a new request each cycle.
     * @param logfile Output stream to write simulation logs.
     */
    void simulate(int total_cycles, int request_chance, std::ostream &logfile);

    /**
     * @brief Gets the current size of the request queue.
     * @return Number of requests waiting in the queue.
     */
    int getQueueSize();

    /**
     * @brief Gets the current number of web servers.
     * @return Total number of web servers.
     */
    int getServerCount();

    /**
     * @brief Counts how many servers are currently processing requests.
     * @return Number of busy (active) servers.
     */
    int getBusyServerCount();

    /**
     * @brief Gets the total number of requests processed by all servers.
     * @return Total processed request count.
     */
    int getTotalProcessedRequests();

    /**
     * @brief Gets the total number of rejected requests due to queue overflow.
     * @return Number of rejected requests.
     */
    int getRejectedRequests();

    /**
     * @brief Calculates how many servers are currently idle (not processing).
     * @return Number of inactive servers.
     */
    int getInactiveServerCount();

    /**
     * @brief Dynamically adjusts the number of web servers based on load conditions.
     *        Adds or removes servers to maintain balanced capacity.
     */
    void scaleServers();

private:
    std::vector<WebServer *> servers;  ///< Vector holding pointers to the managed web servers.
    RequestQueue requestQueue;          ///< Queue of incoming requests awaiting processing.
    int time;                          ///< Simulation clock time.
    int rejected_requests;         ///< Count of requests rejected due to full queue.
};

#endif

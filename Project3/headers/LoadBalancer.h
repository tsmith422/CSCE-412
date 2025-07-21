/**
 * @file LoadBalancer.h
 * @brief Declares the LoadBalancer class responsible for managing web servers and requests.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "WebServer.h"
#include "RequestQueue.h"
#include <fstream>
#include <vector>

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes requests to multiple web servers.
 *
 * The LoadBalancer manages a queue of incoming requests and a pool of web servers.
 * It handles request assignment, ticking server time, and simulating system behavior
 * over multiple clock cycles with logging support.
 */
class LoadBalancer
{
public:
    /**
     * @brief Constructs a LoadBalancer with a given number of web servers.
     * @param num_servers The number of web servers to create.
     */
    LoadBalancer(int num_servers);

    /**
     * @brief Destructor that cleans up dynamically allocated web servers.
     */
    ~LoadBalancer();

    /**
     * @brief Adds a new request to the request queue.
     * @param request The request to add.
     */
    void addRequest(Request request);

    /**
     * @brief Assigns requests from the queue to available web servers.
     */
    void assignRequests();

    /**
     * @brief Advances the simulation by one clock cycle.
     *
     * Processes time ticks for all web servers and increments the internal clock.
     */
    void tick();

    /**
     * @brief Runs the simulation for a specified number of cycles with logging.
     * @param total_cycles The total number of cycles to simulate.
     * @param request_chance The percentage chance (0-100) of a new request per cycle.
     * @param logfile The output stream for writing simulation logs.
     */
    void simulate(int total_cycles, int request_chance, std::ostream &logfile);

    /**
     * @brief Gets the current size of the request queue.
     * @return The number of requests waiting in the queue.
     */
    int getQueueSize();

    /**
     * @brief Gets the total number of web servers managed by the load balancer.
     * @return The number of web servers.
     */
    int getServerCount();

    /**
     * @brief Gets the number of servers currently processing requests.
     * @return The number of busy servers.
     */
    int getBusyServerCount();

    /**
     * @brief Gets the total number of processed requests across all servers.
     * @return The cumulative count of processed requests.
     */
    int getTotalProcessedRequests();

private:
    std::vector<WebServer *> servers; ///< Collection of managed web servers.
    RequestQueue requestQueue;        ///< Queue of incoming requests.
    int time;                         ///< Internal clock counter.
};

#endif

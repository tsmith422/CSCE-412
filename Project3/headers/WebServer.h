/**
 * @file WebServer.h
 * @brief Declares the WebServer class that simulates processing web requests.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Represents a single web server that processes one request at a time.
 *
 * The WebServer class handles request assignment, processing time tracking,
 * and counting the number of processed requests.
 */
class WebServer
{
public:
    /**
     * @brief Constructs a WebServer in an idle state.
     */
    WebServer();

    /**
     * @brief Checks if the server is currently processing a request.
     * @return True if the server is running (processing a request), false otherwise.
     */
    bool isRunning();

    /**
     * @brief Assigns a request to the server for processing.
     * @param request The Request to assign.
     */
    void assignRequest(Request request);

    /**
     * @brief Advances the server by one clock cycle.
     *
     * Decrements the remaining processing time. Marks the server as idle when complete.
     */
    void tick();

    /**
     * @brief Gets the current request being processed by the server.
     * @return The current Request assigned to the server.
     */
    Request getCurrRequest();

    /**
     * @brief Gets the total number of requests processed by this server.
     * @return The count of processed requests.
     */
    int getProcessedRequestCount();

private:
    bool running;         ///< Indicates whether the server is actively processing a request.
    int time_remaining;   ///< Time remaining to complete the current request.
    Request curr_request; ///< The current request being processed.
    int processed_count;  ///< Total number of processed requests.
};

#endif

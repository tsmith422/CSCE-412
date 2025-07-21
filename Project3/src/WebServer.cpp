/**
 * @file WebServer.cpp
 * @brief Implements the WebServer class that simulates individual web server behavior.
 */

#include "../headers/WebServer.h"

/**
 * @brief Constructs a WebServer object with default values.
 *
 * The server starts in an idle state with no active request.
 */
WebServer::WebServer()
    : running(false), time_remaining(0),
      curr_request("", "", 0), processed_count(0) {}

/**
 * @brief Assigns a new request to the web server.
 *
 * Sets the current request, initializes the time remaining, and marks the server as running.
 *
 * @param req The Request object to be processed by the server.
 */
void WebServer::assignRequest(Request req)
{
    curr_request = req;
    time_remaining = req.time;
    running = true;
}

/**
 * @brief Advances the server by one clock cycle.
 *
 * Decrements the time remaining on the current request.
 * If the request is completed, the server becomes idle and increments its processed count.
 */
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

/**
 * @brief Checks if the server is currently processing a request.
 * @return True if the server is running, false otherwise.
 */
bool WebServer::isRunning()
{
    return running;
}

/**
 * @brief Gets the current request assigned to the server.
 * @return The current Request object.
 */
Request WebServer::getCurrRequest()
{
    return curr_request;
}

/**
 * @brief Gets the total number of requests processed by this server.
 * @return The number of processed requests.
 */
int WebServer::getProcessedRequestCount()
{
    return processed_count;
}

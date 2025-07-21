/**
 * @file RequestQueue.h
 * @brief Declares the RequestQueue class for managing a queue of web requests.
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

/**
 * @class RequestQueue
 * @brief A wrapper around the standard queue to manage web requests.
 *
 * Provides enqueue, dequeue, and utility functions for handling a queue of Request objects.
 */
class RequestQueue
{
public:
    /**
     * @brief Default constructor for RequestQueue.
     */
    RequestQueue();

    /**
     * @brief Adds a request to the end of the queue.
     * @param request The Request object to add.
     */
    void enqueue(Request request);

    /**
     * @brief Removes and returns the request at the front of the queue.
     * @return The Request object at the front of the queue.
     * @throws std::runtime_error if the queue is empty.
     */
    Request dequeue();

    /**
     * @brief Returns the request at the front of the queue without removing it.
     * @return The Request object at the front of the queue.
     * @throws std::runtime_error if the queue is empty.
     */
    Request front();

    /**
     * @brief Checks whether the queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty();

    /**
     * @brief Gets the number of requests in the queue.
     * @return The current size of the queue.
     */
    int size();

private:
    std::queue<Request> q; ///< The underlying queue storing Request objects.
};

#endif

/**
 * @file RequestQueue.cpp
 * @brief Implements the RequestQueue class for managing request queuing operations.
 *
 * Provides basic queue functionality for handling web requests in the load balancer system.
 */

#include "../headers/RequestQueue.h"
#include <stdexcept>

using namespace std;

/**
 * @brief Default constructor for RequestQueue.
 */
RequestQueue::RequestQueue() {}

/**
 * @brief Adds a request to the end of the queue.
 * @param req The Request to enqueue.
 */
void RequestQueue::enqueue(Request req)
{
    q.push(req);
}

/**
 * @brief Removes and returns the request at the front of the queue.
 * @return The Request at the front of the queue.
 * @throws std::runtime_error if the queue is empty.
 */
Request RequestQueue::dequeue()
{
    if (q.empty())
    {
        throw runtime_error("Queue is empty");
    }
    Request front = q.front();
    q.pop();
    return front;
}

/**
 * @brief Returns the request at the front of the queue without removing it.
 * @return The Request at the front of the queue.
 * @throws std::runtime_error if the queue is empty.
 */
Request RequestQueue::front()
{
    if (q.empty())
    {
        throw runtime_error("Queue is empty");
    }
    return q.front();
}

/**
 * @brief Checks whether the queue is empty.
 * @return True if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty()
{
    return q.empty();
}

/**
 * @brief Returns the number of requests currently in the queue.
 * @return The size of the queue.
 */
int RequestQueue::size()
{
    return q.size();
}

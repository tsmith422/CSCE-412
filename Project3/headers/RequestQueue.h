#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "Request.h"
#include <queue>

class RequestQueue
{
public:
    RequestQueue();
    void enqueue(Request request);
    Request dequeue();
    bool isEmpty();

private:
    std::queue<Request> q;
};

#endif
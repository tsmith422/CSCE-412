#include "../headers/RequestQueue.h"
#include <stdexcept>
using namespace std;

RequestQueue::RequestQueue() {}

void RequestQueue::enqueue(Request req)
{
    q.push(req);
}

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

Request RequestQueue::front()
{
    if (q.empty())
    {
        throw runtime_error("Queue is empty");
    }
    return q.front();
}

bool RequestQueue::isEmpty()
{
    return q.empty();
}

int RequestQueue::size()
{
    return q.size();
}
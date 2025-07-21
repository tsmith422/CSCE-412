#ifndef REQUEST_H
#define REQUEST_H

#include <string>

struct Request
{
    std::string ip_in;
    std::string ip_out;
    int time;

    Request(std::string ip_in, std::string ip_out, int time)
        : ip_in(ip_in), ip_out(ip_out), time(time) {}
};

#endif
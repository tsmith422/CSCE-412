/**
 * @file Request.h
 * @brief Defines the Request struct used to represent a web request.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @struct Request
 * @brief Represents a web request with input/output IP addresses and processing time.
 *
 * The Request struct holds the information needed by the load balancer and web servers
 * to process a request in the simulation.
 */
struct Request
{
    std::string ip_in;  ///< The IP address of the requester.
    std::string ip_out; ///< The destination IP address for the response.
    int time;           ///< The amount of time required to process the request.

    /**
     * @brief Constructs a Request with specified IP addresses and processing time.
     * @param ip_in The input IP address.
     * @param ip_out The output IP address.
     * @param time The time required to process the request.
     */
    Request(std::string ip_in, std::string ip_out, int time)
        : ip_in(ip_in), ip_out(ip_out), time(time) {}
};

#endif

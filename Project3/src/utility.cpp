/**
 * @file utility.cpp
 * @brief Contains utility functions for generating random IP addresses and requests.
 */

#include "../headers/utility.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

/**
 * @brief Generates a random IPv4 address as a string.
 *
 * The IP address is in the format "X.X.X.X", where each X is a random integer between 0 and 255.
 *
 * @return A randomly generated IPv4 address.
 */
std::string generateRandomIP()
{
    std::stringstream ss;
    ss << (rand() % 256) << "."
       << (rand() % 256) << "."
       << (rand() % 256) << "."
       << (rand() % 256);
    return ss.str();
}

/**
 * @brief Generates a random Request object with random IP addresses and processing time.
 *
 * - Generates random inbound and outbound IP addresses.
 * - Sets the request time to a random value between 10 and 19 (inclusive).
 *
 * @return A randomly generated Request object.
 */
Request generateRandomRequest()
{
    std::string ip_in = generateRandomIP();
    std::string ip_out = generateRandomIP();
    int time = (rand() % 10) + 10;
    return Request(ip_in, ip_out, time);
}

/**
 * @file utility.h
 * @brief Declares utility functions for generating random IP addresses and web requests.
 */

#ifndef UTILITY_H
#define UTILITY_H

#include "Request.h"
#include <string>

/**
 * @brief Generates a random IPv4 address in string format.
 * @return A string representing a randomly generated IPv4 address.
 */
std::string generateRandomIP();

/**
 * @brief Generates a random web request with random IPs and processing time.
 * @return A Request object with randomized IP addresses and time.
 */
Request generateRandomRequest();

#endif

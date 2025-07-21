#include "../headers/utility.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

std::string generateRandomIP()
{
    std::stringstream ss;
    ss << (rand() % 256) << "."
       << (rand() % 256) << "."
       << (rand() % 256) << "."
       << (rand() % 256);
    return ss.str();
}

Request generateRandomRequest()
{
    std::string ip_in = generateRandomIP();
    std::string ip_out = generateRandomIP();
    int time = (rand() % 10) + 10;
    return Request(ip_in, ip_out, time);
}

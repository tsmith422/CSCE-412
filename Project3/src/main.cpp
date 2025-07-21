/**
 * @file main.cpp
 * @brief Entry point for the Load Balancer simulation.
 *
 * This program initializes the load balancer, creates a queue of initial requests,
 * and runs the simulation for a user-defined number of cycles.
 * The simulation results are logged to a file in the docs directory.
 */

#include <iostream>
#include <fstream>
#include "../headers/LoadBalancer.h"
#include "../headers/utility.h"

using namespace std;

/**
 * @brief Main function that drives the Load Balancer simulation.
 *
 * - Prompts the user for the number of web servers and total simulation cycles.
 * - Initializes the load balancer and fills the request queue.
 * - Runs the simulation with a fixed chance of new requests per cycle.
 * - Logs the simulation output to docs/simulation_log.txt.
 *
 * @return int Returns 0 on successful execution, 1 if the log file cannot be opened.
 */
int main()
{
    srand(time(0)); ///< Seed the random number generator.

    int num_servers;
    int total_cycles;
    int new_request_chance = 65; ///< Percentage chance (0-100) of a new request each cycle.

    cout << "Enter number of web servers: ";
    cin >> num_servers;

    cout << "Enter total simulation clock cycles: ";
    cin >> total_cycles;

    LoadBalancer lb(num_servers);

    int initial_queue_size = num_servers * 100;
    for (int i = 0; i < initial_queue_size; ++i)
    {
        lb.addRequest(generateRandomRequest());
    }

    cout << "\nInitial queue of " << initial_queue_size << " requests created.\n";
    cout << "Starting simulation for " << total_cycles << " cycles...\n\n";

    ofstream logfile("docs/simulation_log.txt");
    if (!logfile)
    {
        cerr << "Error opening log file.\n";
        return 1;
    }

    lb.simulate(total_cycles, new_request_chance, logfile);

    cout << "Simulation complete. Log written to ../docs/simulation_log.txt\n";
    logfile.close();

    return 0;
}

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "../headers/LoadBalancer.h"
#include "../headers/utility.h"
using namespace std;

int main()
{
    srand(time(0));

    int num_servers;
    int total_cycles;
    int new_request_chance = 65;

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
    // Open log file in ../docs folder
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
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char *argv[])
{
    double voltage = 0.0, current_voltage = 0.0;
    char buffer[128];

    while (1)
    {
        // Open Pipe to get output
        FILE *pipe = popen("echo \"scale=2; $(rdmsr 0x198 -u --bitfield 47:32)/8192\" | bc", "r");

        // Check if Pipe is open
        if (!pipe)
        {
            std::cout << "Error executing command" << std::endl;
            // return -1;
        }
        else
        {
            // Read from Pipe
            while (!feof(pipe))
            {
                fgets(buffer, sizeof buffer, pipe);
            }

            current_voltage = atof(buffer);
            if (current_voltage > voltage)
            {
                std::cout << "Current Max Core Voltage: " << current_voltage << "V" << std::endl;
                voltage = current_voltage;
            }
        }
        pclose(pipe);

        // std::cout << buffer << std::endl;

        // Wait for one second
        sleep(1);
    }
    return 0;
}
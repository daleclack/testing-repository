#include "CoreVolt.h"
#include <cstdio>
#include <cstdlib>

static double voltage = 0.0;
double get_core_voltage(char *current_voltage_str, char *max_voltage_str)
{
    double current_voltage = 0.0;
    char buffer[10];

    while (1)
    {
        // Open Pipe to get output
        FILE *pipe = popen("echo \"scale=2; $(rdmsr 0x198 -u --bitfield 47:32)/8192\" | bc", "r");

        // Check if Pipe is open
        if (pipe)
        {
            // Read from Pipe
            while (!feof(pipe))
            {
                fgets(buffer, sizeof(buffer) - 1, pipe);
            }

            // Update the max voltage
            current_voltage = atof(buffer);
            snprintf(current_voltage_str, sizeof(current_voltage_str) - 1, "%0.2fV", current_voltage);
            if (current_voltage > voltage)
            {
                voltage = current_voltage;
            }
            snprintf(max_voltage_str, sizeof(max_voltage_str) - 1, "%0.2fV", voltage);
        }
        pclose(pipe);
        return current_voltage;
    }
}

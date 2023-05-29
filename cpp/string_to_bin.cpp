#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char **argv)
{
    char str[70], tmp2[8];
    std::cin >> str; // Input the sentence

    std::fstream outfile;
    outfile.open("20comm_exp1_bs.dat", std::ios::out); // Open the file

    for (int i = 0; i < strlen(str); i++)
    {
        int temp = str[i];
        for (int j = 8; j > 0; j--)
        { // Convert ASCII to 8 bit binary
            tmp2[j - 1] = temp % 2 + '0';
            temp /= 2;
        }
        for (int j = 0; j < 8; j++)
        { // Output the binary
            std::cout << tmp2[j] << " ";
            if (outfile.is_open())
            { // Output the data to file
                outfile << tmp2[j] << " ";
            }
        }
    }
    outfile << std::endl;
    outfile.close(); // Close the file, the content will be saved
    return 0;
}
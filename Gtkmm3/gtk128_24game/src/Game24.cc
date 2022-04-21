// Reference code: https://www.jb51.net/article/182079.htm
#include "Game24.hh"

// Generate a number in [begin,end]
static double randnum(int begin = 0, int end = 1)
{
    return rand() % (end - begin + 1) + begin;
}

// The Game Class
bool Game24::startgame(string user_result)
{
    bool winned = false;

    // Format result number
    if (user_result != "")
    {
        if (user_result.length() < (*(result_strings.begin())).length())
        {
            user_result = '(' + user_result + ')';
        }
    }

    std::cout << user_result << std::endl;

    // Check user input and the results
    if (count > 0)
    {
        for (std::vector<string>::iterator it = result_strings.begin(); it != result_strings.end(); it++)
        {
            if (*it == user_result)
            {
                std::cout << "Winned!" << std::endl;
                winned = true;
                break;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        if (user_result == "(None)")
        {
            winned = true;
        }
    }

    // If lost, output information
    if (!winned)
    {
        std::cout << "Lost" << std::endl;
    }

    return winned;
}

void Game24::getnumbers()
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        // Get Number and output
        number[i] = randnum(1, 13);
        // std::cout << number[i] << " ";

        // Process number to string for display
        switch ((int)number[i])
        {
        case 10:
            result[i] = "10";
            break;
        case 11:
            result[i] = "11";
            break;
        case 12:
            result[i] = "12";
            break;
        case 13:
            result[i] = "13";
            break;
        default:
            result[i] = '0' + number[i];
        }
    }
    // std::cout << std::endl;

    // Get the algorithm that can get the result
    F(n);
    // std::cout << "Has" << count << "Results" << std::endl;
    sprintf(numbers_char, "%d %d %d %d", (int)number[0], (int)number[1], (int)number[2], (int)number[3]);
}

void Game24::F(int n)
{
    // Calculate for three times
    if (n == 1)
    {
        if (number[0] == 24)
        {
            // std::cout << result[0] << std::endl;
            result_strings.push_back(result[0]);
            count++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double a, b;
            string x, y;

            // Save number
            a = number[i];
            b = number[j];
            number[j] = number[n - 1];

            // Save Result String
            x = result[i];
            y = result[j];
            result[j] = result[n - 1];

            // Add
            number[i] = a + b;
            result[i] = '(' + x + '+' + y + ')';
            F(n - 1);

            // Minus
            number[i] = a - b;
            result[i] = '(' + x + '-' + y + ')';
            F(n - 1);
            number[i] = b - a;
            result[i] = '(' + y + '-' + x + ')';
            F(n - 1);

            // multiply
            number[i] = a * b;
            result[i] = '(' + x + '*' + y + ')';
            F(n - 1);

            // divide
            if (b != 0)
            {
                number[i] = a / b;
                result[i] = '(' + x + '/' + y + ')';
                F(n - 1);
            }

            if (a != 0)
            {
                number[i] = b / a;
                result[i] = '(' + y + '/' + x + ')';
                F(n - 1);
            }

            // if the result is not 24, make the numbers back
            number[i] = a;
            number[j] = b;
            result[i] = x;
            result[j] = y;
        }
    }
}

// int main(int argc, char **argv)
// {
//     Game24 game1;
//     game1.startgame();
//     return 0;
// }

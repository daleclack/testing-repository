// Reference code: https://www.jb51.net/article/182079.htm
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

typedef std::string string;

// Generate a number in [begin,end]
static double randnum(int begin = 0, int end = 1)
{
    return rand() % (end - begin + 1) + begin;
}

// The Game Class
class Game24
{
public:
    Game24() {}

    void startgame()
    {
        bool winned = false;
        string user_result;
        getnumbers();
        std::cin >> user_result;

        // Format result number
        if(user_result[user_result.length()] != ')' || user_result[0] != '('){
            user_result = '(' + user_result + ')';
        }

        // Check user input and the results
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

        // If lost, output information
        if(!winned){
            std::cout<<"Lost"<<std::endl;
        }
    }

    void getnumbers()
    {
        srand(time(NULL));
        for (int i = 0; i < n; i++)
        {
            // Get Number and output
            number[i] = randnum(1, 13);
            std::cout << number[i] << " ";

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
        std::cout << std::endl;

        // Get the algorithm that can get the result
        F(n);
        std::cout << "Has" << count << "Results" << std::endl;
    }

private:
    int n = 4;                           // Flag of third calculate
    double number[4] = {0};              // Numbers
    char oper[4] = {'+', '-', '*', '/'}; // operators
    string result[4];
    int count = 0;

    std::vector<std::string> result_strings;

    void F(int n)
    {
        // Calculate for three times
        if (n == 1)
        {
            if (number[0] == 24)
            {
                //std::cout << result[0] << std::endl;
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
};

int main(int argc, char **argv)
{
    Game24 game1;
    game1.startgame();
    return 0;
}

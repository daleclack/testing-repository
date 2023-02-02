#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../toml/toml.hpp"
using namespace std::string_view_literals;

// Function pointer
typedef void(*pfun)();

void save_toml_file()
{
    static constexpr std::string_view some_toml = R"(
        [main]
        width = 1280
        height = 720

        [others]
        backgrounds = ["test1.png", "test2.png", "test3.png"]
    )"sv;

    try
    {
        // parse directly from a string view:
        toml::table tbl = toml::parse(some_toml);
        std::cout << tbl << "\n";

        // Save data to a file
        std::fstream outfile;
        outfile.open("config.toml", std::ios_base::out);
        if (outfile.is_open())
        {
            outfile << tbl;
        }
        outfile.close();

        // // parse from a string stream:
        // {
        //     std::stringstream ss{ std::string{ some_toml } };
        //     toml::table tbl = toml::parse(ss);
        //     std::cout << tbl << "\n";
        // }
    }
    catch (const toml::parse_error &err)
    {
        std::cerr << "Parsing failed:\n"
                  << err << "\n";
        return;
    }
}

void read_toml_file()
{
    std::fstream toml_file;
    toml_file.open("config.toml", std::ios_base::in);
    if(toml_file.is_open()){
        toml::table tbl = toml::parse(toml_file);
        std::cout << tbl["main"]["width"] << std::endl;
        std::cout << tbl["main"]["height"] << std::endl;
        auto test1 = tbl["others"]["backgrounds"][0].as_string()->get();
        std::cout << test1 << std::endl;
    }
    toml_file.close();
}

int main()
{
    pfun funcs[] = {save_toml_file, read_toml_file};
    // Input mode
    int mode;
    std::cin >> mode;

    // Execute function
    funcs[mode]();

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "../toml/toml.hpp"
using namespace std::string_view_literals;

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

int main()
{
    save_toml_file();

    return 0;
}
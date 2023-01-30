/*
A test for json library from nlohmann,
the json object will be a data of the json file
2023/1/29 dale clack
*/
#include "../../json_nlohmann/json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

// Function pointer
typedef void (*funcs)();

void read_json_file()
{
}

void create_json_file()
{
    // Create json data
    json data = json::parse(R"({
        "error": {
            "code": 101,
            "message": "operation failed!"
        },
        "result": {
            "backgrounds": ["test1.png", "test2.png", "test3.png"]
        },
        "data2": {}
	})");

    // Create json object for a key
    json data2 = json::parse(R"({
        "error": {
            "code": 101,
            "message": "operation failed!"
        },
        "result": {
            "backgrounds": ["test1.png", "test2.png", "test3.png"]
        },
        "data2": {}
	})");

    data["data2"] = data2;
    // auto data2 = data["data2"];
    // std::cout << data2 << std::endl;

    // Save data to a json file
    std::fstream outfile;
    outfile.open("test.json", std::ios_base::out);
    if (outfile.is_open())
    {
        outfile << data;
    }
    outfile.close();
}

int main()
{
    create_json_file();
    return 0;
}

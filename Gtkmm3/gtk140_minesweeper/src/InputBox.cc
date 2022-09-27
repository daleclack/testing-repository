#include <fstream>
#include "InputBox.hh"

InputBox::InputBox(){
    main_label.set_label("Input your name");
}

void InputBox::read_json_file(){
    // Try to read json data firstly
    std::fstream json_file;
    json_file.open("scores.json", std::ios_base::in);
    if(json_file.is_open()){
        json data = json::parse(json_file);
        scores_map = data["scores"];
    }
    json_file.close();
}

void InputBox::on_response(int response_id){
    // Put the data to a map container
    std::map<std::string, times_map> outdata;
    outdata["scores"] = scores_map;

    // Output data to json file
    std::fstream outfile;
    outfile.open("scores.json");
    json data = json::parse(outdata);
    if(outfile.is_open()){
        outfile << data;
    }
    outfile.close();
}

#include <fstream>
#include "InputBox.hh"
#include "jsonfile.hh"

InputBox::InputBox(){

}

void InputBox::on_response(int response_id){
    // Read the original json file
    std::fstream json_file;
    json_file.open("score.json");
    // Append data to the json file
    if(json_file.is_open()){
        
    }else{

    }
}

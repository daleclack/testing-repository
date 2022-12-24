/*
Read Contents from a file,
if read failed, a error message will shown,
and the program should not panic
built in 2022/12/23, dale clack
*/
use std::{fs, io};

fn main() {
    let mut filename1 = String::new();

    // Get file name to read
    io::stdin().read_line(&mut filename1).expect("Can't read line");
    let filename = filename1.trim();

    // Read content from file
    let file_str = match fs::read_to_string(filename){
        Ok(file_str) => file_str,
        Err(_) => String::from("default config"),
    };
    
    println!("The Content of file:\n{}", file_str);
}

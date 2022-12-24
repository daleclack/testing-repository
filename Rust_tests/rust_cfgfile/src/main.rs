use std::{fs, io, iter::Map};

fn main() {
    // Read the filename
    let mut filename = String::new();
    io::stdin()
        .read_line(&mut filename)
        .expect("Failed to read the line!");

    // Open the file
    let filename = filename.trim();
    let config_str = match fs::read_to_string(filename) {
        Ok(config_str) => config_str,
        Err(_) => String::from("-1"),
    };

    //println!("The content of file:{}", config_str);

    let v: Vec<&str> = config_str.splitn(3, '\n').collect();

    //println!("{}\n{}\n{}\n", v[0], v[1], v[2]);

    let longterm: Vec<&str> = v[0].split("=").collect();
    let stable: Vec<&str> = v[1].split("=").collect();
    let devel: Vec<&str> = v[2].split("=").collect();

    println!("{}:{}", longterm[0], longterm[1]);
    println!("{}:{}", stable[0], stable[1]);
    println!("{}:{}", devel[0], devel[1]);

    // Get a line of string
    //let config_map : Map<String, String>;
}

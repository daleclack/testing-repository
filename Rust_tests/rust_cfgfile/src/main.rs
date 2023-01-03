/*
Cfgfile example build with Rust,
the original cfgfile is built in Aug 10, 2021,
and this is the rust version
*/
use std::{
    fs::File,
    io::{self, BufRead, BufReader},
    process::exit,
};

fn main() {
    let funcs = [about, read_cfg, append_cfg, quit_app];

    println!("1.Read a config file;2.Append/Create a config to a config file;3.exit");
    // Read user selection
    let mut selection = String::new();
    loop {
        io::stdin()
            .read_line(&mut selection)
            .expect("Read Line Failed!");

        let selection = selection.trim();
        if selection == "0" || selection == "1" || selection == "2" || selection == "3" {
            let index: usize = selection.parse().unwrap();
            funcs[index]();
        } else {
            println!("Input is vaild!");
        }
    }

    // let v: Vec<&str> = config_str.split('\n').collect();

    // println!("The Length:{}", v.len());
    // for element in v.iter(){
    //     println!("{}", element);
    // }

    // let longterm: Vec<&str> = v[0].split("=").collect();
    // let stable: Vec<&str> = v[1].split("=").collect();
    // let devel: Vec<&str> = v[2].split("=").collect();

    // println!("{}:{}", longterm[0], longterm[1]);
    // println!("{}:{}", stable[0], stable[1]);
    // println!("{}:{}", devel[0], devel[1]);
}

fn read_cfg_file(filename: String, key: String, value: &mut String) {
    // let mut value = String::new();
    let key = key.trim();
    // Open the file
    // If the file not exist, create it
    let filename = filename.trim();
    let file1 = match File::open(filename) {
        Ok(file1) => file1,
        Err(_) => File::create(filename).unwrap(),
    };

    // Create a BufReader and read the file line by line
    let reader = BufReader::new(file1);
    for (_, line) in reader.lines().enumerate() {
        let line = line.unwrap();
        // Check the vaild config line
        let result = line.find("=");
        if result != None {
            // split the content line to key and value
            let key_value: Vec<&str> = line.split("=").collect();
            let key1 = key_value[0].clone();
            if key1 == key {
                // Push the value
                value.push_str(key_value[1]);
                return;
            }
        }
    }
}

fn about() {
    println!("The Cfgfile test for Rust by daleclack");
}

fn read_cfg() {
    println!("Read a config file!");
    // Read the filename
    println!("Input filename");
    let mut filename = String::new();
    io::stdin()
        .read_line(&mut filename)
        .expect("Failed to read the line!");

    // Read the value
    println!("Input Key");
    let mut key = String::new();
    io::stdin()
        .read_line(&mut key)
        .expect("Failed to read the line!");
    let key1 = key.clone();

    let mut value = String::new();
    read_cfg_file(filename, key, &mut value);
    println!("{}:{}", key1.trim(), value);
}

fn append_cfg() {
    println!("Append a config to cfgfile!");
    // Read the filename
    println!("Input filename");
    let mut filename = String::new();
    io::stdin()
        .read_line(&mut filename)
        .expect("Failed to read the line!");
}

fn quit_app() {
    exit(0);
}

use std::env;

fn main() {
    // Get executive path
    let args: Vec<String> = env::args().collect();
    let execpath: String = args[0].clone();

    // Handle the path string
    let exec_len: usize = 13;
    let length: usize;
    if cfg!(target_os = "windows") {
        length = execpath.len() - exec_len - 4;
    } else {
        length = execpath.len() - exec_len;
    }
    let path: &str = &execpath[0..length];

    // Print the path of executive
    println!("{}", path);
}

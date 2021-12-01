//Get Current directory(May cause error when handling directory name with chinese)

fn main(){
    let mut args = std::env::args();
    let path = args.nth(0).unwrap();
    let length = path.len();
    println!("{}",path);
    let path1 = &path[0..length-5];
    println!("{}",path1);
}
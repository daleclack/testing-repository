//Get Current directory(May cause error when handling directory name with chinese)
#[allow(dead_code)]

fn main(){
    let path = std::env::args().nth(0).unwrap();    //The arg[0] is the path of binary
    
    let length = path.len();    //Get length to handle the String

    let path1 = &path[0..length-5];        //Remove the binary name

    println!("{}",path1);
}
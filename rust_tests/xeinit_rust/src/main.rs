use rand::*;

fn main() {
    // Get The Value
    let value : u32 = random::<u32>();

    // OutPut the value
    println!("{} {}",value%2,value);
}

use chrono::prelude::*;

fn main() {
    let local = Local::now();
    println!("{} {} {}",local.year(),local.month(),local.day());
}

use chrono::*;
use std::{fs, str::FromStr};

fn main() {
    let version = String::from_str("7.2").unwrap();
    //version = fs::read_to_string("config").expect("Fail to Open the file!\n");
    
    // Get current time
    let now = Utc::now();
    let local = Local::now();
    let naive_time = NaiveDate::from_ymd(2017, 5, 19).and_hms(0, 0, 0);
    let build_version = DateTime::<Utc>::from_utc(naive_time, Utc);

    // Calculate the duration time
    let diff = now.signed_duration_since(build_version);

    // Just print it on terminal
    println!(
        "{}-{}-{} {}.{}",
        local.year(),
        local.month(),
        local.day(),
        version,
        diff.num_days()
    );

    // Get Content that output to a file
    let contents = local.year().to_string()
        + "-"
        + &local.month().to_string()
        + "-"
        + &local.day().to_string()
        + " "
        + &version
        + &diff.num_days().to_string()
        + "\n";

    // Print the content to a file
    fs::write("xe-7.x", contents).expect("Fail to write the file!\n");
}

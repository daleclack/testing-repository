use chrono::*;
use std::fs;

fn main() {
    
    // Get current time
    let now = Utc::now();
    let local = Local::now();
    let naive_time = NaiveDate::from_ymd(2017, 5, 19).and_hms(0, 0, 0);
    let build_version = DateTime::<Utc>::from_utc(naive_time, Utc);

    // Calculate the duration time
    let diff = now.signed_duration_since(build_version);

    // Just print it on terminal
    println!(
        "{}-{}-{} 7.2.{}",
        local.year(),
        local.month(),
        local.day(),
        diff.num_days()
    );

    // Get Content that output to a file
    let contents = local.year().to_string()
        + "-"
        + &local.month().to_string()
        + "-"
        + &local.day().to_string()
        + " "
        + "7.2."
        + &diff.num_days().to_string()
        + "\n";

    // Print the content to a file
    fs::write("xe-7.x", contents).expect("Fail to write the file!");
}

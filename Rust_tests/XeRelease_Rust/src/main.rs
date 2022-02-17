use chrono::*;
use std::io;

fn main() {
    // Pointer to functions
    let funcs = [about, longterm, stable, develop];

    // Information
    println!("Input Mode:");
    println!("1.longterm;2.stable;3.develop");

    // Input mode selection
    let mut string = String::new();
    io::stdin().read_line(&mut string).expect("Read Error!");
    let index: usize = string.trim().parse().unwrap();

    funcs[index]();
}

fn about() {
    println!("XeRelease Rust Edition by daleclack");
}

fn longterm() {
    // Get current time
    let now = Utc::now();
    let local = Local::now();
    let naive_time = NaiveDate::from_ymd(2019, 1, 11).and_hms(0, 0, 0);
    let other_dt = DateTime::<Utc>::from_utc(naive_time, Utc);

    // Calculate the duration time
    let diff = now.signed_duration_since(other_dt);

    // Just print it on terminal
    println!(
        "5.4.{} {}-{}-{}",
        diff.num_days(),
        local.year(),
        local.month(),
        local.day()
    );
}

fn stable() {
    // Get current time
    let now = Utc::now();
    let local = Local::now();
    let naive_time = NaiveDate::from_ymd(2017, 5, 19).and_hms(0, 0, 0);
    let other_dt = DateTime::<Utc>::from_utc(naive_time, Utc);

    // Calculate the duration time
    let diff = now.signed_duration_since(other_dt);

    // Just print it on terminal
    println!(
        "7.2.{} {}-{}-{}",
        diff.num_days(),
        local.year(),
        local.month(),
        local.day()
    );
}

fn develop() {
    // Get current time
    let now = Utc::now();
    let local = Local::now();
    let naive_time = NaiveDate::from_ymd(2017, 5, 19).and_hms(0, 0, 0);
    let other_dt = DateTime::<Utc>::from_utc(naive_time, Utc);

    // Calculate the duration time
    let diff = now.signed_duration_since(other_dt);

    // Just print it on terminal
    println!(
        "8.0.{} {}-{}-{}",
        diff.num_days(),
        local.year(),
        local.month(),
        local.day()
    );
}

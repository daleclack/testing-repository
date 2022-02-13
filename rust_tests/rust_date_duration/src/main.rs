use chrono::*;

fn main() {
    // Get current time
    let now = Utc::now();
    let naive_time = NaiveDate::from_ymd(2017,5,19).and_hms(0, 0, 0);
    let other_dt = DateTime::<Utc>::from_utc(naive_time,Utc);
    
    // Calculate the duration time
    let diff = now.signed_duration_since(other_dt);

    // Just print it on terminal
    println!("{}",diff.num_days());
}

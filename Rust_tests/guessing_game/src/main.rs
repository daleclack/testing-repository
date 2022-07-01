use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {
    println!("Guess number!");

    let test_number = rand::thread_rng().gen_range(1..100); //Generate a random number
    println!("The test number: {}", test_number);
    loop {
        let mut guess = String::new();

        println!("Input a number");

        io::stdin().read_line(&mut guess).expect("Can't read line"); //Read the number

        let guess: u32 = match guess.trim().parse(){    //Use match to handle errors when parse string to number
            Ok(num) => num,
            Err(_) => continue,
        }; //Transform string input to number

        println!("The number you guess is: {}", guess); //Print the numbers

        match guess.cmp(&test_number) {
            //Compare the input number and the generated number
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal =>{
                println!("Winned!");
                break;
            } ,
        }
    }
}

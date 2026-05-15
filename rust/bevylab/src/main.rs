use bevy::prelude::*;

fn hello_bevy()
{
 println!("Hello, Bevy!");
}

fn main()
{
 App::new().add_system(hello_bevy).run();
}

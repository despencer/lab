use bevy::prelude::*;

fn hello_bevy()
{
 println!("Hello, Bevy!");
}

fn main()
{
 App::new()
   .add_plugins(DefaultPlugins)
   .add_system(hello_bevy)
   .run();
}

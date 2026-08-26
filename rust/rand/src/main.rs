use rand_distr::{Normal, Distribution};

fn main()
{
 for _j in 0..2
 {
 let normal = Normal::new(1.0, 0.01).unwrap();
 for i in 0..10
    {
    let mut rng = rand::thread_rng();
    let value : u32 = 400;
    let v = normal.sample(&mut rng) * (value as f32);
    println!("Hello: #{} {}", i, v);
    }
 }
}
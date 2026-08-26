use rand_distr::{Normal, Distribution};

fn signal(credits: f32) -> bool
{
 let normal = Normal::new(0.0, 0.3).unwrap();
 let mut rng = rand::thread_rng();
 let value = (credits / 600.0 ) - 1.0;
 normal.sample(&mut rng) < value
}


fn main()
{
 for i in 0..20
 {
 let credits = 200.0 + (i as f32) * 50.0;
 println!("Signal: #{} {}", credits, signal(credits));
 }
}
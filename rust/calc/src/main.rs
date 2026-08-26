fn main()
{
 let mut sum : u32 = 0;
 for _i in 0..10
   {
   sum = sum.saturating_add(500000000);
   println!("Sum {}", sum);
   }
 let a : u32 = 6;
 let b : u32 = a.saturating_sub(7);
 println!("a {}, b {}", a, b);
}

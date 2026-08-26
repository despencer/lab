pub struct Place
{
 id: u32
}

pub struct Universe<'a>
{
 id: u32,
 places: Vec<Place>,
 places2: Vec<&'a Place>
}

pub fn new<'e>() -> Universe<'e>
 {
  let places = Vec::<Place>::new();
  let places2 = Vec::<&Place>::new();
  let universe = Universe { id: 1, places:places, places2:places2  };
  universe
 }

pub fn populate<'d, 'e>(universe: &'d mut Universe<'e>) -> () where 'd : 'e
 {
   let place = Place { id: 1};
   universe.places.push(place);
   let place2 = &universe.places[0];
   universe.places2.push(place2);
   universe.id += 1;
 }

pub fn create<'b, 'f>() -> Universe<'f> where 'b : 'f
{
 let mut universe = new::<'f>();
    {
    let uni = &'b mut universe;
//    uni.id += 2;
    populate::<'b,'f>(uni);
    }
 universe
}

pub fn dothework<'c>() -> ()
{
 let universe = create::<'c, 'c>();
 println!("Universe {:?}", universe.id);
}

fn main()
{
 dothework();
}
use std::{collections::BTreeMap, fs::File, io::BufWriter};
use std::time::Instant;
use anyhow::Result;
use mcap::{records::MessageHeader, Writer};

fn main() -> Result<()>
{
 let file = File::create("sample.mcap")?;
 let buf = BufWriter::new(file);
 let mut writer = Writer::new(buf)?;

 let start = Instant::now();
 let cid = writer.add_channel( 0, "events", "application/octet-stream", &BTreeMap::new() )?;

 for i in 0..10
   {
   let header = MessageHeader { channel_id : cid, sequence: i, log_time: start.elapsed().as_nanos() as u64, publish_time: start.elapsed().as_nanos() as u64 };
   let payload = vec![0xAB, 0xCD, i as u8];
   writer.write_to_known_channel(&header, &payload)?;
   }

 writer.finish()?;
 Ok(())
}

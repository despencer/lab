from mcap.reader import make_reader

with open('../writer/sample.mcap', 'rb') as f:
    reader = make_reader(f)
    for schema, channel, message in reader.iter_messages():
        print(schema, channel.topic, message.log_time, message.data)
    for schema, channel, message in reader.iter_messages(topics=['evens']):
        print(channel.topic, message.log_time, message.data)



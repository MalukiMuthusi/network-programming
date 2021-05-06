# Notes on TCP Client, Server Applications

When sending tcp messages between the server and the client, it is the duty of the developer to parse the messages. You have to establish the high level protocol you will use to interpret the message. How will you know you have read a complete message from the socket? By reading the `EOF` from the socket.

You can use the standard file functions to read and write data to the socket. Then you will need to add some synchronization mechanism. For example to send the message 

```json
{
    server: "Ubuntu-20", 
    location: "Kenya", 
    geo-point: {
        longitude: 1.1234, 
        latitude: 18.1234
    }, 
    message: "hello"
}
```

The json data is sent without any formating just  normal bytes. The server will read the data from the socket. The first read might read up to the `geo-point` then you do subsequent reads to read the complete message. The message is then stored in a buffer. When the client reads an `EOF`, then they know they have read the complete message from the server. 

The client can now interpret the message. Interpretting the message is just a matter of string processing. Any availble parser can be used.

## Simulation of a http Client, Server communication

What happens when you want to send a very large message, like a web page, html content. The html-content will be held in a buffer. The server then writes the html-content of the buffer to the socket. Because the content of the buffer is large, to send the whole html-content the kernel will break it down and send the packets in chunks.

How does the client receive the html-content? The client will create a buffer and read from the socket to the buffer. What is the size of the buffer? The client does not know the exact size of the buffer. A solution would be to start with a small buffer, then read from the socket to the buffer. If there is more data to read from the socket then expand the size of the buffer. `malloc` can be used to dynamically assign memory from the heap.

## Sending and Reading messages of dynamic sizes

Using a high level protocol of `JSON`, it becomes possible create a simple robust client and server. The main requirements are: string parsing/processing, dynamic memory assignment, reading and writing to sockets.
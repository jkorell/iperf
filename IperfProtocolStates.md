# Introduction #

Iperf3 is a network throughput testing tool.
It sends large quantities of data back and forth, and it
also has a protocol to control and manage the testing.

# Terminology #

The client is the process which sends the data, i.e. the source.
The server is the process that receives the data, i.e. the sink.
A stream is a single traffic flow from the client to the server.
A test is a collection of one or more streams.
In addition to the streams, each test has a control channel, and that
is where the Iperf3 Protocol takes place.

# Protocol Basics #

The control channel is always TCP even if the test streams are UDP.
Most protocol messages are just a single byte, saying what state to
switch to. Some of the messages also have a string of JSON data appended.
The JSON string is preceded by a 32-bit length, in network byte order.

# Typical Test Sequence #

Let's go through a typical test and look at each protocol message.

## IPERF\_START ##

The initial state is IPERF\_START.
This state isn't actually used for anything.

## Test Initiation ##

The client starts a test by creating the TCP control channel and
connecting to the server.
Then it sends the "cookie", an arbitrary 37-byte string that identifies
this test.

## PARAM\_EXCHANGE ##

When the server accepts a new connection, it sets the state to
PARAM\_EXCHANGE and tells the client.
Then the client sends a JSON string containing the test parameters

## CREATE\_STREAMS ##

The server sets the state to CREATE\_STREAMS and tells the client.
The client starts creating streams.

## TEST\_START ##

Once the server has accepted the agreed-upon number of streams,
it sets the state to TEST\_START and tells the client.
Both client and server initialize the test.

## TEST\_RUNNING ##

When the server finishes initializing the test, it sets the state
to TEST\_RUNNING and tells the client.
At this point the client starts sending data.

## TEST\_END ##

When the client determines that the test is over, it sets the state
to TEST\_END and tells the server.
The client stops sending data, and both sides take a final
measurement of the test statistics.

## EXCHANGE\_RESULTS ##

The server sets the state to EXCHANGE\_RESULTS and tells the client.
Then the client sends a JSON string of test results to the server,
and the server likewise sends a JSON string of test results to the
client.

## DISPLAY\_RESULTS ##

The server sets the state to DISPLAY\_RESULTS and tells the client.

## IPERF\_DONE ##

Finally, the client sets the state to IPERF\_DONE and tells the server.
That concludes the test, and both sides close the control channel.

# Atypical Test Sequence #

There are also a few protocol messages / states that only
show up in unusual circumstances.

## ACCESS\_DENIED ##

If the server denies permission for a connection, it returns this
state to the client.
This typically happens if the server is already running a test for
a different client.

## SERVER\_TERMINATE ##

If the server decides to terminate a test early, it sets this state
and tells the client.
Both sides terminate the test.

## CLIENT\_TERMINATE ##

If the client decides to terminate a test early, it sets this state
and tells the server.
Both sides terminate the test.

## SERVER\_ERROR ##

If the server runs into a problem, it sets this state and tells the client.
It then sends a 32-bit int of the Iperf internal error number, and a
32-bit int of the Unix error number.
Both sides terminate the test.

# Stream Protocol #

There is also a mini protocol for each stream:
on initial connection, the client sends the test's 37-byte cookie.
After that, the stream just gets uninterpreted data.

# Reverse Mode #

Iperf3 also has a Reverse Mode in which the client receives the data and the server sends it.
However this does not change how the control protocol and state machine
work.
The client and server go through the same sequence of states as in regular mode.
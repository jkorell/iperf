this is an initial version, an may have mistakes or omissions and probably both...

In Iperf terminology the client is the process which sends the data, eg. the
source.  The server is the process that receives the data, eg. the sink.  A
stream is a single traffic flow from the client to the server.  A test is a
collection of one or more streams.

The Iperf protocol is the very simple protocol that Iperf uses on the wire.
it has three very specific goals:

  1. stream and test initiation and termination
  1. results exchange
  1. collision prevention

There are many additional features that could be put into the Iperf protocol but
ultimately such things will overly complicate and muddy the intent of Iperf and are
best left in other packages.  For example, scheduling, authentication, authorization
and centralized result reporting are already implemented by [BWCTL](http://e2epi.internet2.edu/bwctl/)
which uses Iperf as one of several possible testing tools.

## Stream and Test Termination ##

This provides an explicit method for indicating the end of a stream and a
test.  TCP has explicit semantics for determining when a stream has been
closed, but UDP does not.  In order to provide a uniform and simple mechanism
for determining the end of a stream we use the stream termination mechanism
for both UDP and TCP.

### Stream Initiation ###

`IPERF_STREAM_BEGIN <cookie>`

### Stream Termination ###

A stream will terminate when it receives a packet with exactly the following contents:

`IPERF_STREAM_END <cookie>`

### Test Initiation ###

`IPERF_TEST_BEGIN <cookie>`

### Test Termination ###

`IPERF_TEST_END <cookie>`

## Results Exchange ##

This provides a mechanism for provide transferring results information from
the server back to the client.

The client sends `IPERF_RESULTS_REQUEST <cookie>`.

The server responds with `IPERF_RESULTS_RESPONSE <cookie> <result data>`.

All results exchange messages must be sent over a TCP connection to avoid the
need to packetize the results.  One connection per request.  The server does
not perform per interval results collection so although an
IPERF\_RESULTS\_REQUEST can be made during an active test the data may not be of
much use.

## Collision Prevention ##

This prevents multiple tests from colliding with each other.

The collision prevention mechanism is very simple.  The client generates 32
bytes of random data.  This is the cookie.  Every time the client opens a new
connection to the server the first 32 bytes must be the cookie.  If the server
is not presently servicing a client it will not have a cookie defined and will
accept the connection and store the cookie.  If the cookie for a new
connection does not match the cookie the server holds the new connection will
be rejected.  Once a test is complete This allows a long lived Iperf server to
handle one client session at a time.

The collision prevention mechanism does not provide any kind of security and
can be easily circumvented.  It's meant to protect innocent people from innocent
mistakes.

## Usual Sequence of Messages ##

```
C>S IPERF TEST BEGIN $cookie
C>S IPERF STREAM BEGIN $cookie  # one per stream
C>S [DATA TRANSFER]
C>S IPERF STREAM END $cookie    # one per stream
C>S IPERF RESULTS REQUEST $cookie
S>C IPERF RESULTS RESPONSE $cookie $data
C>S IPERF TEST END
```
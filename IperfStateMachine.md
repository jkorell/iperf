# Introduction #

This document describes the flow of control of Iperf at a very high level.

## Client State Machine ##

```
TEST_START -> TEST_RUNNING -> TEST_END -> TEST_COMPLETE
```

#### TEST\_START ####

  1. open control channel to the server
  1. exchange parameters with the server
  1. create and open test\_streams
  1. -> TEST\_RUNNING

#### TEST\_RUNNING ####

  1. generate data on each stream (either `n` bytes or `n` seconds)
  1. service the periodic callback
  1. when all data has been sent close stream
  1. when all streams closed -> TEST\_END

#### TEST\_END ####

  1. request results from server
  1. close control channel
  1. -> TEST\_COMPLETE

#### TEST\_COMPLETE ####

  1. all connections closed
  1. structs are kept in tact for reporting  and analysis

## Server State Machine ##

```
TEST_WAIT -> TEST_START -> TEST_RUNNING -> TEST_END -> TEST_WAIT
```

#### TEST\_WAIT ####

  1. listen for a control channel connection
  1. -> TEST\_START

#### TEST\_START ####

  1. wait for parameter exchange
  1. -> TEST\_RUNNING

#### TEST\_RUNNING ####

  1. create new streams as the arrive
  1. receive and discard data for each stream
  1. service results requests
  1. when no streams remain -> TEST\_END
  1. if no new data after `timeout` seconds, then close all streams and control channel -> TEST\_WAIT

#### TEST\_END ####

  1. wait for results request or control channel closure
  1. if nothing happens after `timeout` seconds -> TEST\_WAIT
  1. when control channel closed -> TEST\_WAIT
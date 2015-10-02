
```
IPERF(1)                         User Manuals                         IPERF(1)

NAME
       iperf3 - perform network throughput tests

SYNOPSIS
       iperf3 -s [ options ]
       iperf3 -c server [ options ]

DESCRIPTION
       iperf3  is  a  tool for performing network throughput measurements.  It
       can test either TCP or UDP throughput.  To perform an iperf3  test  the
       user must establish both a server and a client.

GENERAL OPTIONS
       -p, --port n
              set server port to listen on/connect to to n (default 5201)

       -f, --format
              [kmKM]   format to report: Kbits, Mbits, KBytes, MBytes

       -i, --interval n
              pause n seconds between periodic bandwidth reports

       -F, --file name
              client-side:  read  from  the  file  and  write  to the network,
              instead of using random data; server-side: read from the network
              and write to the file, instead of throwing the data away

       -A, --affinity n/n,m
              Set  the  CPU  affinity,  if possible (linux only).  On both the
              client and server you can set the local affinity;  in  addition,
              on  the  client  side you can override the server's affinity for
              just that one test, using the n,m form.

       -B, --bind host
              bind to a specific interface

       -V, --verbose
              give more detailed output

       -J, --json
              output in JSON format

       -v, --version
              show version information and quit

       -h, --help
              show a help synopsis

SERVER SPECIFIC OPTIONS
       -s, --server
              run in server mode
       -d, --daemon
              run the server in background as a daemon

CLIENT SPECIFIC OPTIONS
       -c, --client host
              run in client mode, connecting to the specified server

       -u, --udp
              use UDP rather than TCP

       -b, --bandwidth n[KM]
              set  target bandwidth to n bits/sec (default 1 Mbit/sec for UDP,
              unlimited for TCP).  If there are multiple  streams  (-P  flag),
              the  bandwidth  limit is applied separately to each stream.  You
              can also add a '/' and a  number  to  the  bandwidth  specifier.
              This  is  called "burst mode".  It will send the given number of
              packets without pausing, even if that  temporarily  exceeds  the
              specified bandwidth limit.

       -t, --time n
              time in seconds to transmit for (default 10 secs)

       -n, --bytes n[KM]
              number of bytes to transmit (instead of -t)

       -k, --blockcount n[KM]
              number of blocks (packets) to transmit (instead of -t or -n)

       -l, --length n[KM]
              length  of  buffer to read or write (default 128 KB for TCP, 8KB
              for UDP)

       -P, --parallel n
              number of parallel client streams to run

       -R, --reverse
              run in reverse mode (server sends, client receives)

       -w, --window n[KM]
              TCP window size / socket buffer size  (this  gets  sent  to  the
              server and used on that side too)

       -M, --set-mss n
              set TCP maximum segment size (MTU - 40 bytes)

       -N, --no-delay
              set TCP no delay, disabling Nagle's Algorithm

       -4, --version4
              only use IPv4

       -6, --version6
              only use IPv6

       -S, --tos n
              set the IP 'type of service'

       -L, --flowlabel n
              set the IPv6 flow label (only supported on Linux)

       -Z, --zerocopy
              Use  a  "zero copy" method of sending data, such as sendfile(2),
              instead of the usual write(2).

       -O, --omit n
              Omit the first n seconds of the test, to skip past the TCP slow-
              start  period.

       -T, --title str
              Prefix every output line with this string.

       -C, --linux-congestion algo
              Set the congestion control algorithm (linux only).

AUTHORS
       Iperf was originally written by Mark Gates and  Alex  Warshavsky.   Man
       page  and maintence by Jon Dugan .  Other con-
       tributions from Ajay Tirumala, Jim Ferguson,  Feng  Qin,  Kevin  Gibbs,
       John  Estabrook  , Andrew Gallatin , Stephen Hemminger 

SEE ALSO
       libiperf(3), http://code.google.com/p/iperf/

ESnet                              July 2010                          IPERF(1)
```
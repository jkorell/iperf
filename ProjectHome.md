**NEWS**

28 February 2014:  iperf3 has been migrated to GitHub.  Please see:

https://github.com/esnet/iperf

At this point the source code, issue tracker, and wiki have been moved.  Some other Web content remains to be updated.

**Please do not file any issues to the iperf3 issue tracker on Google Code.  Please use the issue tracker on GitHub instead, accessible through the link above.**


---


iperf was orginally developed by NLANR/DAST as a tool for measuring maximum TCP and UDP bandwidth performance.  It allows the tuning of various parameters and UDP characteristics and reports bandwidth, delay jitter, and datagram loss.

iperf3 is a new implementation from scratch, with the goal of a smaller, simpler code base, and a library version of the functionality that can be used in other programs. iperf3 also a number of features found in other tools such as nuttcp and netperf, but were missing from iperf2.X.

Some new features in iperf3 include:
  * reports the number of TCP packets that were retransmitted
  * reports the average CPU utilization of the client and server (-V flag)
  * support for zero copy TCP  (-Z flag)
  * JSON output format (-J flag)

Released versions of iperf3 are available in source code form at:

http://stats.es.net/software/

Or check out the code directly using:

```
git clone https://github.com/esnet/iperf.git
```

iperf3 is supported on Linux, FreeBSD ([FreeBSD Ports Collection](http://www.freshports.org/benchmarks/iperf3/)), and MacOS X only.  (Windows is not currently supported.)

The developer list for iperf3 is: iperf-dev@googlegroups.com

Note that iperf3.X is **not** backwards compatible with iperf2.X.

For iperf2.X code, see: http://sourceforge.net/projects/iperf/
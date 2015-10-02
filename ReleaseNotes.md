# Introduction #

This page include instructions for building a new release.


# Details #

Update README and RELEASE\_NOTES file to be accurate. Make sure
that the "Known Issues" section of the README file is up to date.

Compose a release announcement.  Most of the release announcement can be written before tagging.

There is a shell script in the source repo that can be used to create tarballs:

https://code.google.com/p/iperf/source/browse/make_release
Starting from a clean source tree (be sure that `hg stat` emits no output):

```
vi src/version.h   # update the strings IPERF_VERSION and IPERF_VERSION_DATE
vi configure.ac    # update version parameter in AC_INIT
./bootstrap.sh     # regenerate configure script, etc.
hg commit
hg push

./make_release tag  # this creates a tag in the hg repo that matches the version.h version
./make_release tar  # create tarball and compute SHA256 hash
```

Stage the tarball (and a file containing the SHA256 hash) to the download site.  Currently this is located on `stats.es.net`.

From another host, test the link in the release announcement by downloading a fresh copy of the file and verifying the SHA256 checksum.  For extra points, actually try downloading, compiling, and smoke-testing the results of the tarball on all supported platforms.

Plug the SHA256 checksum into the release announcement.

Send the release announcement (PGP-signed) to these addresses

  * iperf-dev at googlegroups dot com
  * iperf-users at lists dotsourceforge dot net
  * i2-perfsonar at internet2 dot edu
  * performance-node-users at internet2 dot edu
  * performance-wg at internet2.edu

# Note on version numbers #

We use three part release names:  MAJOR.MINOR.PATCH

Increment the:

  * MAJOR version when you make incompatible API changes,
  * MINOR version when you add functionality in a backwards-compatible manner, and
  * PATCH version when you make backwards-compatible bug fixes.
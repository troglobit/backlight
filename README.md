Backlight Control
=================
[![License Badge][]][License] [![Travis Status][]][Travis]

Simple program to control backlight brightness of laptops in Linux.

```
troglobit@example:~$ backlight -h

Usage: backlight [options] [command]

Options:
 -h    This help text
 -v    Show program version

Commands:
 up    Increase brightness
 down  Decrease brightness

Bug report address: https://github.com/troglobit/backlight/issues
```

The program has only two commands: `up` and `down`, which adjusts the
brightness up or down, respectively.  Without arguments the current
(raw) brightness value read from `/sys/class/backlight/*/brightness` is
displayed.

Brightness is controlled using an exponential scale to provide a smooth
transition from max to min.


[License]:         https://en.wikipedia.org/wiki/ISC_license
[License Badge]:   https://img.shields.io/badge/License-ISC-blue.svg
[Travis]:          https://travis-ci.org/troglobit/backlight
[Travis Status]:   https://travis-ci.org/troglobit/backlight.png?branch=master

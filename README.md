Backlight Control
=================

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


Inspiration
-----------

The following two projects served as inspiration, although `backlight`
is written from scratch.

- [light](https://github.com/haikarainen/light/) 
- [brightnessctl](https://github.com/Hummer12007/brightnessctl/)

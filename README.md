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


Build & Install
---------------

This is a GNU configure based project, so unless you are building it
directly from GIT, you can:

```sh
./configure
make
sudo make install
sudo adduser $LOGNAME video
```

The install phase adds the required `90-backlight.rules` to udev so
that the system grants write privileges to members of the video group
to control the display backlight.  For the changes to take effect you
have to reboot the system.

> **Note:** if you are building from GIT, you have to manually create
> the configure script and Makefile.in file: `./autogen.sh` helps you
> but you have to have the autoconf and automake tools installed.


Setup in Awesome
----------------

Users of the [Awesome WM][] can update their `~/.config/awesome/rc.lua`
to include the following:

```lua
    -- Brightness
    awful.key({ }, "XF86MonBrightnessUp", function () os.execute("backlight up") end,
              {description = "Increase brightness", group = "hotkeys"}),
    awful.key({ }, "XF86MonBrightnessDown", function () os.execute("backlight down") end,
              {description = "Decrease brightness", group = "hotkeys"}),
```

Reload Awesome and your brightness keys will now work as expected.

[Awesome WM]:      https://awesomewm.org/
[License]:         https://en.wikipedia.org/wiki/ISC_license
[License Badge]:   https://img.shields.io/badge/License-ISC-blue.svg
[Travis]:          https://travis-ci.org/troglobit/backlight
[Travis Status]:   https://travis-ci.org/troglobit/backlight.png?branch=master

doc_DATA           = README.md LICENSE
EXTRA_DIST         = README.md LICENSE
bin_PROGRAMS       = backlight
dist_man1_MANS     = backlight.1
backlight_SOURCES  = backlight.c

udevrulesdir       = @UDEVDIR@/rules.d
udevrules_DATA     = 90-backlight.rules
EXTRA_DIST        += $(top_srcdir)/90-backlight.rules


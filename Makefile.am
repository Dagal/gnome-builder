include build/autotools/automake/glib-tap.mk
include build/autotools/automake/Defaults.mk
include build/autotools/automake/ChangeLog.mk
include build/autotools/automake/AutomakeDocs.mk

ACLOCAL_AMFLAGS = -I build/autotools/m4 ${ACLOCAL_FLAGS}

AM_CPPFLAGS =
AM_LDFLAGS =

include libide/Makefile.am
include src/gnome-builder.mk
include tools/Makefile.am
include data/data.mk
include data/gsettings.mk
include tests/tests.mk

# XXX: Not happy about this, need to come up with a good way to do
# icon installation that doesn't require subdirs.
SUBDIRS = . data/icons po

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(top_builddir)/data/libide-1.0.pc

EXTRA_DIST += \
	tap-driver.sh \
	tap-test

INTLTOOL_FILES = \
	intltool-extract.in \
	intltool-merge.in \
	intltool-update.in \
	$(NULL)

EXTRA_DIST += \
	$(INTLTOOL_FILES) \
	AUTHORS \
	build/autotools/m4/introspection.m4 \
	$(NULL)

DISTCHECK_CONFIGURE_FLAGS = --enable-introspection

debug:
	G_DEBUG=fatal-criticals $(LIBTOOL) --mode=execute gdb --args gnome-builder test.c

valgrind:
	G_DEBUG=fatal-criticals $(LIBTOOL) --mode=execute valgrind gnome-builder test.c

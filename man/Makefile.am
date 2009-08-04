man_MANS = iat.1
EXTRA_DIST = $(man_MANS)
MAINTAINERCLEANFILES = $(man_MANS)


# The man pages depend on the --help strings and the version number.
common_mandeps = $(top_srcdir)/configure.ac

# Depend on the source, not the binary; we don't need to regenerate the
# binary when any source file changes, only the main one.
# Use -o so that the `missing' program can infer the output file.
iat.1:

#!/bin/bash


# SET configure.ac

# version
GITVERSION=`date  +%Y%m%d%H%M`
GITDATEVERSION=GITDATEVERSION
# file name
CONFIGURE_AC=configure.ac
# edit configure.ac
sed -i  "s/git.*.dev,/git.$GITVERSION.dev,/" $CONFIGURE_AC 
echo "configure.ac : OK";

#gengetopt  --output-dir=src < iat.ggo 
autoreconf --force
echo "autoreconf : OK";
#./configure --enable-maintainer-mode
#make
#./help2man.pl -N -P iat -I iat.h2m src/iat > man/iat.1

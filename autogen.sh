#!/bin/bash

gengetopt  --output-dir=src < iat.ggo 
autoreconf --force
./configure
make
./help2man.pl -P iat -I iat.h2m  src/iat > man/iat.1

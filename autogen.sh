#!/bin/sh

gengetopt  --output-dir=src < iat.ggo 
autoreconf --force
./configure

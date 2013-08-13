#!/bin/bash
# analyzer.sh -- created 2013-08-09, Aljosha Friemann
# @Last Change: 24-Dez-2004.
# @Revision:    0.0

if [ -n ../psafe ]; then
  cd ..
  ./install
  cd analysis
fi

for i in `seq 1 10`
do
  ./../psafe wat 12 >> ./log
done

# vi: 
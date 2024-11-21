#!/bin/bash

# Do things like "cat ../../Downloads/error.in | perf record -g bin/975" first.

perf script > /tmp/out.perf
stackcollapse-perf.pl /tmp/out.perf > /tmp/out.folded
flamegraph.pl /tmp/out.folded > flamegraph.svg
rm perf.data /tmp/out.perf /tmp/out.folded

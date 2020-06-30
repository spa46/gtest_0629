#!/bin/sh
set -x
g++ $1 -I. -lgtest -L. -pthread

#!/bin/bash

vmstat -S M 1 6 | tail -n 5|awk '{print $15}'


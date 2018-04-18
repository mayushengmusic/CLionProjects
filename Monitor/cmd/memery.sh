#!/usr/bin/env bash

free -m |head -n 2|tail -n 1 | awk '{printf("%d",$7/$2*100)}'

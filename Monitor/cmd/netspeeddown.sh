#!/usr/bin/env bash
eno1=$(sar -n DEV 1 2 | tail -n 3|grep wlp58s0|awk '{print $5}')
eno2=$(sar -n DEV 1 2 | tail -n 3|grep wlp58s0|awk '{print $5}')

if [ $(echo "$eno1>$eno2" | bc) = 1 ]; then
echo $eno1 | awk '{printf("%d",$0)}';
else
echo $eno2 | awk '{printf("%d",$0)}';
fi

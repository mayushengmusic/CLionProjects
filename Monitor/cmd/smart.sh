#!/usr/bin/env bash
sudo smartctl -H /dev/$1 | grep -i "SMART overall-health self-assessment test result:" | awk '{print $6}'


#!/usr/bin/env bash
zpool list | grep tank | awk '{printf $7}'
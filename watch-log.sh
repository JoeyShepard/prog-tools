#!/bin/bash
size=$(ls -lh log.txt | awk '{print $5}')
lines=$(tput lines)
lines=$(($lines - 3))
cmd="echo LOG FILE SIZE: $size && cat log.txt | tail -n $lines"
watch -n3 $cmd

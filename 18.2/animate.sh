#!/bin/bash
for i in $(seq 0 504); do
    printf "%03d\n%s\n\n" $i "$(./code $i < input)"
    sleep 0.03
done
while :; do
    for i in $(seq 505 532); do
        printf "%3d\n%s\n\n" $i "$(./code $i < input)"
    done
done


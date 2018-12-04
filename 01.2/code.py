#!/usr/bin/env python3 
strs = open("input").read().split()

nums = list(map(int, strs))

counts = {0: 1}

idx = 0
freq = 0
while True:
    freq += nums[idx]
    counts[freq] = counts.get(freq, 0) + 1
    if counts[freq] == 2:
        print(freq)
        break

    idx = (idx + 1) % len(nums)

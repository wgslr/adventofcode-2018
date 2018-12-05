#!/usr/bin/node

// Wojciech Geisler
// Advent of Code 2018

const input = require('./input.json')

function cb(acc, x) {
  if ("id" in x) {
    acc.curr = x.id
    return acc
  } else if (x.text == "falls asleep") {
    acc.start = x.minute
    return acc
  } else if (x.text == "wakes up") {
    const end = x.minute;
    let { start, curr, guards, totals } = acc;

    if (guards[curr] === undefined) {
      guards[curr] = []
      totals[curr] = 0
      for (let i = 0; i < 60; ++i) {
        guards[curr][i] = 0
      }
    }

    for (let i = start; i < end; ++i) {
      guards[curr][i] += 1;
      totals[curr] += 1;
    }

    return acc
  }
}

function findMax(arr) {
  return arr.reduce((acc, x, idx) => {
    if (x > acc.max) {
      return { max: x, maxIdx: idx };
    } else {
      return acc;
    }
  }, { max: 0, maxIdx: -1 })
}

sums = input.reduce(cb, { curr: -1, start: -1, guards: {}, totals: [] })

const { maxIdx: bestGuard } = findMax(sums.totals);

const { maxIdx: bestMinute } = findMax(sums.guards[bestGuard]);

console.log(bestGuard, bestMinute)
console.log(bestGuard * bestMinute)

// PART 2

bestGuards = [];
bestCounts = [];
for (let i = 0; i < 60; ++i) {
  bestGuards[i] = -1;
  bestCounts[i] = 0;
}

Object.entries(sums.guards).forEach(([guard, minuteCounts]) => {
  const { max: count, maxIdx: bestMinute } = findMax(minuteCounts);
  if (bestCounts[bestMinute] < count) {
    bestGuards[bestMinute] = guard;
    bestCounts[bestMinute] = count;
  }
});


console.log(findMax(bestCounts));
const { maxIdx: bestMinute2 } = findMax(bestCounts);

console.log(bestCounts[bestMinute2]);
console.log(bestGuards[bestMinute2] * bestMinute2);
#!/usr/bin/node

const PLAYERS = 439;
const LAST_MARBLE = 71307
// const PLAYERS = 9;
// const LAST_MARBLE = 25

const circle = [0, 1]
const points = new Array(PLAYERS + 1).fill(0)
let nextMarble = 2;
let nextElf = 2; // elf who places next marble
let currentMarble = 1; // position of current marble

function insert(pos, value) {
  const len = circle.length;

  if (pos > len) {
    pos = pos % len;
  }
  circle.splice(pos, 0, value);
  return circle.indexOf(value);
}

// returns value and position to the right
function remove(pos) {
  const len = circle.length
  pos = pos % len;

  if (pos < 0) {
    pos += len;
  }

  const [removed] = circle.splice(pos, 1);
  return [removed, pos];
}

while (nextMarble <= LAST_MARBLE) {
  if (nextMarble % 23 != 0) {
    currentMarble = insert(currentMarble + 2, nextMarble);
  } else {
    [removed, currentMarble] = remove(currentMarble - 7);
    points[nextElf] += nextMarble; // += 23
    points[nextElf] += removed;
  }

  nextMarble++;
  nextElf = (nextElf) % PLAYERS + 1;
}

const best = Math.max(...points);
console.log(best)
console.log(points.indexOf(best))
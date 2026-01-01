# [Advent of Code 2025](https://adventofcode.com/2025)

### Language of the Year: C

Using C17+, though will likely be C99 compatible.
<div style="width:100%;">
<table style="width:100%;">
  <tr>
    <th>Problem</th>
    <th></th>
    <th>1</th>
    <th>2</th>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/1">Day 1: Secret Entrance</a></td>
    <td>Messy Modulo Math</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day01.c">*</a></td>
    <td><a href="https://raw.githubusercontent.com/dnabre/advent_2025/master/Day01.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/2">Day 2: Gift Shop</a></td>
    <td>String Manipulation</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day02.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day02.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/3">Day 3: Lobby</a></td>
    <td>String Manipulation</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day03.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day03.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/4">Day 4: Printing Department</a></td>
    <td>2D Search and Reverse Flood Fuild</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day04.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day04.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/5">Day 5: Cafeteria</a></td>
    <td>Merging Intervals</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day05.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day05.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/6">Day 6: Trash Compactor</a></td>
    <td>String Manipulation</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day06.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day06.c">* </a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/7">Day 7: Laboratories</a></td>
    <td>Simple State Representation</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day07.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day07.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/8">Day 8: Playground</a></td>
    <td>Graph Fun</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day08.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day08.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/9">Day 9: Movie Theater</a></td>
    <td>Geometry + Assumptions about Input</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day09.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day09.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/10">Day 10: Factory</a></td>
    <td>Combinatorics/Dynamic Programming</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day10.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day10.c">*</a></td>
  </tr>

  <tr>
    <td><a href="https://adventofcode.com/2025/day/11">Day 11: Reactor</a></td>
    <td>Graph Transversal</td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day11.c">*</a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day11.c"> </a></td>
  </tr> 
  <tr>
    <td><a href="https://adventofcode.com/2025/day/12">Day 12: Christmas Tree Farm </a></td>
    <td></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day12.c"> </a></td>
    <td><a href="https://github.com/dnabre/advent_2025/blob/master/src/day12.c"> </a></td>
  </tr>


</table>
</div>

|         | Day by Day Notes                                                                                                                                                                                                                  |
|---------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Day 2:  | Just did the simple brute-force for part 2 - takes over 200ms.                                                                                                                                                                    |
| Day 5:  | Sort & Merge for ranges in part 2. Part 1 still brute force                                                                                                                                                                       |
| Day 6:  | When you realize why the test and input are different, it all makes sense                                                                                                                                                         |
| Day 8:  | This took me a lot time, size of main sort could be reduced                                                                                                                                                                       |
| Day 9:  | Took a lot to figure out, had to visualize to get anywhere. Tailored  algorithm <br>to properites of the input (pretty much required, not uncommon with AoC)                                                                      |
| Day 10: | Recursion, expects to need memoization, but it just wasn't slow enough to bbother. Axiom of AoC helped => whenever they saw to ignore someting (in this case the lights for part 2), don't! It is alway helpful if not vital<br/> |
| Day 11: |                                                                                                                                                                                                                                   |
| Day 12: |                                                                                                                                                                                                                                   |

I'm using C, in part, to knock a little of the massive amount of rust on my C skills.
Between that, and using opinionated rather than idiomatic stuff, this is code-base is not
a good learning resource for C programming.

Toolchain:

* clang version 21.1.5
* Target: aarch64-w64-windows-gnu
* Using msys/clangarm64/clang
* Clion IDE

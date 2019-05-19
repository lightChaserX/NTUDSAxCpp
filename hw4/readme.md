# String And Substring

## Description
You are given a string $s$ and an integer $m$, your task is to solve two problems:

1. Find a longest string $t$, so that $t$ is a substring of $s$, and appears at least $m$ times in $s$. The definition of substring is a sequence of consecutive characters in a string.
For example, $s = baaaababababbababbab$, $m = 3$, then the answer would be $babab$, since there is no other substring of $s$ is longer than $babab$ and appears at least $3$ times in string $s$.

2. Find a longest string $r$, such that $r$ is a prefix of $s$ and a suffix of $s$. In other words, $r$ is the beginning of the string $s$ and the end of the string $s$. To make it more challenging, string $r$ also need to be able to be located somewhere inside the string $s$, that is, it is neither beginning, nor its end.
For example, $s = abcdabcabc$, the answer is $abc$, because it appears at positions $0$ (prefix), $4$ (neither prefix nor suffix), $7$ (suffix), which meets the requirements.

## Input Format
The input contains several test cases. Each test case consists of a line with an integer $m$ $(m  \ge 1)$, the minimum number of repetitions, followd by a line containing a string $s$. All characters in $s$ are lowercase characters from 'a' to 'z'. The last test case is denoted by $m = 0$ and must not be processed.

## Output Format
For each test case, you need to print two lines of answers:

For problem 1, if there is no solution, output "none" without the quotes; otherwise, print two integers in a line, separated by a space. The first integer denotes the maximum length of a substring appearing at least $m$ times; the second integer is the right most possible starting position of such a substring.

For problem 2, print the string that meets the requirements. If a suitable string does not exist, then print "Just a legend" without the quotes.

## Limit
$1 \le length(s), m \le 10^5$

## Sample inputs
```
3
abcdabcabc
4
abcdabcabc
3
abcdabcabcd
1
aaaaaaa
2
btcbtcetheth
0
```

## Sample outputs
```
3 7
abc
none
abc
3 7
Just a legend
7 0
aaaaa
3 9
Just a legend
```

## 較大的測資
[sample input and output](https://drive.google.com/drive/folders/1XVZERkgQCPu3b3hsl52pTXpJ5AoeY_vJ?usp=sharing)

## Hint
[Rolling Hash](http://fcrh.logdown.com/posts/592025-about-rolling-hash)
Hash collision
Binary search

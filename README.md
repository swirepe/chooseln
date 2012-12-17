# chooseln  - choose random lines from an input file

Peter Swire - swirepe.com

## What is it?

It spits out random lines from an input, with each line having the same probability.

## How do I use it?

        chooseln filename         choose a line from a file at random.
        chooseln x filename       choose x lines from a file at random.

## How does it work?

Instead of loading the whole file into memory, it keeps a count of the line number it is on.  It holds onto any line with `1 / line_number` probability.  The first line is 1 / 1, or 100% likely to be chosen.  The second line is 1 / 2, or 50% likely to be chosen.  If it is, the first line is dropped and the second line is held on to.

This is done until there are no more lines to be read.

## Why?

I wrote this in the back of a car during a family trip.  One day it might be part of a larger project for making [user-memorable keys.](http://xkcd.com/936/)  At the time, it was just away to combat boredom while my sister took a nap.

It comes with the output of /usr/share/dict/american-english, with the proper nouns and non-ascii words filtered out.

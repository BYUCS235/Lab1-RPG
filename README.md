# RPGLab-1
The template for RPG Lab #1

# Requirements

## Overview

You will need the files in this git repository to complete this assignment

1. File1 - Construct the Arena (15 points)

Make a class that inherits from the ArenaInterface provided; the arena is simply a collection of fighters, each with a unique name
For Part 1 only, you may assume all strings passed to the arena's adding method will be of the correct format.
For Part 1 only, you may assume all strings passed to the arena's getting and removing methods will be names already existing in the arena.

2. File2- Let the Battle Begin (22 points)

Make a class that inherits from the FighterInterface provided; details about abilities, stats, and more can be found in the FighterInterface
For Part 2, the test driver will not call your useAbility() or regenerate() methods, so it is possible to receive credit for Part 2 without these methods being complete
Completion of Part 1 is required to submit Part 2

3. File3 - Reset Testing (8 points)

This is a more thorough testing of battling and resetting.

4. File4- Fortify the Walls (15 points)

Make adding new fighters to your arena robust; this involves rejecting any string that is not of the correct format or that would add a duplicate name to the arena.
Make getting and removing existing fighters in your arena robust
Completion of Part 1 is required to submit Part 3

5. File5 - Let Me Show You My True Form... (40 points)

Add functionality to the useAbility() method and the regenerate() method for each fighter type
Completion of Parts 1 and 2 is required to submit Part 5

## Requirement Notes

  * You are required to write a seperate '.cpp' and '.h' for each class you implement.
  * You are required to use inheritance to implement the three kinds of fighters. The TAs reserve the right to deny pass off to programs utilizing inheritance incorrectly or that do not have the expected inheritance hierarchy.
  * Unless otherwise instructed, use standard integer division for all division operations specified. This means all fractional results should be rounded down (ex: 17/10 = 1).
  * You should not call a Fighter's useAbility() function in the getDamage() function, the test driver will handle all function calls for the Fighters.
  * It is highly recommended to use the standard vector as the underlying representation for the Arena class.  You are welcome to use other underlying structures, but those will be covered later in the course.
Fighter String Format

Fighters are represented as strings when added to the arena. The following format is expected:
(name) (type) (maximum hit points) (strength) (speed) (magic)
Example: Xephos A 200 13 21 10
The name is a single word; the type is a single capital letter ((R)obot, (A)rcher, or (C)leric); the remaining four stats are positive integers.

## Fighting

The following is a table of battles that will be run by the test driver:
![Battles](https://mjcleme.github.io/CS235Lab1Battles.png "Battles")

 

## Class Hierarchy 

The following class hierarchy diagram shows the expected inheritance relationship between classes.  Each box represents a class with inheritance indicated by the arrows.  You should have at least this set of classes to complete the lab.

![Lab1UML](https://mjcleme.github.io/CS235Lab1UML.png "UML")

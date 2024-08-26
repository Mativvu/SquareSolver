# Solver of quadratic equations (overpowered version)


## Project describtion

A C/C++ project for solving quadratic equations including other features such as 
file input and output, unit testing, colored output and processing command-line flags.


## Table of contents.
* [How to install and run the project](#How-to-install-and-run-the-project)
* [How to use the project](#How-to-use-the-project)
* [Project status](#Project-status)
* [Sources](#Sources)
* [Authors](#Authors)

## How to install and run the project

### Compatibily
This project was made for MacOS, but you can still run it on any other OS if you delete compilation flags from
bash file **compile.sh**, also you will lose a feature of shouting "ER TE"[^1] from your speakers, but this is 
optional.

[^1]: "ER TE" or "РТ" is an abbreviation of MIPT faculty "FRECT" I`m studing at.

This is the line you need to find in **compile.sh** and delete everything after the word *program*(all ... stuff).
```
g++ SSCatchError.cpp SquareSolver.cpp SSFlagsAndFiles.cpp SSInput.cpp SSSolve.cpp SSOutput.cpp SSUnitTest.cpp -o program ...
```

### How to run the program
Compilator: project was tested on Clang of version 15.0.0.

Github URL for cloning: 
```
https://github.com/Mativvu/SquareSolver
```

To run the program open your terminal and type `cd folder` to get to the folder with project, then type
this two lines to execute bash file and start the program:
```
complie.sh
program
```
Congratulations, you ran the program!


## How to use the project
If you start the program without any command-line flags you will see what kind of input it expects and what
data it recieved seccessfully, after algorithm finishing, you will see the solutions to the equation 
*ax^2+bx+c=0*.
My project has some features besides just calcuating roots to the quadratic equation, you can access
most of them using command-line arguments by typing them after the word *program*:
```
/PATH/program --flag1 --flag2
```
Here is the list of all command-line flags:
  * **"--help" or "-h"** Prints describtion to each available flag and stops program. 
  * **"--debug" or "-d"** Prints what to do to enable debug mode. Prints additional info for user and
activates assert() functions in program while debug mode is on.
  * **"--test" or "-t"** Unit testing mode. Takes tests data from internal arrays and prints how many tests
failed and passed in terminal. When combined with flag **"--file" or "-f"**, takes data from files "UnitTestsInput.txt"
and "UnitTestsAnswers.txt". You can add more tests if you want, there are only 9 of them right now.
  * **"--file" or "-f"** Mode to use default "input.txt" and "output.txt" files. Combining this flag with flags
**"--in"** or **"--out"** is forbidden, because they lead to other files being opened.
  * **"--in" or "-i" plus "filename"** Activates input from file that user inputted. 
  * **"--out" or "-o" plus "filename"** Activates output to file that user inputted.
  * **"--RT" or "-r"** Prints "РТ" sign and shouts "ER TE" from speakers. This flag was made in honor to our
wonderful Faculty of Radio Engineering and Computer Technology(FRECT), you probably wouldn`t understand.

Most of the text in program is colored using ANSI color codes, you can find them in **SSOutput.h** file, 
unfortunately colored output is not supported for files. Debug output is all blue, errors are printed in
red and unit tests use red, green and yellow colors. Command-line arguments are printed in cyan and their 
describtions in magenta.


## Project status
The last version is 4.1, no more updates are planned.


## Sources
This project was made on summer school of MIPT just before the start of the first year as our
first real programmming task. We were provided help from mentors, so this is a kind of a team project.


## Authors
Matveychuk Egor, 1 year MIPT student



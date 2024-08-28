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
bash file [compile.sh](compile.sh), also you will lose a feature of shouting "ER TE"[^1] from your speakers, but this is optional.

[^1]: "ER TE" or "РТ" is an abbreviation of MIPT faculty "FRECT" I`m studing at.

This is the line you need to find in [compile.sh](compile.sh) and delete everything after the word *program*.
```
g++ SSCatchError.cpp SquareSolver.cpp SSFlagsAndFiles.cpp SSInput.cpp SSSolve.cpp SSOutput.cpp SSUnitTest.cpp -o program <flags to delete>
```

### How to run the program
Compilator: project was tested on Clang version 15.0.0.

Github URL for cloning: 
```
https://github.com/Mativvu/SquareSolver
```

To run the program open your terminal and type `cd folder` to get to the folder with project, then type
these two lines to execute bash file and start the program:
```
complie.sh
program
```
If you see this, then congratulations, you ran the program!

<img width="1156" alt="Снимок экрана 2024-08-26 в 18 33 59" src="https://github.com/user-attachments/assets/f93154ab-b4d6-42fd-a521-52644ecaa899">


## How to use the project
Project has some features besides just calcuating roots to the quadratic equation, you can access
most of them using command-line arguments by typing them after the word *program*:
```
/PATH/program --flag1 --flag2
```
Here is the list of all command-line flags:
  * **"--help"** or **"-h"** prints describtion to each available flag and stops program. 
  * **"--debug"** or **"-d"** prints what to do to enable debug mode. Prints additional info for user and
activates assert() functions in program while debug mode is on.
  * **"--test"** or **"-t"** starts unit testing mode. Takes tests data from internal arrays and prints how many tests
failed and passed in terminal. When combined with flag *"--file"* or *"-f"*, takes data from files "UnitTestsInput.txt" and "UnitTestsAnswers.txt". You can add more tests if you want, there are only 9 of them right now.
Example of output after unit testing:

<img width="1154" alt="Снимок экрана 2024-08-26 в 18 37 18" src="https://github.com/user-attachments/assets/51939405-1b1a-4a75-94e9-36d933733fc1">

  * **"--file"** or **"-f"** mode to use default "input.txt" and "output.txt" files. Combining this flag with flags
    *"--in"* or *"--out"* is forbidden, because they lead to other files being opened. Here is the output after typing
    this command: (Also shows what debug mode looks like)
    
<img width="1156" alt="Снимок экрана 2024-08-26 в 18 52 44" src="https://github.com/user-attachments/assets/447fa939-628e-499e-a416-c8a0ea935b76">

Contents of the file "input.txt" were: `1 0 -4` and "output.txt": `First solution: 2, second solution: -2`

  * **"--in"** or **"-i" plus "filename"** activates input from file that user inputted. 
  * **"--out"** or **"-o" plus "filename"** activates output to file that user inputted. 
  * **"--RT"** or **"-r"** prints "РТ" sign and shouts "ER TE" from speakers. This flag was made in honor to our
wonderful Faculty of Radio Engineering and Computer Technology(FRECT), you probably wouldn`t understand. Thats how it looks like:

<img width="1156" alt="Снимок экрана 2024-08-26 в 18 54 27" src="https://github.com/user-attachments/assets/d5ca6670-ec3c-4272-b31a-80de25dc27b4">

> _Most of the text in program is colored using ANSI color codes, you can find them in [SSOutput.h](SSOutput.h) file, 
unfortunately colored output is not supported for files. Debug output is all blue, errors are printed in
red and unit tests use red, green and yellow colors. Command-line arguments are printed in cyan and their 
describtions in magenta._


## Project status
It will be get updates once in a while.


## Sources
This project was made on summer school of MIPT just before the start of the first year as our
first real programmming task. We were provided help from mentors, so this is a kind of a team project.


## Authors
Matveychuk Egor, first year MIPT student



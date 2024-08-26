/*!
* \file
* \brief Enum ::Mode for compilation flags codes and struct Command
* to store its code, name and describtion.
* Functions to process flags, open files and print some stuff :)
* Uses colored output, see \file SSOutput.h for all color codes.
*/

/** \struct Command
* \brief Contains command usual and short name, its code and describtion.
*
* \details
* - Contains:
*       - mode of enum type ::Mode, code expressed in 1 to the n power of 2.
*       - long name starting with "--".
*       - short name starting with "-".
*       - command describtion.
*/

/** \fn ProcessMainArgs(const int argc, const char *argv[], int *mode_field,
*                       const char **fin_name, const char **fout_name)
* \brief Goes through argv list to find correct compilation flags.
*
* \details Goes through argv list to find correct compilation flags.
* - Calls ::IsValidCommand() to determine if inputted flag exists.
*
* If the right flag is found, turns on the matching bit in mode_field
using bit operators like this:
* \code
*   mode_field |= flag;
* \endcode
* If unknown flag if found, returns an error and the name of the flag.
* Combination of flags "--file" and "--in" or "--out" is forbidden.
*
* @param argc Number of arguments main function recieved, including
* the filename of the program.
* @param argv Array of strings representing command-line arguments.
* @param mode_field Integer, each bit of which represents the state(on/off)
* of each mode from enum ::Mode.
* @param fin_name Name of file with input data inputted by user if
* command "--in" is found.
* @param fout_name Name of file for output data inputted by user if
* command "--out" is found.
*
* @throw ::ExitCodeDUPLICATION_ERROR if two similar commands are found.
* @throw ::ExitCodeUNKNOWN_ARG if unknown command is found.
*
* @return ::ExitCodeOK if finished with no errors.
*/

/** \fn FileManager(int mode, FILE **fin_p, FILE **fout_p, const char *fin_name,
                    const char *fout_name);
* \brief Opens files if appropriate commands were inputted.
*
* \details Opens default files "input.txt" and "output.txt" if command
* "--file" was found and files with "fin_name" name or "fout_name" name
* if commands "--in" or "--out" were found accordingly.
* - Calls functions:
*       - ::IsModeSet() to check if command was found.
*       - fopen() to open file.
*
* Also checks if file was opened successfully by comparing pointer to
* it with nullptr. Returns error if combination of flags "--file" and
* "--in" or "--out" was inputted.
*
* @param mode_field Integer, each bit of which represents the state(on/off)
* of each mode from enum ::Mode.
* @param fin_p Pointer to file with input data to asssign fopen() to.
* @param fout_p Pointer to file for output data to asssign fopen() to.
* @param fin_name Name of the file with input data that user typed.
* @param fout_name Name of the file for output data that user typed.
*
* @throw abort() if DEBUG mode is on and fin_p is nullptr.
* @throw abort() if DEBUG mode is on and fout_p is nullptr.
* @throw ::ExitCodeCOMMAND_ERROR if fobidden combination of commands "--file"
* and "--in" or "--out" is found.
* @throw ::ExitCodeFILE_ERROR if cannot open/find file "fin_name" or "fout_name"
*
* @return ::ExitCodeOK if finished with no errors.
*/

/** \fn IsModeSet(int mode_field, int mode)
* \brief Checks if mode is turned on.
*
* \details Checks if matching bits in mode_field and mode are set to 1
* using bit operators like this:
* \code
* if(mode_field & mode)
* \endcode
*
* @param mode_field Integer, each bit of which represents the state(on/off)
* of each mode from enum ::Mode.
* @param mode Command code from enum ::Mode expressed in 1 to the n power of 2.
*
* @return 1 if mode is turned on, 0 otherwise
*/

/** \fn IsValidCommand(const char* str, Command command)
* \brief Checks if str is an existing command name or not.
*
* \details Compares str with usual and short name of the flag from
* Command using strcmp() from <string> library.
*
* @param str String from argv array.
* @param command Element of array of structures Command.
*
* @return 1 if str is equal to usual\short name of command, 0 otherwise
*/

/** \fn PrintCommands()
* \brief Prints describtions to each command-line argument if "--help" is found.
*
* \details Prints colored describtions from Command::describtion to each command-line
* argument if command "--help" is found.
*/

/** \fn PrintRT()
* \brief Prints a big sign "РТ" made from "РТ" and shouts "РТ" from speakers.
*
* \details Prints a big "РТ" sign made from "РТ" and shouts "РТ" from speakers.
* If cannot find/open file "RT.txt", sends message and finishes, program continues
* in normal mode. Uses getline() to read file line by line and shout "РТ" before
* each line.
*
* @warning Shouts "РТ" only on macbooks(.
*/

#ifndef SSFLAGSANDFILES_H
#define SSFLAGSANDFILES_H

#include "SSErrorCodes.h"
#include "SSErrorCodes.h"

enum Mode {
    ModeTest   = 1U << 0, /**< Unit testing mode. */
    ModeFile   = 1U << 1, /**< Mode to use default "input.txt" and "output.txt" files. */
    ModeDebug  = 1U << 2, /**< Does nothing, because DEBUG mode switches using define. */
    ModeHelp   = 1U << 3, /**< Prints describtion to each available flag. */
    ModeInput  = 1U << 4, /**< Activates input from file that user inputted. */
    ModeOutput = 1U << 5, /**< Activates output to file that user inputted. */
    ModeRT     = 1U << 6  /**< Prints "РТ" sign and shouts "РТ" from speakers.*/
};

struct Command {
    Mode mode;
    const char* name;
    const char* short_name;
    const char* describtion;
};

ExitCode ProcessMainArgs(const int argc, const char *argv[], int *mode_field, const char **fin_name, const char **fout_name);
ExitCode FileManager(int mode_field, FILE **fin_p, FILE **fout_p, const char *fin_name, const char *fout_name);
bool IsModeSet(int mode_field, int mode);
bool IsValidCommand(const char* str, Command command);
void PrintCommands();
void PrintRT();

#endif

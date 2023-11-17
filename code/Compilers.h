/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: Sina Khodaveisi, Ark Gupte
* Professors: Paulo Sousa
************************************************************
=------------------------------------------------------------=
|             COMPILERS - ALGONQUIN COLLEGE (F23)            |
=------------------------------------------------------------=
|     _   __                    _____           _       __   |
|    / | / /___ _   ______ _   / ___/__________(_)___  / /_  |
|   /  |/ / __ \ | / / __ `/   \__ \/ ___/ ___/ / __ \/ __/  |
|  / /|  / /_/ / |/ / /_/ /   ___/ / /__/ /  / / /_/ / /_    |
| /_/ |_/\____/|___/\__,_/   /____/\___/_/  /_/ .___/\__/    |
                                           /_/               |
=------------------------------------------------------------=
*/

/*
************************************************************
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* Language name */
#define STR_LANGNAME "NovaScript"

/* Logical constants - adapt for your language */
#define NOVASCRIPT_TRUE 1
#define NOVASCRIPT_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
        but they can be necessary for conversions.
------------------------------------------------------------
*/

/* TO_DO: Define your typedefs */
// typedef int int;
typedef long int64;
typedef float float32;
typedef double float64;
// typedef void void;

typedef char rune;
typedef char *string;

// typedef unsigned char bool;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS
{
    PGM_READER = 'r',
    PGM_SCANNER = 's',
    PGM_PARSER = 'p'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
int mainReader(int argc, string *argv);

/*
TO_DO: Include later mainScaner (A22) and mainParser (A32)
*/
void printLogo();

#endif

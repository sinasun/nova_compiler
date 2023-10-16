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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (NOVASCRIPT) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 /* (0000.0000)_2 = (000)_10 */
#define FUL_FLAG 0x01 /* (0000.0001)_2 = (001)_10 */
#define EMP_FLAG 0x02 /* (0000.0010)_2 = (002)_10 */
#define REL_FLAG 0x04 /* (0000.0100)_2 = (004)_10 */
#define END_FLAG 0x08 /* (0000.1000)_2 = (008)_10 */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (novaScript) .................................. */

/* Offset declaration */
typedef struct position {
	novaScript_int mark;			/* the offset to the mark position (in chars) */
	novaScript_int read;			/* the offset to the get a char position (in chars) */
	novaScript_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	novaScript_string	content;			/* pointer to the beginning of character array (character buffer) */
	novaScript_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	novaScript_int		increment;			/* character array increment factor */
	novaScript_int		mode;				/* operational mode indicator */
	novaScript_bool		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	novaScript_int		histogram[NCHAR];	/* Statistics of chars */
	novaScript_int		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(novaScript_int, novaScript_int, novaScript_int);
BufferPointer	readerAddChar		(BufferPointer const, novaScript_byte);
novaScript_bool		readerClear		    (BufferPointer const);
novaScript_bool		readerFree		    (BufferPointer const);
novaScript_bool		readerIsFull		(BufferPointer const);
novaScript_bool		readerIsEmpty		(BufferPointer const);
novaScript_bool		readerSetMark		(BufferPointer const, novaScript_int);
novaScript_int		readerPrint		    (BufferPointer const);
novaScript_int		readerLoad			(BufferPointer const, FILE* const);
novaScript_bool		readerRecover		(BufferPointer const);
novaScript_bool		readerRetract		(BufferPointer const);
novaScript_bool		readerRestore		(BufferPointer const);
/* Getters */
novaScript_byte		readerGetChar		(BufferPointer const);
novaScript_string	readerGetContent	(BufferPointer const, novaScript_int);
novaScript_int		readerGetPosRead	(BufferPointer const);
novaScript_int		readerGetPosWrte	(BufferPointer const);
novaScript_int		readerGetPosMark	(BufferPointer const);
novaScript_int		readerGetSize		(BufferPointer const);
novaScript_int		readerGetInc		(BufferPointer const);
novaScript_int		readerGetMode		(BufferPointer const);
novaScript_bool		readerGetFlags		(BufferPointer const);
novaScript_void		readerPrintStat		(BufferPointer const);
novaScript_int		readerNumErrors		(BufferPointer const);

#endif

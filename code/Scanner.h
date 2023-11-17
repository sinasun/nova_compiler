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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */
/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 22
/* TO_DO: Define Token codes - Create your token classes */
enum NOVASCRIPT_TOKENS {
	
	ERR_T,          /* Error token */
	MNID_T,         /* Method name identifier token */
	INL_T,          /* Integer literal token */
	FLL_T,          /* Float literal token */
	STR_T,         /* String literal token */
	LPR_T,          /* Left parenthesis '(' token */
	RPR_T,          /* Right parenthesis ')' token */
	LBR_T,          /* Left brace '{' token */
	RBR_T,          /* Right brace '}' token */
	SEMI_T,         /* Semicolon ';' token */
	COMMA_T,        /* Comma ',' token */
	OP_T,           /* Operator (e.g., '+', '-', '*', '/') token */
	CMP_T,          /* Comparison operator (e.g., '==', '<', '>') token */
	SEOF_T,         /* Source end-of-file token */
	CMT_T,           /* Comment token */
    EOS_T,		/*   End of statement (semicolon) */
	RTE_T,		/*  Run-time error token */
	KW_T,
	VAR_T,
	OPASSIGN_T,  /* '=' */
//	REOP_T,
	LOOP_T,
	
};

/* TO_DO: Define the list of keywords */
static string tokenStrTable[NUM_TOKENS] = {
	"Error",
	"Method Name Identifier",
	"Integer Literal",
	"Float Literal",
	"String Literal",
	"Left Parenthesis",
	"Right Parenthesis",
	"Left Brace",
	"Right Brace",
	"Semicolon",
	"Comma",
	"Operator",
	"Comparison Operator",
	"Source End-of-File",
	"Comment",
	"End-of-statement",
	"Run-time-error",
	"keyword",
	"variablename",
	"Assignmentoperator",
	//"Relationoperataor",
	"Logicaloperator",

};

/* TO_DO: Operators token attributes */

/* Arithmetic Operators */
typedef enum ArithmeticOperators {
	OP_ADD,   /* '+' */
	OP_SUB,   /* '-' */
	OP_MUL,   /* '*' */
	OP_DIV,   /* '/' */
} AriOperator;

/* Relational Operators */
typedef enum RelationalOperators {
	OP_EQ,    /* '@' */
	OP_NE,    /* '~' */
	OP_GT,    /* '>' */
	OP_LT,    /* '<' */
} RelOperator;

/* Logical Operators */
typedef enum LogicalOperators {
	OP_AND,   /* '&' */
	OP_OR,    /* '|' */
	OP_NOT    /* '!' */
} LogOperator;


	


/* Source End of File Markers */
typedef enum SourceEndOfFile {
	SEOF_0,    
	SEOF_255   
} EofOperator;


/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int intValue;				/* integer literal attribute (value) */
	int keywordIndex;			/* keyword index in the keyword table */
	int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float32 floatValue;				/* floating-point literal attribute (value) */
	rune idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	rune errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	rune flags;			/* Flags information */
	union {
		int intValue;				/* Integer value */
		float32 floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '"'
#define CHRCOL6 '#'
#define CHRCOL8 '.'

/* These constants will be used on VID / MID function */
#define MNID_SUF '('
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		100		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		14
#define CHAR_CLASSES	9


/* TO_DO: Transition table - type of states defined in separate table */
static int64 transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4),   E(5), C(6),  O(7)   P(8) */
	{     1, 10,   ESNR,  ESNR,   4,  ESWR,	  6,    ESNR,   ESNR},	 // S0: NOAS
	{     1,    1,    1,    2,	  3,    3,   3,     3,       3  },	// S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S2: ASNR (MVID)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S3: ASWR (KEY)
	{     4,    4,    4,    4,    5, ESWR,	  4,     4,      4},    // S4: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S5: ASNR (SL)
	{     6,    6,    6,    6,    6, ESWR,	  7,     6,       6},	// S6: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S7: ASNR (COM)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S8: ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},  // S9: ASWR (ER)
	{     11,    10,   11,  11,	 11,   11,    11,   11,      12},	// S10: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},	// S11: ASWR (INL_T)
	{     13,    12,   13,  13,	 13,   13,    13,   13,      13},    // S12: ASWR (
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,    FS,      FS},    //S13: 
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int64 stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	FSNR, /* 08 (Err1 - no retract) */
	FSWR,  /* 09 (Err2 - retract) */
    NOFS,   /*10 */
	FSWR,   /*11  (INL_T)  */
	 NOFS,   //12
	FSWR,     //13
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int64			startScanner(BufferPointer psc_buf);
static int64	nextClass(rune c);					/* character class function */
static int64	nextState(int64, rune);		/* state machine function */
void			printScannerData(ScannerData scData);
Token				tokenizer(void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL	(string lexeme);
Token funcIL	(string lexeme);
Token funcID	(string lexeme);
Token funcCMT   (string lexeme);
Token funcKEY	(string lexeme);
Token funcErr	(string lexeme);
Token funcFL    (string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	funcErr,	/* ERR1 [08] */
	funcErr,		/* ERR2 [09] */
	NULL,    /* - [10]*/
    funcIL,    /* [11]*/
	NULL,    //12
	funcFL,  //13

};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 17

/* TO_DO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
	"int",
	"float32",
	"bool",
	"string",
	"if",		
	"else",	
	"for",
	"break",
	"const",
	"continue",
	"func",
	"import",
	"package",
	"return",
	"var",
	"struct",
	"type",
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rune indentationCharType;
	int64 indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int64 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif

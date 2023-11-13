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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
    factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
*************************************************************
*/

BufferPointer readerCreate(int size, int increment, int mode)
{
    BufferPointer readerPointer;
    if (size <= 0 || increment <= 0 || (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI))
    {
        return NULL;
    }
    readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
    if (!readerPointer)
        return NULL;
    readerPointer->content = (string)malloc(size);

    if (!readerPointer->content)
    {
        free(readerPointer);
        return NULL;
    }

    for (int i = 0; i < NCHAR; i++)
    {
        readerPointer->histogram[i] = 0;
    }

    readerPointer->size = size;
    readerPointer->increment = increment;
    readerPointer->mode = mode;

    readerPointer->flags = 0;
    readerPointer->flags |= EMP_FLAG;
    /* NEW: Cleaning the content */
    if (readerPointer->content)
        readerPointer->content[0] = READER_TERMINATOR;
    readerPointer->position.wrte = 0;
    readerPointer->position.mark = 0;
    readerPointer->position.read = 0;
    return readerPointer;
}

/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer const readerPointer, rune ch)
{
    string tempReader = NULL;
    int newSize = 0;

    if (readerPointer == NULL || readerPointer->content == NULL)
    {
        return NULL;
    }

    readerPointer->flags &= ~REL_FLAG;
    if (readerPointer->position.wrte * (int)sizeof(rune) < readerPointer->size)
    {
        // no action needed
    }
    else
    {
        readerPointer->flags &= ~FUL_FLAG;

        switch (readerPointer->mode)
        {
        case MODE_FIXED:
            return NULL;
        case MODE_ADDIT:
            newSize = readerPointer->size + readerPointer->increment;
            if (newSize > READER_MAX_SIZE)
            {
                return NULL;
            }
            break;
        case MODE_MULTI:
            newSize = readerPointer->size * readerPointer->increment;
            if (newSize > READER_MAX_SIZE)
            {
                return NULL;
            }
            break;
        default:
            return NULL;
        }
        tempReader = (string)realloc(readerPointer->content, newSize);
        if (tempReader == NULL)
        {
            return NULL;
        }
        readerPointer->content = tempReader;
        readerPointer->size = newSize;
        readerPointer->flags |= REL_FLAG;
    }
    readerPointer->content[readerPointer->position.wrte++] = ch;
    if (ch >= 0)
    {
        readerPointer->histogram[ch]++;
    }

    return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerClear(BufferPointer const readerPointer)
{
    if (readerPointer == NULL || readerPointer->content == NULL)
    {
        return NOVASCRIPT_FALSE;
    }

    readerPointer->flags = READER_DEFAULT_FLAG;

    readerPointer->position.wrte = readerPointer->position.mark = readerPointer->position.read = 0;

    return NOVASCRIPT_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerFree(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }
    if (readerPointer->content != NULL)
    {
        free(readerPointer->content);
    }
    free(readerPointer);
    return NOVASCRIPT_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerIsFull(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }
    return (readerPointer->flags & FUL_FLAG) != 0 ? NOVASCRIPT_TRUE : NOVASCRIPT_FALSE;
}

/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerIsEmpty(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }
    return (readerPointer->flags & EMP_FLAG) != 0 ? NOVASCRIPT_TRUE : NOVASCRIPT_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerSetMark(BufferPointer const readerPointer, int mark)
{
    if (readerPointer == NULL || mark < 0 || mark > readerPointer->position.wrte)
    {
        return NOVASCRIPT_FALSE;
    }

    readerPointer->position.mark = mark;

    return NOVASCRIPT_TRUE;
}

/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
*************************************************************
*/
int readerPrint(BufferPointer const readerPointer)
{
    int cont = 0;
    rune c;

    if (readerPointer == NULL)
    {
        return 0;
    }

    c = readerGetChar(readerPointer);

    while (cont < readerPointer->position.wrte)
    {
        cont++;
        printf("%c", c);
        c = readerGetChar(readerPointer);
    }

    return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
    an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
*************************************************************
*/
int readerLoad(BufferPointer const readerPointer, FILE *const fileDescriptor)
{
    int size = 0;
    rune c;

    if (readerPointer == NULL || fileDescriptor == NULL)
    {
        return READER_ERROR;
    }

    c = (rune)fgetc(fileDescriptor);

    while (!feof(fileDescriptor))
    {
        if (!readerAddChar(readerPointer, c))
        {
            ungetc(c, fileDescriptor);
            return READER_ERROR;
        }

        c = (rune)fgetc(fileDescriptor);
        size++;
    }

    return size;
}
/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
*************************************************************
*/

bool readerRecover(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }

    readerPointer->position.read = 0;
    readerPointer->position.mark = 0;

    return NOVASCRIPT_TRUE;
}
/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerRetract(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }

    if (readerPointer->position.read > 0)
    {
        readerPointer->position.read--;
    }

    return NOVASCRIPT_TRUE;
}

/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerRestore(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return NOVASCRIPT_FALSE;
    }

    readerPointer->position.read = readerPointer->position.mark;

    return NOVASCRIPT_TRUE;
}

/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
*************************************************************
*/
rune readerGetChar(BufferPointer const readerPointer)
{
    if (readerPointer == NULL || readerPointer->position.read >= readerPointer->position.wrte)
    {
        readerPointer->flags |= END_FLAG;
        return READER_TERMINATOR;
    }

    readerPointer->flags &= ~END_FLAG;

    if (readerPointer->position.wrte > 0)
    {
        return readerPointer->content[readerPointer->position.read++];
    }
    return READER_TERMINATOR;
}

/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
*************************************************************
*/
string readerGetContent(BufferPointer const readerPointer, int pos)
{
    if (readerPointer == NULL || pos < 0 || pos >= readerPointer->position.wrte)
    {
        return NULL;
    }

    return readerPointer->content + pos;
}

/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
*************************************************************
*/
int readerGetPosRead(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->position.read;
}

/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
*************************************************************
*/
int readerGetPosWrte(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->position.wrte;
}

/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
*************************************************************
*/
int readerGetPosMark(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->position.mark;
}

/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
*************************************************************
*/
int readerGetSize(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
*************************************************************
*/
int readerGetInc(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
*************************************************************
*/
int readerGetMode(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
*************************************************************
*/
uint8 readerGetFlags(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return READER_ERROR;
    }

    return readerPointer->flags;
}

/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
*************************************************************
*/
void readerPrintStat(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return;
    }

    printf("Reader Statistics:\n");
    for (int i = 0; i < NCHAR; i++)
    {
        printf("B['%c']= %d, ", (char)i, readerPointer->histogram[i]);
    }
    printf("\n");
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
*************************************************************
*/
int readerNumErrors(BufferPointer const readerPointer)
{
    if (readerPointer == NULL)
    {
        return 0;
    }

    int numErrors = 0;
    for (int i = 0; i < NCHAR; i++)
    {
        if (i < 0 || i >= NCHAR || readerPointer->histogram[i] < 0)
        {
            numErrors++;
        }
    }

    return numErrors;
}

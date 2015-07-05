/* c4.c - C in four functions
*
* Data types : char, int, and pointer types.
* Conditional statements: if, while, return, and expression statements.
* Features: Just enough features to allow self-compilation and a bit more..

* Written by Robert Swierczek
* Edited and documented by Rishabh Chakrabarti 
* 
* Note: Since code is comparatively minimal and a bit compressed and without lay-friendly documentation, I have decided to comment the entire code for understanding. 
* 
* With reference from the website and the discussion that follows on it, 
* Source: https://news.ycombinator.com/item?id=8558822
* 
* There are three levels to consider:
* 1. Readability for modification
* 2. Readability for the "what"
* 3. Readability for the "why"
* 
* I have tried to keep these three levels in mind while documenting the whole code. 
* 
* Advice for newbies-> START from the main(). 
*/

#include <stdio.h> 
/* Library used for the basic input/output functions. 
 * Functions used -> 
 * 1. printf, 
 * 2. scanf.
 */
#include <stdlib.h> 
/*The standard library functions like - are linked from this library.
 * */
#include <memory.h> 
/* Memory header file for memory manipulation and memory allocation functions.
 * Functions used:
 * 1. malloc() 
 * */
#include <unistd.h> 
/* Description :
 * In the C and C++ programming languages, unistd.h is the name of the header file that provides access to the POSIX operating system API. 
 * It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any conforming (or quasi-conforming) operating system/compiler (all official versions of UNIX, including Mac OS X, GNU/Linux, etc.).
 * On Unix-like systems, the interface defined by unistd.h is typically made up largely of system call wrapper functions such as fork, pipe and I/O primitives (read, write, close, etc.).
 * Functions used from the following header:
 * 1. open()
 */

char *p, *lp, // For marking and maintaining the current position of the read pointer in the source code. Parsing the code files.
     *data;   // data/bss pointer 

int *e, *le,  // current position in emitted code
    *id,      // currently parsed identifier
    *sym,     // symbol table (simple list of identifiers)
// The above int pointers are declared for memory allocation in main. 
    tk,       // current token
    ival,     // current token value
    ty,       // current expression type
    loc,      // local variable offset
    line,     // current line number  
    src,      // print source and assembly flag
    debug;    // print executed instructions
// The following are enums without any identifiers, thus defining a number of constants to skip the step of maintaining a series of #defines
// The Different genres of constants:

// 1. Tokens and Classes (Operators are mentioned last and in order of precedence)
enum {
  Num = 128, Fun, Sys, Glo, Loc, Id,
  Char, Else, Enum, If, Int, Return, Sizeof, While,
  Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

// 2. Opcodes
enum { LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,
       OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,
       OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT };

// 3. Types
enum { CHAR, INT, PTR };

// 4. Identifier Offsets (since we can't create an ident struct)
enum { Tk, Hash, Name, Class, Type, Val, HClass, HType, HVal, Idsz };


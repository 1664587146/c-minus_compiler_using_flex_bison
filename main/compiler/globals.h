/****************************************************/
/* Module: globals.h                                */
/* Global types and vars for C-compiler             */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "cminus.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */
extern int lineno; /* source line number for listing */

/***********   Syntax tree for parsing ************/
typedef enum {STMTK, EXPK, VARK, SYSK} NodeKind;
typedef enum {INTEGERK, VOIDK, IFK, WHILEK, RETURNK, COMPK} StmtKind;
typedef enum {ATRIBK, RELK, ARITHK} ExpKind;
typedef enum {IDK, VECTORK, CONSTK, FUNCTIONK, CALLK} VarKind;
typedef enum {INPUT, OUTPUT} SysCallKind;
typedef enum {DECLK, ACCESSK} VarAccessK;
typedef enum {LOCALK, PARAMK, GLOBALK, FUNCTION_MEM} VarMemK;

/* ExpType is used for type checking.*/
typedef enum exp {VOID_TYPE, INTEGER_TYPE} ExpType;

#define MAXCHILDREN 3

typedef struct Identifier {
    VarKind varKind;
    VarMemK mem;
    VarAccessK access;
    struct ScopeRec * scope;
    union {
        int val;
        char * name;
    } attr;
} Identifier;

typedef struct treeNode {
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    NodeKind node;
    int lineno;
    union {
        StmtKind stmt;
        ExpKind exp;
        struct Identifier var;
        SysCallKind sys;
    } kind;
    TokenType op;
    ExpType type; /* for type checking of exps */
} TreeNode;

typedef struct codeInfo {
    char pgm[120];
} CodeInfo;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error;
#endif

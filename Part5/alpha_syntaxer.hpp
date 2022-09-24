/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ALPHA_SYNTAXER_HPP_INCLUDED
# define YY_YY_ALPHA_SYNTAXER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PLUS = 258,                    /* PLUS  */
    ASSIGNMENT = 259,              /* ASSIGNMENT  */
    MINUS = 260,                   /* MINUS  */
    MULTIPLICATION = 261,          /* MULTIPLICATION  */
    DIVISION = 262,                /* DIVISION  */
    MODULO = 263,                  /* MODULO  */
    PLUS_PLUS = 264,               /* PLUS_PLUS  */
    MINUS_MINUS = 265,             /* MINUS_MINUS  */
    UMINUS = 266,                  /* UMINUS  */
    EQUAL = 267,                   /* EQUAL  */
    NOT_EQUAL = 268,               /* NOT_EQUAL  */
    GREATER_THAN = 269,            /* GREATER_THAN  */
    LESS_THAN = 270,               /* LESS_THAN  */
    GREATER_OR_EQUAL = 271,        /* GREATER_OR_EQUAL  */
    LESS_OR_EQUAL = 272,           /* LESS_OR_EQUAL  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    WHILE = 275,                   /* WHILE  */
    FOR = 276,                     /* FOR  */
    FUNCTION = 277,                /* FUNCTION  */
    RETURN = 278,                  /* RETURN  */
    BREAK = 279,                   /* BREAK  */
    CONTINUE = 280,                /* CONTINUE  */
    AND = 281,                     /* AND  */
    OR = 282,                      /* OR  */
    NOT = 283,                     /* NOT  */
    LOCAL = 284,                   /* LOCAL  */
    TRUE = 285,                    /* TRUE  */
    FALSE = 286,                   /* FALSE  */
    NIL = 287,                     /* NIL  */
    LEFT_BRACE = 288,              /* LEFT_BRACE  */
    RIGHT_BRACE = 289,             /* RIGHT_BRACE  */
    LEFT_BRACKET = 290,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 291,           /* RIGHT_BRACKET  */
    LEFT_PAREN = 292,              /* LEFT_PAREN  */
    RIGHT_PAREN = 293,             /* RIGHT_PAREN  */
    SEMICOLON = 294,               /* SEMICOLON  */
    COMMA = 295,                   /* COMMA  */
    COLON = 296,                   /* COLON  */
    COLON_COLON = 297,             /* COLON_COLON  */
    DOT = 298,                     /* DOT  */
    DOT_DOT = 299,                 /* DOT_DOT  */
    COMM_LINE = 300,               /* COMM_LINE  */
    COMM_BLOCK = 301,              /* COMM_BLOCK  */
    UNDEFINED = 302,               /* UNDEFINED  */
    NEWLINE = 303,                 /* NEWLINE  */
    INTCONST = 304,                /* INTCONST  */
    REALCONST = 305,               /* REALCONST  */
    IDENT = 306,                   /* IDENT  */
    STRINGCONST = 307              /* STRINGCONST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PLUS 258
#define ASSIGNMENT 259
#define MINUS 260
#define MULTIPLICATION 261
#define DIVISION 262
#define MODULO 263
#define PLUS_PLUS 264
#define MINUS_MINUS 265
#define UMINUS 266
#define EQUAL 267
#define NOT_EQUAL 268
#define GREATER_THAN 269
#define LESS_THAN 270
#define GREATER_OR_EQUAL 271
#define LESS_OR_EQUAL 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define FOR 276
#define FUNCTION 277
#define RETURN 278
#define BREAK 279
#define CONTINUE 280
#define AND 281
#define OR 282
#define NOT 283
#define LOCAL 284
#define TRUE 285
#define FALSE 286
#define NIL 287
#define LEFT_BRACE 288
#define RIGHT_BRACE 289
#define LEFT_BRACKET 290
#define RIGHT_BRACKET 291
#define LEFT_PAREN 292
#define RIGHT_PAREN 293
#define SEMICOLON 294
#define COMMA 295
#define COLON 296
#define COLON_COLON 297
#define DOT 298
#define DOT_DOT 299
#define COMM_LINE 300
#define COMM_BLOCK 301
#define UNDEFINED 302
#define NEWLINE 303
#define INTCONST 304
#define REALCONST 305
#define IDENT 306
#define STRINGCONST 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "yyalpha.yacc"

	const char* stringVal;
	int intVal;
	double doubleVal;
	expr* expression;
	forstruct* forVal;
	callstruct* callVal;
	indexedstruct* pairVal;

#line 181 "alpha_syntaxer.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ALPHA_SYNTAXER_HPP_INCLUDED  */

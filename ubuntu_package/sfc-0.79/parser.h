/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CONFIGURATION = 258,
     COMMA = 259,
     EVENT_CONDITION = 260,
     FROM = 261,
     GOTO = 262,
     START = 263,
     USE = 264,
     WHEN = 265,
     APPLICATION = 266,
     NETWORK = 267,
     MAC = 268,
     RADIO = 269,
     ADDRESS = 270,
     SOURCE = 271,
     LF = 272,
     VIRTUAL_NETWORK = 273,
     LT = 274,
     GT = 275,
     LE = 276,
     GE = 277,
     NE = 278,
     EQ = 279,
     OPEN_BRACE = 280,
     CLOSE_BRACE = 281,
     OPEN_PARENTHESIS = 282,
     CLOSE_PARENTHESIS = 283,
     ONCE = 284,
     OPEN_SQUARE_BRACE = 285,
     CLOSE_SQUARE_BRACE = 286,
     LEVEL = 287,
     AT = 288,
     SHARED = 289,
     CONSTANT = 290,
     IDENTIFIER = 291,
     VARIABLE_LINE = 292,
     PATH = 293,
     RELOP = 294,
     AND = 295,
     OR = 296,
     NOT = 297,
     NOTHING = 298,
     ANY = 299,
     MODULES = 300
   };
#endif
/* Tokens.  */
#define CONFIGURATION 258
#define COMMA 259
#define EVENT_CONDITION 260
#define FROM 261
#define GOTO 262
#define START 263
#define USE 264
#define WHEN 265
#define APPLICATION 266
#define NETWORK 267
#define MAC 268
#define RADIO 269
#define ADDRESS 270
#define SOURCE 271
#define LF 272
#define VIRTUAL_NETWORK 273
#define LT 274
#define GT 275
#define LE 276
#define GE 277
#define NE 278
#define EQ 279
#define OPEN_BRACE 280
#define CLOSE_BRACE 281
#define OPEN_PARENTHESIS 282
#define CLOSE_PARENTHESIS 283
#define ONCE 284
#define OPEN_SQUARE_BRACE 285
#define CLOSE_SQUARE_BRACE 286
#define LEVEL 287
#define AT 288
#define SHARED 289
#define CONSTANT 290
#define IDENTIFIER 291
#define VARIABLE_LINE 292
#define PATH 293
#define RELOP 294
#define AND 295
#define OR 296
#define NOT 297
#define NOTHING 298
#define ANY 299
#define MODULES 300




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 66 "parser.y"

	struct symtab		*symp;
	struct modtab		*modp;
	struct libtab		*libp;
	int 			ival;
	char 			*str;
	double			dval;
	struct confnode		*confp;
	struct confnodes	*confsp;
	struct eventnode	*evep;
	struct eventnodes	*evesp;
	struct policy		*pol;
	struct policies		*pols;
	struct initnode		*initp;
	struct program		*prog;
	struct variable		*var;
	struct variables	*vars;
	struct paramtype	*mtl;
	struct paramvalue	*parv;
	struct defvalue		*defv;



/* Line 2068 of yacc.c  */
#line 164 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



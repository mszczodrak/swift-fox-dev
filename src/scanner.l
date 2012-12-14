%{
/*  
    Swift Fox Compiler
    Copyright (C) 2009-2012 Marcin Szczodrak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#ifdef __DEBUG__	/* link with the testing suite */
#include <unistd.h>
#include "common.h"
#else			/* link with YACC/Bison */
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include "parser.h"
#include "sf.h"

#define YY_NO_INPUT
#endif

%}

%option nounput

delim		[ \v\f\r]
tab		\t+
fixed_keys	[NODE|BRIDGE|UNKNOWN|BROADCAST]
whitespace	{delim}+
letter		[A-Za-z]
digit		[0-9]
number		[1-9]{digit}*
newline		\n.*
identifier	({letter}|_)({letter}|{digit}|_)*
module_param	{digit}|,|{whitespace}|{fixed_keys}
modules		{identifier}\({module_param}*\)
numtype		(C|F|msec|sec|min|hr)
constant	{digit}|{number}{numtype}?|ON|OFF
env_const	\$\(({letter}|{digit}|_)*\)
path		(http:\/\/|\.|\/|{env_const})({letter}|{digit}|\.|\/|_|-|~)*
comment		#.*

%%

{newline}       {
#ifndef __DEBUG__
			(void)memset(linebuf, 0, BUF_SZ);
			strncpy(linebuf, yytext + 1, BUF_SZ - 1); lineno++; 
			tokenpos = 0; yyless(1);
#else
			yyless(1);
#endif
			return LF;    				}
{tab}		{
#ifndef __DEBUG__
			tokenpos += ((yyleng*5) + (yyleng - 1) * 3);
#endif
								}


{whitespace}	{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
							}
{comment}	{
#ifndef __DEBUG__
			tokenpos = 0; 		
#endif
							}
any		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.symp = symlook(yytext);
#endif
			return ANY;			}
(configuration|conf)	{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return CONFIGURATION;		}
,		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return COMMA;			}

(nothing|none)	{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.symp = symlook(yytext);
#endif
			return NOTHING;			}
(event-condition|event)	{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return EVENT_CONDITION;		}
from		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return FROM;			}
goto		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return GOTO;			}


start		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return START;			}

(at|@)           {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return AT;                   }

shared           {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return SHARED;                   }

level           {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return LEVEL;                   }


l           {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return LEVEL;                   }



use		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return	USE;			}
application	{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif	
			return APPLICATION;		}
network		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return NETWORK;			}
mac         {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return MAC;                 }
radio         {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return RADIO;                 }
address         {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return ADDRESS;                 }
source		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return SOURCE;			}
once		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return ONCE;			}
when		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return WHEN;			}
and		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = AND; 
#endif
			return AND;			}
or		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = OR; 
#endif
			return OR;			}
not		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = NOT; 
#endif
			return NOT;			}
"<"		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = LT;
#endif
			return RELOP;			}
">"		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = GT;
#endif
			return RELOP;			}
"<="		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = LE;
#endif
			return RELOP;			}
">="		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = GE;
#endif
			return RELOP;			}
"<>"		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = NE;
#endif
			return RELOP;			}
"="		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.ival = EQ;
#endif
			return RELOP;			}
\{		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return OPEN_BRACE;		}
\}		{
#ifndef __DEBUG__
			tokenpos += yyleng;
#endif
			return CLOSE_BRACE;		}

\(              {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return OPEN_PARENTHESIS;              }
\)              {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
			return CLOSE_PARENTHESIS;		}


"["              {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return OPEN_SQUARE_BRACE;              }
"]"              {
#ifndef __DEBUG__
                        tokenpos += yyleng;
#endif
                        return CLOSE_SQUARE_BRACE;               }

{identifier}	{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.symp = symlook(yytext);
#endif
			return IDENTIFIER;		}

{path}		{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.libp = liblook(yytext);
#endif
			return PATH;			}
{constant}	{
#ifndef __DEBUG__
			tokenpos += yyleng;
			yylval.symp = symlook(yytext);
#endif
			return CONSTANT;		}

virtual-network	{
			return VIRTUAL_NETWORK;		}

%%

#ifdef __DEBUG__	/* link with the testing suite */
int
main(int argc, char **argv) {

	int tok;	/* token from the scanner */

        /* try to open the first argument for input */
        if ((argc != 1) && ((yyin = fopen(argv[1], "r")) == NULL))
		/* failed */
		yyin = stdin;	/* read from stdin */

	/* call the scanner repetitively */
	while ((tok = yylex()) != 0)
		/* print the identified token */
		(void)fprintf(stdout, "%d ", tok);
	/* EOL */
	(void)fprintf(stdout, "\n");
	
	/* cleanup */
	(void)fclose(yyin);

	/* finish */
	return EXIT_SUCCESS;
}
#endif
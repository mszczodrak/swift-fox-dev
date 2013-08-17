#define CONFIGURATION 257
#define COMMA 258
#define EVENT_CONDITION 259
#define FROM 260
#define GOTO 261
#define START 262
#define USE 263
#define WHEN 264
#define APPLICATION 265
#define NETWORK 266
#define MAC 267
#define RADIO 268
#define ADDRESS 269
#define SOURCE 270
#define LF 271
#define VIRTUAL_NETWORK 272
#define LT 273
#define GT 274
#define LE 275
#define GE 276
#define NE 277
#define EQ 278
#define OPEN_BRACE 279
#define CLOSE_BRACE 280
#define OPEN_PARENTHESIS 281
#define CLOSE_PARENTHESIS 282
#define ONCE 283
#define OPEN_SQUARE_BRACE 284
#define CLOSE_SQUARE_BRACE 285
#define LEVEL 286
#define AT 287
#define SHARED 288
#define CONSTANT 289
#define IDENTIFIER 290
#define VARIABLE_LINE 291
#define PATH 292
#define RELOP 293
#define AND 294
#define OR 295
#define NOT 296
#define NOTHING 297
#define ANY 298
#define MODULES 299
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

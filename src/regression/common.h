/* regression testing suite for scanner */

/* token names */
enum TOKEN_NAME {
	ANY = 1, APPLICATION,				/* 1, 2 */
	NOT,						/* 3 */
	COMMA, CONFIGURATION, CONSTANT,	 CLOSE_BRACE, 	/* 4, 5, 6, 7 */
	EVENT_CONDITION,				/* 8 */
	FROM,						/* 9 */
	GOTO,						/* 10 */
	IDENTIFIER,					/* 11 */
	LF,						/* 12 */
	NETWORK, NOTHING,				/* 13, 14 */
	ONCE, OPEN_BRACE,				/* 15, 16 */
	PATH,						/* 17 */
	RELOP,						/* 18 */
	SOURCE,						/* 19 */
	START,						/* 20 */
	USE,						/* 21 */
	WHEN,						/* 22 */
	AND,						/* 23 */
	OR 						/* 24 */
};

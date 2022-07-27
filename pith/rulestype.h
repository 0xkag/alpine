#ifndef PITH_RULESTYPE_INCLUDED
#define PITH_RULESTYPE_INCLUDED

typedef struct rule {
	char *result;	/* The result of the rule */
	int number;	/* The number of the rule that succeded, -1 if not */
} RULE_RESULT;

typedef struct {
        char    *value;
        int     type;
} RULE_ACTION;


#define TOKEN_VALUE	struct tokenvalue_s
#define CONDITION_S	struct condition_s
#define REXSUB_S	struct rexsub_s
#define RULEACTION_S	struct ruleaction_s
#define RULE_S		struct rule_s
#define RULELIST	struct rulelist_s
#define PRULELIST_S	struct parsedrulelist_s

#define FREEREGEX	1

#define UNDEFINED_TYPE	0
#define CHAR_TYPE	1
#define REXSUB_TYPE	2

TOKEN_VALUE {
	char	*testxt;
	void	*voidtxt;
	int	voidtype;
	int	codefcn;
	TOKEN_VALUE *next;
};

typedef enum {Equal, Subset, Includes, NotEqual, NotSubset, NotIncludes, EndTypes} TestType;

typedef enum {And, Or, ParOpen, ParClose, Condition} CondType;

typedef struct condvalue_s {
    char	*tname;		/* tname ttype {value} */
    TestType	ttype;		/* type of rule */
    TOKEN_VALUE	*value;		/* value to check against */
} CONDVALUE_S;

CONDITION_S {
    void     *cndrule;		/* text in condition */
    CondType  cndtype;		/* type of object    */
    CONDITION_S	*next;		/* next condition to test */
};

#define COND(C)  ((CONDVALUE_S *)((C)->cndrule))

RULEACTION_S {
   char *token;		/* token := function{value} or token = null  */
   char *function;	/* token := function{value} or simply function{value}*/
   TOKEN_VALUE  *value; /* token := function{value} or simply function{value}*/
   int   context;	/* context in which this rule can be used */
   char* (*exec)();
};

REXSUB_S {
   char *pattern;	/* pattern to use in the replacement	     */
   char *text;		/* text to replace			     */
   int   times;		/* how many times to repeat the substitution */
};

RULE_S {
  CONDITION_S  *condition;
  RULEACTION_S *action;
};

RULELIST {
   RULE_S *prule;
   RULELIST *next;
};

PRULELIST_S {
   int varnum;		/* number associated to the variable */
   RULELIST *rlist;
   PRULELIST_S *next;
};

#define USE_RAW_SP      0x001
#define PROCESS_SP      0x010

typedef struct sparep {
   int flag;
   char *value;
} SPAREP_S;


#endif	/* PITH_RULESTYPE_INCLUDED */

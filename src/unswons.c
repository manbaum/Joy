/*
    module  : unswons.c
    version : 1.2
    date    : 05/17/22
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
2130  unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
PRIVATE void unswons_(pEnv env)
{
    ONEPARAM("unswons");
    switch (nodetype(env->stck)) {
    case SET_: {
        int i = 0;
        long set = nodevalue(env->stck).set;
        CHECKEMPTYSET(set, "unswons");
        while (!(set & ((long)1 << i)))
            i++;
        UNARY(SET_NEWNODE, set & ~((long)1 << i));
        NULLARY(INTEGER_NEWNODE, i);
        break;
    }
    case STRING_: {
        char *s = nodevalue(env->stck).str;
        CHECKEMPTYSTRING(s, "unswons");
        UNARY(STRING_NEWNODE, GC_strdup(++s));
        NULLARY(CHAR_NEWNODE, *--s);
        break;
    }
    case LIST_:
        SAVESTACK;
        CHECKEMPTYLIST(nodevalue(SAVED1).lis, "unswons");
        UNARY(LIST_NEWNODE, nextnode1(nodevalue(SAVED1).lis));
        GNULLARY(
            nodetype(nodevalue(SAVED1).lis), nodevalue(nodevalue(SAVED1).lis));
        POP(env->dump);
        return;
    default:
        BADAGGREGATE("unswons");
    }
}
#endif

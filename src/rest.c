/*
    module  : rest.c
    version : 1.2
    date    : 05/17/22
*/
#ifndef REST_C
#define REST_C

/**
2050  rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
PRIVATE void rest_(pEnv env)
{
    ONEPARAM("rest");
    switch (nodetype(env->stck)) {
    case SET_: {
        int i = 0;
        CHECKEMPTYSET(nodevalue(env->stck).set, "rest");
        while (!(nodevalue(env->stck).set & ((long)1 << i)))
            i++;
        UNARY(SET_NEWNODE, nodevalue(env->stck).set & ~((long)1 << i));
        break;
    }
    case STRING_: {
        char *s = nodevalue(env->stck).str;
        CHECKEMPTYSTRING(s, "rest");
        UNARY(STRING_NEWNODE, GC_strdup(++s));
        break;
    }
    case LIST_:
        CHECKEMPTYLIST(nodevalue(env->stck).lis, "rest");
        UNARY(LIST_NEWNODE, nextnode1(nodevalue(env->stck).lis));
        return;
    default:
        BADAGGREGATE("rest");
    }
}
#endif

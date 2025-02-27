/*
    module  : concat.c
    version : 1.2
    date    : 05/17/22
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
2160  concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
PRIVATE void concat_(pEnv env)
{
    TWOPARAMS("concat");
    SAME2TYPES("concat");
    switch (nodetype(env->stck)) {
    case SET_:
        BINARY(SET_NEWNODE,
            nodevalue(nextnode1(env->stck)).set | nodevalue(env->stck).set);
        return;
    case STRING_: {
        char *s, *p;
        s = p = (char *)GC_malloc_atomic(
            strlen(nodevalue(nextnode1(env->stck)).str)
            + strlen(nodevalue(env->stck).str) + 1);
        strcpy(s, nodevalue(nextnode1(env->stck)).str);
        strcat(s, nodevalue(env->stck).str);
        BINARY(STRING_NEWNODE, s);
        return;
    }
    case LIST_:
        if (!nodevalue(nextnode1(env->stck)).lis) {
            BINARY(LIST_NEWNODE, nodevalue(env->stck).lis);
            return;
        }
        env->dump1 = LIST_NEWNODE(
            nodevalue(nextnode1(env->stck)).lis, env->dump1); /* old */
        env->dump2 = LIST_NEWNODE(0L, env->dump2); /* head */
        env->dump3 = LIST_NEWNODE(0L, env->dump3); /* last */
        while (DMP1) {
            if (!DMP2) { /* first */
                DMP2 = NEWNODE(nodetype(DMP1), nodevalue(DMP1), 0);
                DMP3 = DMP2;
            } else { /* further */
                nextnode1(DMP3)
                    = NEWNODE(nodetype(DMP1), nodevalue(DMP1), 0);
                DMP3 = nextnode1(DMP3);
            };
            DMP1 = nextnode1(DMP1);
        }
        nextnode1(DMP3) = nodevalue(env->stck).lis;
        BINARY(LIST_NEWNODE, DMP2);
        POP(env->dump1);
        POP(env->dump2);
        POP(env->dump3);
        return;
    default:
        BADAGGREGATE("concat");
    }
}
#endif

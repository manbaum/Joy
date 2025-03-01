/*
    module  : formatf.c
    version : 1.2
    date    : 05/02/22
*/
#ifndef FORMATF_C
#define FORMATF_C

/**
1770  formatf  :  F C I J  ->  S
S is the formatted version of F in mode C
('e or 'E = exponential, 'f = fractional,
'g or G = general with lower or upper case letters)
with maximum width I and precision J.
*/
PRIVATE void formatf_(pEnv env)
{
    int width, prec;
    char spec, format[7], *result;
#ifdef USE_SNPRINTF
    int leng;
#endif
    FOURPARAMS("formatf");
    INTEGERS2("formatf");
    prec = nodevalue(env->stck).num;
    POP(env->stck);
    width = nodevalue(env->stck).num;
    POP(env->stck);
    CHARACTER("formatf");
    spec = (char)nodevalue(env->stck).num;
    POP(env->stck);
    CHECKFORMATF(spec, "formatf");
    strcpy(format, "%*.*lg");
    format[5] = spec;
    FLOAT("formatf");
#ifdef USE_SNPRINTF
    leng = snprintf(0, 0, format, width, prec, nodevalue(env->stck).num) + 1;
    result = GC_malloc_atomic(leng + 1);
    snprintf(result, leng, format, width, prec, nodevalue(env->stck).dbl);
#else
    result = GC_malloc_atomic(INPLINEMAX); /* should be sufficient */
    sprintf(result, format, width, prec, nodevalue(env->stck).dbl);
#endif
    UNARY(STRING_NEWNODE, result);
}
#endif

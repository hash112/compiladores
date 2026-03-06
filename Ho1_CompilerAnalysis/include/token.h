#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
    char *val;
    enum 
    {
        TOKEN_KEYWORD,
        TOKEN_REG,
        TOKEN_MEM,
        TOKEN_COMMA,
    };
};

#endif
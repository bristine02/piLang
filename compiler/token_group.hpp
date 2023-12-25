#pragma once
#include <cstddef>

enum TokenGroupType
{
    TOKEN_GROUP_MODULE_HEADER,
    TOKEN_GROUP_LIB_INSTANCE,
    TOKEN_GROUP_MODULE_END
};
typedef struct
{
    TokenGroupType tokenGroupType;
    size_t tokens_start; // Index of first token in token group.
    size_t tokens_length;      // number of tokens in token group
} TokenGroup;
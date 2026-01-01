#include "c17_strict.h"
#include <string.h>
#include <stdlib.h>
// C17 clean implementation of common C/POSIX functions which may not be always available

char *c17_strdup(const char *str)
{
    size_t len;
    char *copy;

    len = strlen(str) + 1;
    if ((copy = malloc(len)) == NULL)
        return (NULL);
    memcpy(copy, str, len);
    return (copy);
}

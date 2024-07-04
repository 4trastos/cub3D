#include "../incl/cube3d.h"

int ft_strmapcmp(char *str, char *dst, int len)
{
    int i;

    if (str[0] == '.')
        return (1);
    i = ft_strlen(str) - 1;
    while (len > 0 && dst[len] == str[i])
    {
        if (dst[len] != str[i])
            return (1);
        len--;
        i--;
    }
    return (0);
}
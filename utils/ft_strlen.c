#include "../incl/cube3d.h"

int ft_strlen(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}
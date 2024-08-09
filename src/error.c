#include "../incl/cube3d.h"

void    error_msg(char *str, char **map)
{
    int i;

    if (map)
        free(map);
    i = 0;
    while (*str)
        write(1, str++, 1);
    write(1, "\n", 1);
    exit (1);    
}
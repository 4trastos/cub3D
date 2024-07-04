#ifndef CUBE3D_H
# define CUBE3D_h

# define SIZE 64

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

//*** STRUCTS ***//

typedef struct s_design
{
    /* data */
}   t_design;

typedef struct s_game
{
    /* data */
}   t_game;


//*** INIT ***//

int     main(int argc, char **argv);

//*** GAME ***//



//*** PARSE ***//

char    **arg_check(int argc, char **argv, t_design *design, char **map);

//*** UTILS ***//

int     ft_strmapcmp(char *str, char *dst, int len);
int     ft_strlen(char *str);

//*** ERRORS ***//

void    error_msg(char *str, char **map);

#endif
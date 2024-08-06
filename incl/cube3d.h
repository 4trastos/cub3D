/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:37:02 by davgalle          #+#    #+#             */
/*   Updated: 2024/08/06 10:30:14 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define SIZE 64
# define BUFFER_SIZE 2
# define RIGHT -1
# define LEFT +1
# define UP -1
# define DOWN +1

// # include "../minilibx-linux/mlx.h"
// # include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include "game.h"

//*** STRUCTS ***//

typedef struct s_move
{
	bool	right;
	bool	left;
	bool	up;
	bool	down;
}	t_move;

typedef struct s_design
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				floor[3];
	int				ceiling[3];
	bool			floor_set;
	bool			ceiling_set;
	size_t			px;
	size_t			py;
}	t_design;

typedef struct s_game
{
	t_design		*cartridge;

}	t_game;

typedef struct s_brain
{
	t_design			*cartridge;
	t_game				*game;
	t_move				*move;
	int					init_x;
	int					init_y;
	bool				drowned;
	bool				right;
	bool				left;
	bool				up;
	bool				down;
	unsigned long long	init_coord;

}	t_brain;

//*** INIT ***//

int				main(int argc, char **argv);

//*** STRUCTS ***//

void			new_design(t_design *new);
void			new_brain(t_brain *new);
t_game			*new_game(void);
void			create_cartridge(char **data, t_design *cartridge,
					size_t y);
void			free_struct(t_design *cartridge);

//*** GAME ***//

//*** PARSE ***//

char			**arg_check(int argc, char **argv, t_design *cartridge,
					char **map);
char			**map_check(int fd, t_design *cartridge, char **map,
					t_brain *brain);
int				char_validator(char **map);
int				coordinates(char *str, t_design *cartridge);
int				get_coordinates(char *str, t_design *cartridge, int flag);
int				ft_colours(char *str, t_design *cartridge);
int				map_validator(char **map, t_brain *brain);
int				player_validator(char **map);
char			*read_file(int fd, char *str);
char			**dupmatrix(char **str);
void			upcolour_f(char **number, t_design *cartridge);
void			upcolour_c(char **number, t_design *cartridge);
void			skip_space(char *str, int *x);

//*** UTILS ***//

int				ft_strmapcmp(char *str, char *dst, int len);
size_t			ft_strlen(char *str);
int				ft_strlencust(char *str);
void			ft_putstr(char *str);
char			*ft_strdup(char *str);
char			*ft_strchr(char *str, int c);
char			*ft_strjoin(char *str, char *dstr);
void			skip_whitespace(char **str);
int				ft_countlines(char **str);
int				ft_mtx_len(char **mtx);
int				get_prev(char *str);

//*** ERRORS & FREE ***//

void			error_msg(char *str, char **map);
void			free_map(char **map);
void			free_coordinates(t_design *cartridge);
void			free_struct(t_design *cartridge);

//*** FT_SPLIT ***//

char			**ft_empty_split(void);
char			*ft_strdup_custom(const char *s, size_t n);
char			**ft_free_str(char **aux);
int				ft_countc(char const *s, char c);
char			**ft_split(char const *s, char c);

//*** GET NEXT LINE ***//

char			*ft_new_line(char *board);
char			*ft_line(char *board);
char			*ft_read(int fd, char *board);
char			*get_next_line(int fd);

//*** FT_ITOA ***//

unsigned int	ft_numlen(int n);
char			*ft_itoa(int n);

//*** FT_ATOI ***//

int				ft_count(char *str, int i);
int				ft_atoi(char *str);

//*** WALKING THE WALL ***//

void			save_init(int y, int x, t_brain *brain);
void			walking_border(t_brain *brain, char **map, int *y, int *x);
void			updgrade_current(unsigned long long *current, char **map,
					int *y, int *x);
int				walking_the_wall(char **map, t_brain *brain);	
void			ft_printmap(char **map);
void			reset_move(t_brain *brain);
void			first_line(t_brain *brain, char **map, int *y, int *x);
void			last_line(t_brain *brain, char **map, int *y, int *x);
void			intermediate_lines(t_brain *brain, char **map, int *y, int *x);
void			last_position(t_brain *brain, char **map, int *y, int *x);
void			first_position(t_brain *brain, char **map, int *y, int *x);

#endif
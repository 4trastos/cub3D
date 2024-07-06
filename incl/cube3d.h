/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:37:02 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/06 21:39:46 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define SIZE 64
# define BUFFER_SIZE 2

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

//*** STRUCTS ***//

typedef struct s_design
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	size_t	px;
	size_t	py;
}	t_design;

typedef struct s_game
{
	t_design	*cartridge;

}	t_game;

//*** INIT ***//

int			main(int argc, char **argv);

//*** STRUCTS ***//

t_design	*new_design(void);
t_game		*new_game(void);
void		create_cartridge(char **data, t_design *cartridge, size_t x, size_t y);

//*** GAME ***//

//*** PARSE ***//

char		**arg_check(int argc, char **argv, t_design *cartridge, char **map);
char		**map_check(int fd, t_design *cartridge, char **map);
int			char_validator(char *str);
int			coordinates(char *str, t_design *cartridge, size_t x);
int			ft_colours(char *str, t_design *cartridge, size_t x, size_t y);
int			map_validator(char **data, t_design *cartridge, size_t y);
int			walls_validator(char **copy);
char		*read_file(int fd, char *str);

//*** UTILS ***//

int			ft_strmapcmp(char *str, char *dst, int len);
size_t		ft_strlen(char *str);
void		ft_putstr(char *str);
char		*ft_strdup(char *str);
char		*ft_strchr(char *str, int c);
char		*ft_strjoin(char *str, char *dstr);

//*** ERRORS ***//

void		error_msg(char *str, char **map);
void		free_map(char **map);

//*** FT_SPLIT ***//

char		**ft_empty_split(void);
char		*ft_strdup_custom(const char *s, size_t n);
char		**ft_free_str(char **aux);
int			ft_countc(char const *s, char c);
char		**ft_split(char const *s, char c);

//*** GET NEXT LINE ***//

char		*ft_new_line(char *board);
char		*ft_line(char *board);
char		*ft_read(int fd, char *board);
char		*get_next_line(int fd);

#endif
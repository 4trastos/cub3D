/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:37:02 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/05 13:31:52 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define SIZE 64
# define BUFFER_SIZE 42

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>

//*** STRUCTS ***//

typedef struct s_error
{
	char	wall;
	char	space;
	char	exit;
	char	player;
	char	collects;
	char	enemys;

}	t_error;

typedef struct s_design
{

}	t_design;

//*** INIT ***//

int			main(int argc, char **argv);

//*** STRUCTS ***//

t_design	*new_design(void);
t_error		*new_error(void);

//*** GAME ***//

//*** PARSE ***//

char		**arg_check(int argc, char **argv, t_design *design, char **map);
char		**map_check(int fd, t_design *design, char **map);
int			char_validator(char *str);

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:03:06 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/12 11:34:56 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "cube3d.h"

# define N 0b01001110    // ASCII de 'N' = 78
# define O 0b01001111    // ASCII de 'O' = 79
# define S 0b01010011    // ASCII de 'S' = 83
# define E 0b01000101    // ASCII de 'E' = 69
# define W 0b01010111    // ASCII de 'W' = 87
# define A 0b01000001    // ASCII de 'A' = 65

# define NO 20047   // N(78) << 8 | O(79) = 157
# define SO 21327   // S(83) << 8 | O(79) = 183
# define WE 22341   // W(87) << 8 | E(69) = 231
# define EA 17729   // E(69) << 8 | A(65) = 229

//*** BITWISE ***//

void			print_bits(unsigned char octet);
unsigned char	reverse_bits(unsigned char octet);
unsigned char	swap_bits(unsigned char octet);
unsigned int	pack_coordinates(int y, int x);
void			unpack_coord(unsigned int packed, int *y, int *x);

//*** MORE UTILS ***//

void			skip_space(char *str, int *x);


#endif
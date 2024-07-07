/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:49:49 by davgalle          #+#    #+#             */
/*   Updated: 2024/07/07 10:44:25 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cube3d.h"

int ft_countlines(char **str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i] != NULL)
        i++;
    return (i);
}

void    skip_whitespace(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

char    **dupmatrix(char **str)
{
    char    **new;
    int     len;
    int     i;

    if (!str)
        return (NULL);
    len = ft_countlines(str);
    new = (char **)malloc(sizeof(char *) * (len + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (i < len && str[i] != NULL)
    {
        new[i] = ft_strdup(str[i]);
        i++;
    }
    new[i] = NULL;
    return (new);
}


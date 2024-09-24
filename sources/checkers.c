/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:49:12 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/15 13:49:13 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	file_check(t_data *img)
{
	int	i;

	i = 0;
	img->line[i] = get_next_line(img->fd); // if can't open then file error
	while (img->line[i])
	{
		ft_printf("%s", img->line[i]);		// APAGAR
		img->line[++i] = get_next_line(img->fd);
		img->rows++;
	}
	i = 0;
	while (img->line[0][i])
	{
		if (img->line[0][i] == ' ' && ft_isdigit(img->line[0][i+1]))
			img->col++;
		i++;
	}
	img->col++;
	close(img->fd);
	return (1);
}


int	number_check(t_data *img)
{
	int		i;
	int		j;
	int		old;
	double	**points;
	char	**tab;

	i = 0;
	old = 0;
	points = alloc_points(img);
	if (!points)
		return(0);
	i = 0;
	while (img->line[i])
	{
		j = 0;
		tab = ft_split(img->line[i], ' ');	// Faz o split da tabela pro numeros
		if (!tab)
		{
			while (i > 0)
				free(points[--i]);
			free(points);
			return (0);
		}
		while (tab[j])
		{
			points[i][j] = ft_atoi(tab[j]);
			j++;
		}
		if (old == 0)
			old = j;
		img->col = old;
		if (j != old)				// Confere se os tamanhos de todas as linhas sao iguais
		{
			file_error(2);
			return (0);
		}
		i++;
		free(tab);
	}
	img->points = points;
	i = 0;
	return (1);
}
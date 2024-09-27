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

/* int	file_check(t_data *img)
{
	int		i;
	char	**line;

	i = 0;
	img->line[i] = get_next_line(img->fd);
	printf("\n\nA\n\n");
	while (img->line[i])
	{
		//ft_printf("%s", img->line[i]);		// APAGAR
		img->rows++;
		i++;
		img->line[i] = get_next_line(img->fd);
	}
	i = 0;
	while (img->line[0][i])
	{
		if (img->line[0][i] == ' ' && ft_isdigit(img->line[0][i+1]))
			img->col++;
		i++;
	}
	img->col++;
	if (number_check() == 0)
	{
		return (0);
	}
	
	close(img->fd);
	return (1);
}
 */

/* int	file_check(t_data *img)
{
	int		i;
	char	**line;

	i = 0;
	line = NULL;
	line[i] = get_next_line(img->fd);
	while (line[i])
	{
		img->rows++;
		i++;
		line[i] = get_next_line(img->fd);
	}
	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == ' ' && ft_isdigit(line[0][i+1]))
			img->col++;
		i++;
	}
	img->col++;
	if (number_check(img, line) == 0)
	{
		return (0);
	}
	close(img->fd);
	return (1);
} */

/* int	file_check(t_data *img)
{
	int		i;
	char	**line;

	i = 0;
	line[i] = NULL;
	line[i] = get_next_line(img->fd);
	printf("\n\nA\n\n");
	while (line[i])
	{
		//ft_printf("%s", img->line[i]);		// APAGAR
		img->rows++;
		i++;
		line[i] = get_next_line(img->fd);
	}
	i = 0;
	while (line[0][i])
	{
		if (line[0][i] == ' ' && ft_isdigit(line[0][i+1]))
			img->col++;
		i++;
	}
	img->col++;
	if (number_check(img, line) == 0)
	{
		return (0);
	}
	close(img->fd);
	return (1);
} */

int file_check(t_data *img)
{
    int     i;
    char    *line;
    char    **split_line;
    char    **all_lines;
    int     line_count;

    img->rows = 0;
    img->col = 0;
    line_count = 0;
    all_lines = (char **)malloc(sizeof(char *) * 1000);
    if (!all_lines)
        return (0);
    line = get_next_line(img->fd);
    while (line)
    {
        all_lines[line_count] = line;
        line_count++;
        img->rows++;
        if (img->rows == 1)
        {
            split_line = ft_split(line, ' ');
            if (!split_line)
            {
                free(line);
                return (0);
            }
            i = 0;
            while (split_line[i])
            {
                img->col++;
                i++;
            }
            i = 0;
            while (split_line[i])
            {
                free(split_line[i]);
                i++;
            }
            free(split_line);
        }
        line = get_next_line(img->fd);
    }
    if (number_check(img, all_lines) == 0)
    {
        for (i = 0; i < line_count; i++)
            free(all_lines[i]);
        free(all_lines);
        close(img->fd);
        return (0);
    }
    for (i = 0; i < line_count; i++)
        free(all_lines[i]);
    free(all_lines);
    close(img->fd);
    return (1)
}

int	number_check(t_data *img, char **line)
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
	while (line[i])
	{
		j = 0;
		tab = ft_split(line[i], ' ');	// Faz o split da tabela pro numeros
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
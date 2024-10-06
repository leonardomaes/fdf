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

int	count_cols(char *line, int expected_cols)
{
	char	**split_line;
	int	cols;

	split_line = ft_split(line, ' ');
	cols = 0;
	while (split_line[cols])
	{
			cols++;
	}
	free_split(split_line);
	if (expected_cols == 0)
		return (cols);
	if (cols != expected_cols)
		return (-1);
	return (cols);
}

t_info	*read_map(t_data *fdf)
{
	int		fd;
	int		cols;
	char	*line;
	t_info	*map;

	map = malloc(sizeof(t_info));
	map->cols = 0;
	map->rows = 0;
	fd = open(fdf->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ERROR:\nFile doesn't exist or couldn't open!\n");
		exit (1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("ERROR:\nFile can't be readed!\n");
		close(fd);
		return (NULL);
	}
	while (line)
	{
		line = ft_strtrim(line, "\n");
		cols = count_cols(line, map->cols);
		if (cols == -1)
		{
			ft_printf("ERROR:\nMap in wrong format, check the edges!\n");
			exit(1);
		}
		if (map->cols == 0)
		{
			map->cols = cols;
		}
		free(line);
		line = get_next_line(fd);
		map->rows++;
	}
	free(line);
	close(fd);
	return (map);
}

t_points	*get_data(char	*line, t_data *fdf, int y)
{
	int		x;
	char	**data;
	char	**sep_data;
	t_points	*points;

	x = 0;
	points = malloc(fdf->map->cols * sizeof(t_points));
	if (!points)
		return (NULL);
	data = ft_split(line, ' ');
	while (data[x])
	{
		sep_data  = ft_split(data[x], ',');
		points[x].x = x;
		points[x].y = y;
		points[x].z = ft_atoi(sep_data[0]);
		points[x].original_z = ft_atoi(sep_data[0]);
		if (sep_data[1])
		{
			points[x].color = ft_atoi_hex(sep_data[1]);
		}
		else
			points[x].color = 0;
		x++;
		free_split(sep_data);
	}
	free_split(data);
	return (points);
}

t_points **fill_points(t_data *fdf)
{
	int			y;
	int			fd;
	char		*line;
	t_points	**points;
	
	y = 0;
	fd = open(fdf->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ERROR:\nFile doesn't exist or couldn't open!\n");
		exit (1);
	}
	points = malloc(fdf->map->rows * sizeof(t_points *));
	if (!points)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, "\n");
		points[y] = get_data(line, fdf, y);
		if (points[y] == NULL)
		{
			while (y-- > 0)
			{
				free(points[y]);
			}
			free(points);
			free(line);
			close(fd);
			return (NULL);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (points);
}

int	file_check(t_data *fdf)
{
	int	size;

	size = ft_strlen(fdf->filename);
	if (ft_strncmp(fdf->filename + (size - 4), ".fdf", 4) != 0)
	{
		ft_printf("ERROR:\nFile specified in wrong format!\n");
		exit (1);
	}
	fdf->map = read_map(fdf);
	if (fdf->map == NULL)
		exit(1);
	fdf->points = fill_points(fdf);
 	printf("\nrows - height: %i\n", fdf->map->rows);
	printf("cols - width: %i\n", fdf->map->cols);
	printf("X: %f\n", fdf->points[3][3].x);
	printf("Y: %f\n", fdf->points[3][3].y);
	printf("Z: %i\n", fdf->points[3][3].z);
	return (0);
}

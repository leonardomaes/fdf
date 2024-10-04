/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:49:40 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/11 12:49:43 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/***********************************************/
/*					Include						*/
/***********************************************/

# include "includes/ft_printf/ft_printf.h"
# include "includes/libft/libft.h"
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/***********************************************/
/*					Structs						*/
/***********************************************/

typedef struct s_draw		 // Bresenham
{
	int	sx;
	int	sy;
	double dx;
	double dy;
	int err;
	int	e2;
}				t_draw;

typedef struct s_offset
{
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
}				t_offset;


typedef struct s_image		// MLX
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	void *mlx;
	void *win;
}				t_image;

typedef struct s_info		// Map info
{
	int	rows;		// HEIGHT - altura
	int	cols;		// WIDTH - largura
	double	width;
	double	height;
	double	zoom;
	double	x_offset;
	double	y_offset;
	double	size;
	int		angle;
	int		color;
	int		size_applyed;
}				t_info;

typedef struct s_points		// Matriz dos valores
{
	double x;
	double y;
	int z;
	int	original_z;
	int color;
}				t_points;

typedef struct s_data
{
	char		*filename;
	t_image 	mlx;
	t_info		*map;
	t_points 	**points;
}				t_data;

/***********************************************/
/*					Defines						*/
/***********************************************/

// WINDOW SETTINGS
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MIDDLE_WIDTH WINDOW_WIDTH / 2
# define MIDDLE_HEIGHT WINDOW_HEIGHT / 2
# define MLX_ERROR 1
// COLORS
# define PI 3.14159265
# define RED_PIXEL 0xFF0000
# define BLUE_PIXEL 0x0000FF
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF
// KEYBOARD
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define ARROW_UP 126
# define ARROW_DOWN 125
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

/***********************************************/
/*				Declarations					*/
/***********************************************/

// MAIN
t_data	*init_win(const char *path);

// CHECKERS
int				count_cols(char *line, int expected_cols);
t_info			*read_map(t_data *fdf);
t_points		*get_data(char	*line, t_data *fdf, int y);
t_points		**fill_points(t_data *fdf);
int				file_check(t_data *fdf);

// COMMANDS
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				check_key(int keysym, t_data *img);

// EXITS
void			free_points(t_data *fdf);
void			free_split(char **data);
void			clear_all(t_data *data);
int				kill_all(t_data *data);

// FORMATS
void			draw_bresenham(t_points a, t_points b, t_data *fdf);
void			draw_lines(t_data *fdf, t_points a, t_points b);
void			print_fdf(t_data *fdf);

// MATH
void    		isometric(double *x, double *y, int z, int angle);
double			ft_abs(float n);
void			rotate_x(t_points *a, int angle);
void			rotate_y(t_points *a, int angle);
void			rotate_z(t_points *a, int angle);

// UTILS
void			var_init(t_data *fdf);
void			apply_size(t_data *fdf, int	flag);
void			apply_rotate(t_data *fdf, int	flag);
void			get_next_color(t_data *fdf, int flag);
void			retore_original_z(t_data *fdf);

#endif
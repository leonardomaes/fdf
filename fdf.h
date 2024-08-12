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
#define FDF_H

/***********************************************/
/*					Include					   */
/***********************************************/

# include "includes/ft_printf/ft_printf.h"
# include "includes/libft/libft.h"

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/***********************************************/
/*					Structs					   */
/***********************************************/

typedef struct	s_data {
	//image
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;			

	//mlx
    void	*mlx;			//Inicia do programa
    void	*win;			//Inicia da tela

	//draw
	double	zoom;			//Quantidade de zoom
	double	rotation;
	double	width_x;				//Tamando da imagem proporcionalmente ao zoom
	double	height_y;				//Tamando da imagem proporcionalmente ao zoom
	double	pos_x;			//Pos Inicial do X baseado no tamanho da tela e do zoom
	double	pos_y;			//Pos Inicial do Y baseado no tamanho da tela e do zoom
	double	last_x;			//
	double	last_y;			//
	double	last_z;			//
	double	cur_x;			//
	double	cur_y;			//
	double	cur_z;			//

	//floats
	double **points;		//Vetor com os valores da *Line[] em Double

	//file
	int			fd;			//File descriptor
	double		rows;		//Qtd de linhas
	double		col;		//Qtd de colunas
	char		*line[];	//Linha obtida pelo GNL
}				t_data;

typedef struct s_draw
{
	double	dx;
	double	dy;
	double	d1;
	double	d2;
	double	x;
	double	y;
	double	sx;
	double	sy;
}				t_draw;


/***********************************************/
/*					Defines					   */
/***********************************************/

// WINDOW SETTINGS
# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 600
# define MIDDLE_WIDTH WINDOW_WIDTH/2
# define MIDDLE_HEIGHT WINDOW_HEIGHT/2
# define MLX_ERROR 1
// COLORS
# define PI 3.14159265
# define RED_PIXEL 0xFF0000
# define BLUE_PIXEL 0x0000FF
# define GREEN_PIXEL 0x00FF00
# define WHITE_PIXEL 0xFFFFFF
// KEYBOARD
# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100
# define ARROW_UP 126
# define ARROW_DOWN 125
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5


/***********************************************/
/*				Declarations				   */
/***********************************************/
// FORMATS
void    draw_line(t_data *img);
void	print_fdf(t_data *data);

// COMMANDS
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		check_key(int keycode, t_data *img);
int		mouse_hook(int keysym, t_data *img);

// CHECKERS
int		file_check(t_data *img);
int	number_check(t_data *img);

//	ERRORS
void file_error(int flag);

// UTILS
void	var_init(t_data *img, char *filename);
int		kill_all(t_data *data);
void	clear_all(t_data *data);
double	**alloc_points(t_data *img);

//	MATH
void    isometric(double *x, double *y, double z);
double	ft_abs(float n);

#endif
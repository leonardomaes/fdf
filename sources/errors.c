/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:01:45 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/17 13:01:46 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void file_error(int flag)
{
    if (flag == 1)
	    ft_printf("ERROR:\nFile doesn't exist or couldn't open!");
    else if(flag == 2)
        ft_printf("ERROR:\nMap in wrong format, check the edges!");
}
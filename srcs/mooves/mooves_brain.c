/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves_brain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 13:57:01 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	ft_handle_keypress(int keysym, t_env *e)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
		e->data->win_ptr = NULL;
		return (0);
	}
	if (ft_check_1(keysym, e) == 0 && ft_check_2(keysym, e) == 0 && \
	ft_check_3(keysym, e) == 0 && ft_check_4(keysym, e) == 0)
		return (0);
	ft_update_coordinates_and_pivot(e);
	return (0);
}

int	ft_handle_mouse(int button, int x, int y, t_env *e)
{
	if (button == 4 && e->mooves->sf < SCALE_FACTOR_MAX)
	{
		x = 0;
		y = 0;
		if (e->mooves->sf < SCALE_FACTOR_MAX)
			e->mooves->sf += 1.0;
		ft_get_pivot(e);
	}
	else if (button == 5 && e->mooves->sf > SCALE_FACTOR_MIN)
	{
		x = 0;
		y = 0;
		if (e->mooves->sf > SCALE_FACTOR_MIN)
			e->mooves->sf -= 1.0;
		ft_get_pivot(e);
	}
	else
		return (0);
	ft_update_coordinates_and_pivot(e);
	return (0);
}

int	ft_destroy_red_cross(t_env *e)
{
	mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
	e->data->win_ptr = NULL;
	mlx_destroy_image(e->data->mlx_ptr, e->data->img.mlx_img);
	mlx_destroy_display(e->data->mlx_ptr);
	free(e->data->mlx_ptr);
	ft_free_tab(e->size->map, e->size->height);
	ft_free_env(e);
	exit(0);
}

void	ft_space_reset(t_env *e)
{
	e->mooves->angle_x = M_PI / 6;
	e->mooves->angle_y = M_PI / 6;
	e->mooves->angle_z = 0;
	e->mooves->sf = e->mooves->keep_scaling;
	e->mooves->z_sf = 0.4;
	e->mooves->step = 10;
	e->mooves->sign = 1;
	e->mooves->rotation_step = 0.1;
	e->mooves->rotation_angle = 0.1;
	e->mooves->z_scale_step = 0.1;
	e->mooves->color_choice = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 12:12:14 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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

int	ft_check_1(int keysym, t_env *e)
{
	if (keysym == XK_D || keysym == XK_d)
	{
		e->mooves->angle_x += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_A || keysym == XK_a)
	{
		e->mooves->angle_x -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_W || keysym == XK_w)
	{
		e->mooves->angle_y += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_S || keysym == XK_s)
	{
		e->mooves->angle_y -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	return (0);
}

int	ft_check_2(int keysym, t_env *e)
{
	if (keysym == XK_Q || keysym == XK_q)
	{
		e->mooves->angle_z -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_E || keysym == XK_e)
	{
		e->mooves->angle_z += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_1)
	{
		e->mooves->z_sf += e->mooves->z_scale_step;
		return (1);
	}
	else if (keysym == XK_2)
	{
		e->mooves->z_sf -= e->mooves->z_scale_step;
		return (1);
	}
	return (0);
}

int	ft_check_3(int keysym, t_env *e)
{
	if (keysym == XK_Z || keysym == XK_z)
	{
		if (e->mooves->color_choice == 4)
			e->mooves->color_choice = 1;
		else
			e->mooves->color_choice += 1;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_X || keysym == XK_x)
	{
		if (e->mooves->color_choice == 1)
			e->mooves->color_choice = 4;
		else
			e->mooves->color_choice -= 1;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_space)
	{
		ft_put_middle_window(e);
		ft_space_reset(e);
		return (ft_get_pivot(e), 1);
	}
	return (0);
}

int	ft_check_4(int keysym, t_env *e)
{
	if (keysym == XK_Left)
	{
		ft_move_points_x(e, -e->mooves->sign);
		ft_get_pivot(e);
		return (0);
	}
	else if (keysym == XK_Right)
	{
		ft_move_points_x(e, e->mooves->sign);
		ft_get_pivot(e);
		return (0);
	}
	else if (keysym == XK_Up)
	{
		ft_move_points_y(e, -e->mooves->sign);
		ft_get_pivot(e);
		return (0);
	}
	else if (keysym == XK_Down)
	{
		ft_move_points_y(e, e->mooves->sign);
		ft_get_pivot(e);
		return (0);
	}
	return (1);
}

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

void	ft_move_points_x(t_env *e, int sign)
{
	int	i;

	i = 0;
	while (i < e->size->width * e->size->height)
	{
		if (sign > 0)
			e->points[i].x += e->mooves->step;
		else
			e->points[i].x -= e->mooves->step;
		++i;
	}
}

void	ft_move_points_y(t_env *e, int sign)
{
	int	i;

	i = 0;
	while (i < e->size->width * e->size->height)
	{
		if (sign > 0)
			e->points[i].y += e->mooves->step;
		else
			e->points[i].y -= e->mooves->step;
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/06 15:11:33 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


int handle_mouse(int button, int x, int y, t_env *e)
{
    if (button == 4 && e->mooves->scale_factor < SCALE_FACTOR_MAX)
    {
		x = 0;
		y = 0;
        if (e->mooves->scale_factor < SCALE_FACTOR_MAX)
            e->mooves->scale_factor += 1.0;
		printf("zoom = %0.00lf\n", e->mooves->scale_factor);
        get_pivot(e);
    }
    else if (button == 5 && e->mooves->scale_factor > SCALE_FACTOR_MIN)
    {
		x = 0;
		y = 0;
        if (e->mooves->scale_factor > SCALE_FACTOR_MIN)
            e->mooves->scale_factor -= 1.0;
		printf("zoom = %0.00lf\n", e->mooves->scale_factor);
        get_pivot(e);
    }
	else
		return (0);
    update_coordinates_and_pivot(e);
    return (0);
}


int	destroy_red_cross(t_env *e)
{
	mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
	e->data->win_ptr = NULL;
	mlx_destroy_image(e->data->mlx_ptr, e->data->img.mlx_img);
    mlx_destroy_display(e->data->mlx_ptr);
	free(e->data->mlx_ptr);
	ft_free_tab(e->size->map, e->size->height);
	free_env(e);
    exit(0);
}


int	handle_keypress(int keysym, t_env *e)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
		e->data->win_ptr = NULL;
		return (0);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
        e->mooves->angle_x += e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y);
		get_pivot(e);
    }
	else if (keysym == XK_A || keysym == XK_a)
	{
		e->mooves->angle_x -= e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y);
		get_pivot(e);
    }
	else if (keysym == XK_W || keysym == XK_w)
	{
        e->mooves->angle_y += e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y);
		get_pivot(e);
    }
	else if (keysym == XK_S || keysym == XK_s)
	{
        e->mooves->angle_y -= e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y);
        get_pivot(e);
    }

	else if (keysym == XK_Q || keysym == XK_q)
	{
        e->mooves->angle_z -= e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\nz = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y, e->mooves->angle_z);
		get_pivot(e);
    }
	else if (keysym == XK_E || keysym == XK_e)
	{
        e->mooves->angle_z += e->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\nz = %0.2lf\n", e->mooves->angle_x, e->mooves->angle_y, e->mooves->angle_z);
		get_pivot(e);
    }

	else if (keysym == XK_1)
    {
        e->mooves->z_scale_factor += e->mooves->z_scale_step;
    }
    else if (keysym == XK_2)
    {
        e->mooves->z_scale_factor -= e->mooves->z_scale_step;
    }

	else if (keysym == XK_Left)
	{
        move_points_x(e, -e->mooves->sign);
		get_pivot(e);
		return(1);
    }
	else if (keysym == XK_Right)
	{
        move_points_x(e, e->mooves->sign);
		get_pivot(e);
		return(1);
    }
	else if (keysym == XK_Up)
	{
        move_points_y(e, -e->mooves->sign);
		get_pivot(e);
		return(1);
    }
	else if (keysym == XK_Down)
	{
        move_points_y(e, e->mooves->sign);
		get_pivot(e);
		return(1);
    }
	else if (keysym == XK_space)
	{
        space_reset(e);
		put_middle_window(e);
		get_pivot(e);
    }
	else if (keysym == XK_Z || keysym == XK_z)
	{
		if (e->mooves->color_choice == 4)
			e->mooves->color_choice = 1;
		else
			e->mooves->color_choice += 1;
		get_pivot(e);
	}
	else if (keysym == XK_X || keysym == XK_x)
	{
		if (e->mooves->color_choice == 1)
			e->mooves->color_choice = 4;
		else
			e->mooves->color_choice -= 1;
		get_pivot(e);
	}
	else
		return (0);
	update_coordinates_and_pivot(e);
	return (0);
}

void space_reset(t_env *e)
{
	e->mooves->angle_x = M_PI / 6;
	e->mooves->angle_y = M_PI / 6;
	e->mooves->angle_z = 0;
    e->mooves->scale_factor = 30.0;
	verify_size(e);
    e->mooves->z_scale_factor = 0.4;
	e->mooves->step = 10;
	e->mooves->sign = 1;
	e->mooves->rotation_step = 0.1;
	e->mooves->rotation_angle = 0.1;
	e->mooves->z_scale_step = 0.1;
	e->mooves->color_choice = 1;
}

void move_points_x(t_env *e, int sign)
{
	int i;
	
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

void move_points_y(t_env *e, int	sign)
{
	int i;

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

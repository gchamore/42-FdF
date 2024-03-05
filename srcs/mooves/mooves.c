/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/05 14:54:18 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


int handle_mouse(int button, int x, int y, t_env *env)
{
    if (button == 4 && env->mooves->scale_factor < SCALE_FACTOR_MAX)
    {
		x = 0;
		y = 0;
        if (env->mooves->scale_factor < SCALE_FACTOR_MAX)
            env->mooves->scale_factor += 1.0;
		printf("zoom = %0.00lf\n", env->mooves->scale_factor);
        get_pivot(env);
    }
    else if (button == 5 && env->mooves->scale_factor > SCALE_FACTOR_MIN)
    {
		x = 0;
		y = 0;
        if (env->mooves->scale_factor > SCALE_FACTOR_MIN)
            env->mooves->scale_factor -= 1.0;
		printf("zoom = %0.00lf\n", env->mooves->scale_factor);
        get_pivot(env);
    }
	else
		return (0);
    update_coordinates_and_pivot(env);
    return (0);
}


int	destroy_red_cross(t_env *env)
{
	mlx_destroy_window(env->data->mlx_ptr, env->data->win_ptr);
	env->data->win_ptr = NULL;
	mlx_destroy_image(env->data->mlx_ptr, env->data->img.mlx_img);
    mlx_destroy_display(env->data->mlx_ptr);
	free(env->data->mlx_ptr);
	ft_free_tab(env->size->map, env->size->height);
	free_render_data(env);
    exit(0);
}


int	handle_keypress(int keysym, t_env *env)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(env->data->mlx_ptr, env->data->win_ptr);
		env->data->win_ptr = NULL;
		return (0);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
        env->mooves->angle_x += env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y);
		get_pivot(env);
    }
	else if (keysym == XK_A || keysym == XK_a)
	{
		env->mooves->angle_x -= env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y);
		get_pivot(env);
    }
	else if (keysym == XK_W || keysym == XK_w)
	{
        env->mooves->angle_y += env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y);
		get_pivot(env);
    }
	else if (keysym == XK_S || keysym == XK_s)
	{
        env->mooves->angle_y -= env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y);
        get_pivot(env);
    }

	else if (keysym == XK_Q || keysym == XK_q)
	{
        env->mooves->angle_z -= env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\nz = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y, env->mooves->angle_z);
		get_pivot(env);
    }
	else if (keysym == XK_E || keysym == XK_e)
	{
        env->mooves->angle_z += env->mooves->rotation_step;
		printf("x = %0.2lf\ny = %0.2lf\nz = %0.2lf\n", env->mooves->angle_x, env->mooves->angle_y, env->mooves->angle_z);
		get_pivot(env);
    }

	else if (keysym == XK_1)
    {
        env->mooves->z_scale_factor += env->mooves->z_scale_step;
    }
    else if (keysym == XK_2)
    {
        env->mooves->z_scale_factor -= env->mooves->z_scale_step;
    }

	else if (keysym == XK_Left)
	{
        move_points_x(env, -env->mooves->sign);
		get_pivot(env);
		return(1);
    }
	else if (keysym == XK_Right)
	{
        move_points_x(env, env->mooves->sign);
		get_pivot(env);
		return(1);
    }
	else if (keysym == XK_Up)
	{
        move_points_y(env, -env->mooves->sign);
		get_pivot(env);
		return(1);
    }
	else if (keysym == XK_Down)
	{
        move_points_y(env, env->mooves->sign);
		get_pivot(env);
		return(1);
    }
	else if (keysym == XK_space)
	{
        space_reset(env);
		put_middle_window(env);
		get_pivot(env);
    }
	else
		return (0);
	update_coordinates_and_pivot(env);
	return (0);
}

void space_reset(t_env *env)
{
	env->mooves->angle_x = M_PI / 6;
	env->mooves->angle_y = M_PI / 6;
	env->mooves->angle_z = 0;
    env->mooves->scale_factor = 30.0;
	verify_size(env);
    env->mooves->z_scale_factor = 0.4;
	env->mooves->step = 10;
	env->mooves->sign = 1;
	env->mooves->rotation_step = 0.1;
	env->mooves->rotation_angle = 0.1;
	env->mooves->z_scale_step = 0.1;
}

void move_points_x(t_env *env, int sign)
{
	int i;
	
	i = 0;
    while (i < env->size->width * env->size->height)
	{
		if (sign > 0)
			env->points[i].x += env->mooves->step;
		else
			env->points[i].x -= env->mooves->step;
		++i;
    }
}

void move_points_y(t_env *env, int	sign)
{
	int i;

	i = 0;
    while (i < env->size->width * env->size->height)
	{
		if (sign > 0)
			env->points[i].y += env->mooves->step;
		else
			env->points[i].y -= env->mooves->step;
		++i;
    }
}

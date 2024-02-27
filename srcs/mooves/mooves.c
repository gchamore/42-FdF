/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/27 16:47:47 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


int	handle_mouse(int button, int x, int y, t_env *env)
{
	if (button == 5)
	{
		x = 0;
		y = 0;
		env->mooves->scale_factor += 1.0;
		get_pivot(env);
	}
	if (button == 4)
	{
		x = 0;
		y = 0;
		env->mooves->scale_factor -= 1.0;
		get_pivot(env);
	}
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
	// Pour quitter le programme

	if (keysym == XK_Escape)
	{
		mlx_destroy_window(env->data->mlx_ptr, env->data->win_ptr);
		env->data->win_ptr = NULL;
		return (0);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
        env->mooves->angle_x += env->mooves->rotation_step;
		get_pivot(env);
    }
	else if (keysym == XK_A || keysym == XK_a)
	{
		env->mooves->angle_x -= env->mooves->rotation_step;
		get_pivot(env);
    }
	else if (keysym == XK_W || keysym == XK_w)
	{
        env->mooves->angle_y += env->mooves->rotation_step;
		get_pivot(env);
    }
	else if (keysym == XK_S || keysym == XK_s)
	{
        env->mooves->angle_y -= env->mooves->rotation_step;
        get_pivot(env);
    }

	else if (keysym == XK_Q || keysym == XK_q)
	{
        get_pivot(env);
        rotate_isometric_projection(env, -env->mooves->rotation_angle);
		put_middle_map(env);
		get_pivot(env);
		return(1);
    }
	else if (keysym == XK_E || keysym == XK_e)
	{
        get_pivot(env);
        rotate_isometric_projection(env, env->mooves->rotation_angle);
		put_middle_map(env);
		get_pivot(env);
		return(1);
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

	update_coordinates_and_pivot(env);
	return (0);
}

void space_reset(t_env *env)
{
	env->mooves->scale_factor = 15.0;
    env->mooves->z_scale_factor = 0.8;
	env->mooves->step = 10;
	env->mooves->sign = 1;
	env->mooves->rotation_step = 0.1;
	env->mooves->rotation_angle = 0.1;
	env->mooves->z_scale_step = 0.1;
	env->mooves->angle_x = (sqrt(3) / 2);
	env->mooves->angle_y = (sqrt(3) / 2);
}

void rotate_isometric_projection(t_env *env, double rotation_angle)
{
	t_tools v;
	double new_x;
	double new_y;
	
    v.new_mid_x = env->size->width / 2;
    v.new_mid_y = env->size->height / 2;
	v.i = 0;
	while (v.i < env->size->width * env->size->height)
	{
        // Translate to origin
        v.temp_x = env->points[v.i].x - v.new_mid_x;
        v.temp_y = env->points[v.i].y - v.new_mid_y;

        // Perform rotation
        new_x = v.temp_x * cos(rotation_angle) - v.temp_y * sin(rotation_angle);
        new_y = v.temp_x * sin(rotation_angle) + v.temp_y * cos(rotation_angle);

        // Translate back to original position
        env->points[v.i].x = new_x + v.new_mid_x;
        env->points[v.i].y = new_y + v.new_mid_y;
		++v.i;
    }
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

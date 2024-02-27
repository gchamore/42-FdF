/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/27 15:26:58 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void update_coordinates_and_pivot(t_env *env)
{
    get_coordinates_from_map(env);
    put_middle_map(env);
	get_pivot(env);
}

void	init_min_max(t_env *env)
{
	env->size->max_x = env->points[0].x;
    env->size->max_y = env->points[0].y;
	env->size->min_x = env->points[0].x;
    env->size->min_y = env->points[0].y;
}

void	get_min_max(t_env *env)
{
	t_tools	v;

	init_min_max(env);
	v.i = 0;
	v.n = 0;
    while (v.i < env->size->height)
	{
		v.j = 0;
        while (v.j < env->size->width)
		{
            if (env->points[v.n].x > env->size->max_x)
                env->size->max_x = env->points[v.n].x;
			if (env->points[v.n].x < env->size->min_x)
                env->size->min_x = env->points[v.n].x;
            if (env->points[v.n].y > env->size->max_y)
                env->size->max_y = env->points[v.n].y;
			if (env->points[v.n].y < env->size->min_y)
                env->size->min_y = env->points[v.n].y;
			v.j++;
			v.n++;
        }
		v.i++;
    }
}

void get_pivot(t_env *env)
{
    get_min_max(env);
   	env->size->mid_x = (env->size->max_x + env->size->min_x) / 2;
    env->size->mid_y = (env->size->max_y + env->size->min_y) / 2;
}

void put_middle_map(t_env *env)
{
	t_tools	v;

    get_min_max(env);
   	v.new_mid_x = (env->size->max_x + env->size->min_x) / 2;
    v.new_mid_y = (env->size->max_y + env->size->min_y) / 2;
    v.delta_x = env->size->mid_x - v.new_mid_x;
    v.delta_y = env->size->mid_y - v.new_mid_y;
	// printf("\nNew pivot map\n -> x = %0.0lf\n -> y = %0.0lf\n", v.delta_x, v.delta_y);
	v.i = 0;
	v.n = 0;
    while (v.i < env->size->height)
	{
		v.j = 0;
        while (v.j < env->size->width)
		{
            env->points[v.n].x += v.delta_x;
            env->points[v.n].y += v.delta_y;
			v.j++;
			v.n++;
        }
		v.i++;
    }
}

void put_middle_window(t_env *env)
{
	t_tools	v;

    get_min_max(env);
   	env->size->mid_x = (env->size->max_x + env->size->min_x) / 2;
    env->size->mid_y = (env->size->max_y + env->size->min_y) / 2;
    v.delta_x = WINDOW_WIDTH / 2 - env->size->mid_x;
    v.delta_y = WINDOW_HEIGHT / 2 - env->size->mid_y;
	// printf("\nNew pivot win\n -> x = %0.0lf\n -> y = %0.0lf\n", v.delta_x, v.delta_y);

	v.i = 0;
	v.n = 0;
    while (v.i < env->size->height)
	{
		v.j = 0;
        while (v.j < env->size->width)
		{
            env->points[v.n].x += v.delta_x;
            env->points[v.n].y += v.delta_y;
			v.j++;
			v.n++;
        }
		v.i++;
    }
}

void get_coordinates_from_map(t_env *env)
{
    t_tools v;

    v.mid_win_x = WINDOW_WIDTH / 2;
    v.mid_win_y = WINDOW_HEIGHT / 2;
    v.i = 0;
    v.y = 0;
    while (v.y < env->size->height)
	{
        v.x = 0;
        while (v.x < env->size->width)
		{
            env->points[v.i].x = (sqrt(3) / 2) + cos(env->mooves->angle_x) * (v.x - v.y) * env->mooves->scale_factor + v.mid_win_x;
            env->points[v.i].y = (sqrt(3) / 2) + sin(env->mooves->angle_y) * (v.x + v.y) * env->mooves->scale_factor - env->size->map[v.y][v.x] * env->mooves->z_scale_factor * env->mooves->scale_factor + v.mid_win_y;
            v.i++;
            v.x++;
        }
        v.y++;
    }
}

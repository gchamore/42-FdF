/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/05 15:21:53 by gchamore         ###   ########.fr       */
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
			if (env->size->map[v.i][v.j] < env->size->max_z)
                env->size->max_z = env->size->map[v.i][v.j];
			if (env->size->map[v.i][v.j] < env->size->min_z)
                env->size->min_z = env->size->map[v.i][v.j];
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
void	verify_size(t_env *env)
{
	while ((env->size->max_y > WINDOW_HEIGHT || env->size->max_x > WINDOW_WIDTH) && env->mooves->scale_factor > 1)
	{
		env->mooves->scale_factor -= 1.0;
		printf("\n%0.02lf\n", env->mooves->scale_factor);
		get_coordinates_from_map(env);
		get_min_max(env);
	}
	get_pivot(env);
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
	verify_size(env);
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
// void	check_color(t_env *env)
// {
// 	int	first_div;
// 	int	second_div;
	
// 	first_div = env->points_3D->z / 3;
// 	first_div = env->points_3D->z - (env->points_3D->z / 3);
// 	if (env->points_3D->z < first_div)
// 		env->points_3D->color = GREEN_PIXEL;
// 	else if(env->points_3D->z >= first_div && env->points_3D->z < second_div)
// 		env->points_3D->color = MAROON_PIXEL;
// 	else if(env->points_3D->z >=  second_div)
// 		env->points_3D->color = WHITE_PIXEL;
// }
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
            env->points_3D[v.i].x = (sqrt(3) / 2) * (v.x - v.y) * env->mooves->scale_factor;
            env->points_3D[v.i].y = (sqrt(3) / 2) * (v.x + v.y) * env->mooves->scale_factor;
            env->points_3D[v.i].z = env->size->map[v.y][v.x] * env->mooves->z_scale_factor * env->mooves->scale_factor;
            rotate_point_x(&env->points_3D[v.i], env->mooves->angle_x);
            rotate_point_y(&env->points_3D[v.i], env->mooves->angle_y);
            rotate_point_z(&env->points_3D[v.i], env->mooves->angle_z);
            env->points[v.i].x = env->points_3D[v.i].x + v.mid_win_x;
            env->points[v.i].y = env->points_3D[v.i].y + v.mid_win_y;
            v.i++;
            v.x++;
        }
        v.y++;
    }
}

void rotate_point_x(t_point3D *points_3D, double angle)
{
    double new_y;
    double new_z;

	new_y = points_3D->y * cos(angle) - points_3D->z * sin(angle);
	new_z = points_3D->y * sin(angle) + points_3D->z * cos(angle);
    points_3D->y = new_y;
    points_3D->z = new_z;
}

void rotate_point_y(t_point3D *points_3D, double angle)
{
    double new_x;
    double new_z;

	new_x = points_3D->x * cos(angle) + points_3D->z * sin(angle);
	new_z = -points_3D->x * sin(angle) + points_3D->z * cos(angle);
    points_3D->x = new_x;
    points_3D->z = new_z;
}

void rotate_point_z(t_point3D *points_3D, double angle)
{
    double new_x;
    double new_y;

	new_x = points_3D->x * cos(angle) - points_3D->y * sin(angle);
	new_y = points_3D->x * sin(angle) + points_3D->y * cos(angle);
    points_3D->x = new_x;
    points_3D->y = new_y;
}

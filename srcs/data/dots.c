/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 12:10:43 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_update_coordinates_and_pivot(t_env *e)
{
	ft_get_coordinates_from_map(e);
	ft_put_middle_map(e);
	ft_get_pivot(e);
}

void	ft_init_min_max(t_env *e)
{
	e->size->max_x = e->points[0].x;
	e->size->max_y = e->points[0].y;
	e->size->min_x = e->points[0].x;
	e->size->min_y = e->points[0].y;
	e->size->max_z = e->size->map[0][0];
	e->size->min_z = e->size->map[0][0];
}

void	ft_get_min_max(t_env *e)
{
	t_tools	v;

	ft_init_min_max(e);
	v.i = 0;
	v.n = 0;
	while (++v.i < e->size->height)
	{
		v.j = 0;
		while (++v.j < e->size->width)
		{
			if (e->points[v.n].x > e->size->max_x)
				e->size->max_x = e->points[v.n].x;
			if (e->points[v.n].x < e->size->min_x)
				e->size->min_x = e->points[v.n].x;
			if (e->size->map[v.i][v.j] > e->size->max_z)
				e->size->max_z = e->size->map[v.i][v.j];
			if (e->size->map[v.i][v.j] < e->size->min_z)
				e->size->min_z = e->size->map[v.i][v.j];
			if (e->points[v.n].y > e->size->max_y)
				e->size->max_y = e->points[v.n].y;
			if (e->points[v.n].y < e->size->min_y)
				e->size->min_y = e->points[v.n].y;
			v.n++;
		}
	}
}

void	ft_get_pivot(t_env *e)
{
	ft_get_min_max(e);
	e->size->mid_x = (e->size->max_x + e->size->min_x) / 2;
	e->size->mid_y = (e->size->max_y + e->size->min_y) / 2;
}

void	ft_verify_size(t_env *e)
{
	while ((e->size->max_y > WINDOW_HEIGHT || e->size->max_x > WINDOW_WIDTH) \
	&& e->mooves->sf > 1)
	{
		e->mooves->sf -= 1.0;
		ft_get_coordinates_from_map(e);
		ft_get_min_max(e);
	}
	if (e->mooves->keep_scaling == 0)
		e->mooves->keep_scaling = e->mooves->sf;
	ft_get_pivot(e);
}

void	ft_put_middle_map(t_env *e)
{
	t_tools	v;

	ft_get_min_max(e);
	v.new_mid_x = (e->size->max_x + e->size->min_x) / 2;
	v.new_mid_y = (e->size->max_y + e->size->min_y) / 2;
	v.delta_x = e->size->mid_x - v.new_mid_x;
	v.delta_y = e->size->mid_y - v.new_mid_y;
	v.i = 0;
	v.n = 0;
	while (v.i < e->size->height)
	{
		v.j = 0;
		while (v.j < e->size->width)
		{
			e->points[v.n].x += v.delta_x;
			e->points[v.n].y += v.delta_y;
			v.j++;
			v.n++;
		}
		v.i++;
	}
}

void	ft_put_middle_window(t_env *e)
{
	t_tools	v;

	ft_get_min_max(e);
	ft_verify_size(e);
	e->size->mid_x = (e->size->max_x + e->size->min_x) / 2;
	e->size->mid_y = (e->size->max_y + e->size->min_y) / 2;
	v.delta_x = WINDOW_WIDTH / 2 - e->size->mid_x;
	v.delta_y = WINDOW_HEIGHT / 2 - e->size->mid_y;
	v.i = 0;
	v.n = 0;
	while (v.i < e->size->height)
	{
		v.j = 0;
		while (v.j < e->size->width)
		{
			e->points[v.n].x += v.delta_x;
			e->points[v.n].y += v.delta_y;
			v.j++;
			v.n++;
		}
		v.i++;
	}
}

void	ft_get_coordinates_from_map(t_env *e)
{
	t_tools	v;

	v.mid_win_x = WINDOW_WIDTH / 2;
	v.mid_win_y = WINDOW_HEIGHT / 2;
	v.i = 0;
	v.y = 0;
	while (v.y < e->size->height)
	{
		v.x = 0;
		while (v.x < e->size->width)
		{
			e->points_3D[v.i].x = (sqrt(3) / 2) * (v.x - v.y) * e->mooves->sf;
			e->points_3D[v.i].y = (sqrt(3) / 2) * (v.x + v.y) * e->mooves->sf;
			e->points_3D[v.i].z = \
			e->size->map[v.y][v.x] * e->mooves->z_sf * e->mooves->sf;
			ft_rotate_point_x(&e->points_3D[v.i], e->mooves->angle_x);
			ft_rotate_point_y(&e->points_3D[v.i], e->mooves->angle_y);
			ft_rotate_point_z(&e->points_3D[v.i], e->mooves->angle_z);
			e->points[v.i].x = e->points_3D[v.i].x + v.mid_win_x;
			e->points[v.i].y = e->points_3D[v.i].y + v.mid_win_y;
			v.i++;
			v.x++;
		}
		v.y++;
	}
}

void	ft_rotate_point_x(t_point3D *points_3D, double angle)
{
	double	new_y;
	double	new_z;

	new_y = points_3D->y * cos(angle) - points_3D->z * sin(angle);
	new_z = points_3D->y * sin(angle) + points_3D->z * cos(angle);
	points_3D->y = new_y;
	points_3D->z = new_z;
}

void	ft_rotate_point_y(t_point3D *points_3D, double angle)
{
	double	new_x;
	double	new_z;

	new_x = points_3D->x * cos(angle) + points_3D->z * sin(angle);
	new_z = -points_3D->x * sin(angle) + points_3D->z * cos(angle);
	points_3D->x = new_x;
	points_3D->z = new_z;
}

void	ft_rotate_point_z(t_point3D *points_3D, double angle)
{
	double	new_x;
	double	new_y;

	new_x = points_3D->x * cos(angle) - points_3D->y * sin(angle);
	new_y = points_3D->x * sin(angle) + points_3D->y * cos(angle);
	points_3D->x = new_x;
	points_3D->y = new_y;
}

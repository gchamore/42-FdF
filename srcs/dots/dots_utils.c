/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:54:25 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/08 17:21:47 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_get_min_max(t_env *e)
{
	t_tools	v;

	ft_init_min_max(e);
	v.i = -1;
	v.n = 0;
	while (++v.i < e->size->height)
	{
		v.j = -1;
		while (++v.j < e->size->width)
		{
			if (e->points_2d[v.n].x > e->size->max_x)
				e->size->max_x = e->points_2d[v.n].x;
			if (e->points_2d[v.n].x < e->size->min_x)
				e->size->min_x = e->points_2d[v.n].x;
			if (e->size->map[v.i][v.j] > e->size->max_z)
				e->size->max_z = e->size->map[v.i][v.j];
			if (e->size->map[v.i][v.j] < e->size->min_z)
				e->size->min_z = e->size->map[v.i][v.j];
			if (e->points_2d[v.n].y > e->size->max_y)
				e->size->max_y = e->points_2d[v.n].y;
			if (e->points_2d[v.n].y < e->size->min_y)
				e->size->min_y = e->points_2d[v.n].y;
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

void	ft_init_min_max(t_env *e)
{
	e->size->max_x = e->points_2d[0].x;
	e->size->max_y = e->points_2d[0].y;
	e->size->min_x = e->points_2d[0].x;
	e->size->min_y = e->points_2d[0].y;
	e->size->max_z = e->size->map[0][0];
	e->size->min_z = e->size->map[0][0];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 11:06:45 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf_bonus.h"

void	ft_put_middle_map(t_env *e)
{
	t_tools	v;

	ft_get_min_max(e);
	v.new_mid_x = (e->size->max_x + e->size->min_x) / 2;
	v.new_mid_y = (e->size->max_y + e->size->min_y) / 2;
	v.delta_x = e->size->mid_x - v.new_mid_x;
	v.delta_y = e->size->mid_y - v.new_mid_y;
	v.i = 0;
	v.y = 0;
	while (v.y < e->size->height)
	{
		v.x = 0;
		while (v.x < e->size->width)
		{
			e->points_2d[v.i].x += v.delta_x;
			e->points_2d[v.i].y += v.delta_y;
			v.x++;
			v.i++;
		}
		v.y++;
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
			e->points_2d[v.n].x += v.delta_x;
			e->points_2d[v.n].y += v.delta_y;
			v.j++;
			v.n++;
		}
		v.i++;
	}
}

void	ft_update_coordinates_and_pivot(t_env *e)
{
	ft_get_coordinates_from_map(e);
	ft_put_middle_map(e);
	ft_get_pivot(e);
}

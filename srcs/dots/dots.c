/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 14:41:06 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_brain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:15:42 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/08 15:54:59 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
			e->points_3d[v.i].x = (sqrt(3) / 2) * (v.x - v.y) * e->mooves->sf;
			e->points_3d[v.i].y = (sqrt(3) / 2) * (v.x + v.y) * e->mooves->sf;
			e->points_3d[v.i].z = \
			e->size->map[v.y][v.x] * e->mooves->z_sf * e->mooves->sf;
			ft_rotate_point_x(&e->points_3d[v.i], e->mooves->angle_x);
			ft_rotate_point_y(&e->points_3d[v.i], e->mooves->angle_y);
			ft_rotate_point_z(&e->points_3d[v.i], e->mooves->angle_z);
			e->points_2d[v.i].x = e->points_3d[v.i].x + v.mid_win_x;
			e->points_2d[v.i].y = e->points_3d[v.i].y + v.mid_win_y;
			v.i++;
			v.x++;
		}
		v.y++;
	}
}

void	ft_rotate_point_x(t_point3d *points_3d, double angle)
{
	double	new_y;
	double	new_z;

	new_y = points_3d->y * cos(angle) - points_3d->z * sin(angle);
	new_z = points_3d->y * sin(angle) + points_3d->z * cos(angle);
	points_3d->y = new_y;
	points_3d->z = new_z;
}

void	ft_rotate_point_y(t_point3d *points_3d, double angle)
{
	double	new_x;
	double	new_z;

	new_x = points_3d->x * cos(angle) + points_3d->z * sin(angle);
	new_z = -points_3d->x * sin(angle) + points_3d->z * cos(angle);
	points_3d->x = new_x;
	points_3d->z = new_z;
}

void	ft_rotate_point_z(t_point3d *points_3d, double angle)
{
	double	new_x;
	double	new_y;

	new_x = points_3d->x * cos(angle) - points_3d->y * sin(angle);
	new_y = points_3d->x * sin(angle) + points_3d->y * cos(angle);
	points_3d->x = new_x;
	points_3d->y = new_y;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:39:34 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 13:47:06 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_make_horizontal(t_env *e, t_tools v)
{
	int	index1;
	int	index2;

	while (v.x < e->size->height)
	{
		v.y = 0;
		while (v.y < e->size->width - 1)
		{
			index1 = v.x * e->size->width + v.y;
			index2 = v.x * e->size->width + (v.y + 1);
			ft_check_z(e, v.x, v.y);
			ft_check_z(e, v.x, v.y + 1);
			ft_init_render_line(&v, e, index1, index2);
			ft_render_line(&(e->data->img), &v, e);
			v.y++;
		}
		v.x++;
	}
}

void	ft_make_vertical(t_env *e, t_tools v)
{
	int	index1;
	int	index2;

	while (v.y < e->size->width)
	{
		v.x = 0;
		while (v.x < e->size->height - 1)
		{
			index1 = v.x * e->size->width + v.y;
			index2 = (v.x + 1) * e->size->width + v.y;
			ft_check_z(e, v.x, v.y);
			ft_check_z(e, v.x + 1, v.y);
			ft_init_render_line(&v, e, index1, index2);
			ft_render_line(&(e->data->img), &v, e);
			v.x++;
		}
		v.y++;
	}
}

void	ft_check_z(t_env *e, int x, int y)
{
	int	z;

	z = 0;
	z = ft_get_percent(e->size->max_z, e->size->min_z, e->size->map[x][y]);
	ft_choose_color1(e);
	if (z >= 0 && z < 20)
		e->mooves->color = e->mooves->color1;
	else if (z >= 20 && z <= 50)
		e->mooves->color = e->mooves->color2;
	else if (z > 50 && z <= 80)
		e->mooves->color = e->mooves->color3;
	else if (z > 80 && z <= 100)
		e->mooves->color = e->mooves->color4;
}

int	ft_my_abs(int c)
{
	if (c < 0)
		return (-c);
	else
		return (c);
}

int	ft_get_percent(int max, int min, int z)
{
	int	max_temp;
	int	max_perc;
	int	temp;

	max_temp = max - min;
	max_perc = 100;
	temp = (z * max_perc / max_temp);
	return (temp);
}

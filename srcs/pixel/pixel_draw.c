/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:39:31 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/08 17:34:26 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_init_render_line(t_tools *v, t_env *e, int index1, int index2)
{
	v->start_x = e->points_2d[index1].x;
	v->start_y = e->points_2d[index1].y;
	v->end_x = e->points_2d[index2].x;
	v->end_y = e->points_2d[index2].y;
	v->diff_x = abs(v->end_x - v->start_x);
	v->diff_y = abs(v->end_y - v->start_y);
	if (v->start_x < v->end_x)
		v->step_x = 1;
	else
		v->step_x = -1;
	if (v->start_y < v->end_y)
		v->step_y = 1;
	else
		v->step_y = -1;
	v->error = v->diff_x - v->diff_y;
}

void	ft_render_line(t_img *img, t_tools *v, t_env *e)
{
	while (v->start_x != v->end_x || v->start_y != v->end_y)
	{
		ft_img_pix_put(img, v->start_x, v->start_y, e->mooves->color);
		v->error2 = 2 * v->error;
		if (v->error2 > -v->diff_y)
		{
			v->error -= v->diff_y;
			v->start_x += v->step_x;
		}
		if (v->error2 < v->diff_x)
		{
			v->error += v->diff_x;
			v->start_y += v->step_y;
		}
	}
}

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH || x < 0 || y < 0)
		return ;
	else
		ft_my_img_pix_put(img, x, y, color);
}

void	ft_my_img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

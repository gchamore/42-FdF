/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:52 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 12:09:01 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			ft_img_pix_put(img, j++, i, color);
		++i;
	}
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

void	ft_choose_color1(t_env *e)
{
	if (e->mooves->color_choice == 1)
	{
		e->mooves->color1 = DARK_GREEN_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_GREEN_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_GREEN_PIXEL;
		e->mooves->color4 = LIGHT_GREEN_PIXEL;
	}
	else if (e->mooves->color_choice == 2)
	{
		e->mooves->color1 = DARK_YELLOW_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_YELLOW_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_YELLOW_PIXEL;
		e->mooves->color4 = LIGHT_YELLOW_PIXEL;
	}
	ft_choose_color2(e);
}

void	ft_choose_color2(t_env *e)
{
	if (e->mooves->color_choice == 3)
	{
		e->mooves->color1 = DARK_BLUE_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_BLUE_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_BLUE_PIXEL;
		e->mooves->color4 = LIGHT_BLUE_PIXEL;
	}
	else if (e->mooves->color_choice == 4)
	{
		e->mooves->color1 = DARK_ORANGE_RED_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_ORANGE_RED_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_ORANGE_RED_PIXEL;
		e->mooves->color4 = LIGHT_ORANGE_RED_PIXEL;
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

void	ft_init_render_line(t_tools *v, t_env *e, int index1, int index2)
{
	v->start_x = e->points[index1].x;
	v->start_y = e->points[index1].y;
	v->end_x = e->points[index2].x;
	v->end_y = e->points[index2].y;
	v->diff_x = ft_my_abs(v->end_x - v->start_x);
	v->diff_y = ft_my_abs(v->end_y - v->start_y);
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

void	ft_render_dot(t_env *e)
{
	t_tools	v;

	v.x = 0;
	v.y = 0;
	ft_make_horizontal(e, v);
	v.y = 0;
	ft_make_vertical(e, v);
}

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

int	ft_render(t_env *e)
{
	if (e->data->win_ptr == NULL)
		return (1);
	ft_render_background(&(e->data->img), BLACK_PIXEL);
	ft_render_dot(e);
	mlx_put_image_to_window(e->data->mlx_ptr, e->data->win_ptr, \
	e->data->img.mlx_img, 0, 0);
	return (0);
}

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	if (y > WINDOW_HEIGHT || x > WINDOW_WIDTH || x < 0 || y < 0)
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

int	ft_pixel_brain(char *argv, t_env *e)
{
	e->data->mlx_ptr = mlx_init();
	if (e->data->mlx_ptr == NULL)
		return (MLX_ERROR);
	e->data->win_ptr = \
	mlx_new_window(e->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, argv);
	if (e->data->win_ptr == NULL)
		return (MLX_ERROR);
	e->data->img.mlx_img = \
	mlx_new_image(e->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	e->data->img.addr = mlx_get_data_addr(e->data->img.mlx_img, \
	&e->data->img.bpp, &e->data->img.line_len, &e->data->img.endian);
	ft_get_coordinates_from_map(e);
	ft_put_middle_window(e);
	ft_get_pivot(e);
	mlx_loop_hook(e->data->mlx_ptr, ft_render, e);
	mlx_key_hook(e->data->win_ptr, ft_handle_keypress, e);
	mlx_mouse_hook(e->data->win_ptr, ft_handle_mouse, e);
	mlx_hook(e->data->win_ptr, DestroyNotify, StructureNotifyMask, \
	ft_destroy_red_cross, e);
	mlx_loop(e->data->mlx_ptr);
	mlx_destroy_image(e->data->mlx_ptr, e->data->img.mlx_img);
	mlx_destroy_display(e->data->mlx_ptr);
	free(e->data->mlx_ptr);
	return (0);
}

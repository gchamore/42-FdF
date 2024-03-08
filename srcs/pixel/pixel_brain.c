/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_brain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:39:17 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/08 18:10:00 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
	mlx_hook(e->data->win_ptr, KeyPress, KeyPressMask, ft_handle_keypress, e);
	mlx_mouse_hook(e->data->win_ptr, ft_handle_mouse, e);
	mlx_hook(e->data->win_ptr, KeyRelease, KeyReleaseMask, \
	ft_handle_keyrelease, e);
	mlx_hook(e->data->win_ptr, DestroyNotify, StructureNotifyMask, \
	ft_destroy_red_cross, e);
	mlx_loop(e->data->mlx_ptr);
	mlx_destroy_image(e->data->mlx_ptr, e->data->img.mlx_img);
	mlx_destroy_display(e->data->mlx_ptr);
	return (free(e->data->mlx_ptr), 0);
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

void	ft_render_background(t_img *img, int color)
{
	t_tools	v;

	v.i = 0;
	while (v.i < WINDOW_HEIGHT)
	{
		v.j = 0;
		while (v.j < WINDOW_WIDTH)
			ft_img_pix_put(img, v.j++, v.i, color);
		++v.i;
	}
}

void	ft_render_dot(t_env *e)
{
	ft_make_horizontal(e);
	ft_make_vertical(e);
}

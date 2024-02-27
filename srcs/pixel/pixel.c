/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:52 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/27 16:27:44 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	render_background(t_img *img, int color)
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

int my_abs(int c)
{
    if (c < 0)
		return (-c);
    else
        return (c);
}

void ft_render_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int diff_x;
    int diff_y;
    int step_x;
	int step_y;
	int error;
	int error2;
	
	diff_x = my_abs(x1 - x0);
	diff_y = my_abs(y1 - y0);
    if (x0 < x1)
        step_x = 1;
    else
        step_x = -1;
    if (y0 < y1)
        step_y = 1;
    else
        step_y = -1;
    error = diff_x - diff_y;
    while (x0 != x1 || y0 != y1)
    {
        ft_img_pix_put(img, x0, y0, color);
        error2 = 2 * error;
        if (error2 > -diff_y)
        {
            error -= diff_y;
            x0 += step_x;
        }
        if (error2 < diff_x)
        {
            error += diff_x;
            y0 += step_y;
        }
    }
}

void ft_render_dot(t_env *env)
{
    int i;
	int j;

	i = 0;
	j = 0;
    while (i < env->size->height)
    {
        j = 0;
        while (j < env->size->width - 1)
        {
            int index1 = i * env->size->width + j;
            int index2 = i * env->size->width + (j + 1);
            ft_render_line(&(env->data->img), env->points[index1].x, env->points[index1].y, env->points[index2].x, env->points[index2].y, WHITE_PIXEL);
            j++;
        }
        i++;
    }
    j = 0;
    while (j < env->size->width)
    {
        i = 0;
        while (i < env->size->height - 1)
        {
            int index1 = i * env->size->width + j;
            int index2 = (i + 1) * env->size->width + j;
            ft_render_line(&(env->data->img), env->points[index1].x, env->points[index1].y, env->points[index2].x, env->points[index2].y, WHITE_PIXEL);
            i++;
        }
        j++;
    }
}

int ft_render(t_env *env)
{
    if (env->data->win_ptr == NULL)
        return (1);
    render_background(&(env->data->img), env->color);
    ft_render_dot(env);
    mlx_put_image_to_window(env->data->mlx_ptr, env->data->win_ptr, env->data->img.mlx_img, 0, 0);
    return (0);
}

void	ft_img_pix_put(t_img *img, int x, int y, int color)
{
	// ft_printf("x = %d && y = %d\n", x, y);
	if(y > WINDOW_HEIGHT || x > WINDOW_WIDTH || x < 0 || y < 0)
		return ;
	else
		img_pix_put(img, x, y, color);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
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

int pixel_brain(char *argv, t_env *env)
{
    env->data->mlx_ptr = mlx_init();
    if (env->data->mlx_ptr == NULL)
        return (MLX_ERROR);
    env->data->win_ptr = mlx_new_window(env->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, argv);
    if (env->data->win_ptr == NULL)
        return (MLX_ERROR);
    env->data->img.mlx_img = mlx_new_image(env->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    env->data->img.addr = mlx_get_data_addr(env->data->img.mlx_img, &env->data->img.bpp, &env->data->img.line_len, &env->data->img.endian);
	get_coordinates_from_map(env);
	put_middle_window(env);
	get_pivot(env);
	mlx_loop_hook(env->data->mlx_ptr, ft_render, env);
	mlx_key_hook(env->data->win_ptr, handle_keypress, env);
	mlx_mouse_hook(env->data->win_ptr, handle_mouse, env);
	mlx_hook(env->data->win_ptr, DestroyNotify, StructureNotifyMask, destroy_red_cross, env);
    mlx_loop(env->data->mlx_ptr);
    mlx_destroy_image(env->data->mlx_ptr, env->data->img.mlx_img);
    mlx_destroy_display(env->data->mlx_ptr);
	free(env->data->mlx_ptr);
    return (0);
}

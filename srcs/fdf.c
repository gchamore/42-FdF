/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/22 15:12:01 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	init_structs(t_size *size)
{
	size->height = 0;
	size->width = 0;
}

void rotate_points(t_point2D *points, int num_points, double angle)
{
	int i;
    double cos_angle;
    double sin_angle;
	double new_x;
	double new_y;
	
	i = 0;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
    while (i < num_points)
	{
        new_x = points[i].x * cos_angle - points[i].y * sin_angle;
        new_y = points[i].x * sin_angle + points[i].y * cos_angle;
        points[i].x = new_x;
        points[i].y = new_y;
		i++;
    }
}

// int handle_rotation(int keysym, t_data *data)
// {
// 	// t_render_data *render_data;
	
// 	// render_data = (t_render_data *)param;
//     // const double rotation_step = 0.1;
//     if (keysym == XK_Left)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
//         // render_data->rotation_data->angle -= rotation_step;
//         // rotate_points(render_data->points, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
//         // return (1);
//     }
// 	else if (keysym == XK_Right)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
//         // render_data->rotation_data->angle += rotation_step;
//         // rotate_points(render_data->points, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
//         // return (1);
//     }
//     return (0);
// }

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            img_pix_put(img, j++, i, color);
        ++i;
    }
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
        img_pix_put(img, x0, y0, color);
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

void ft_render_dot(t_data *data, t_point2D *points, t_size *size)
{
    int i;
	int j;

	i = 0;
	j = 0;
    while (i < size->height)
    {
        j = 0;
        while (j < size->width - 1)
        {
            int index1 = i * size->width + j;
            int index2 = i * size->width + (j + 1);
            ft_render_line(&(data->img), points[index1].x, points[index1].y, points[index2].x, points[index2].y, WHITE_PIXEL);
            j++;
        }
        i++;
    }
    j = 0;
    while (j < size->width)
    {
        i = 0;
        while (i < size->height - 1)
        {
            int index1 = i * size->width + j;
            int index2 = (i + 1) * size->width + j;
            ft_render_line(&(data->img), points[index1].x, points[index1].y, points[index2].x, points[index2].y, WHITE_PIXEL);
            i++;
        }
        j++;
    }
}


int ft_render(void *param)
{
    t_render_data *render_data;
    t_data *data;
	
	render_data = (t_render_data *)param;
	data = render_data->data;

    if (data->win_ptr == NULL)
        return (1);
    render_background(&(data->img), render_data->color);
    ft_render_dot(data, render_data->points, render_data->size);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
    return (0);
}

void	fill_render(t_render_data *render_data, t_data *data, t_point2D *points, t_size *size)
{
	render_data->data = data;
	render_data->points = points;
	render_data->size = size;
	render_data->color = BLACK_PIXEL;
}

int pixel_brain(char *argv, t_point2D *points, t_size *size)
{
    t_data data;
    t_render_data render_data;
    // t_rotation_data rotation_data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, argv);
    if (data.win_ptr == NULL)
        return (MLX_ERROR);
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	fill_render(&render_data, &data, points, size);
	mlx_loop_hook(data.mlx_ptr, ft_render, &render_data);
	// rotation_data.angle = 0.0;
	// render_data.rotation_data = &rotation_data;
	// mlx_key_hook(data.win_ptr, handle_rotation, &data);
	mlx_key_hook(data.win_ptr, handle_keypress, &data);
    mlx_loop(data.mlx_ptr);

    mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
    return (0);
}

void get_coordinates_from_map(int **map, t_size *size, t_point2D *points)
{
    int x, y, i;
    double scale_factor;
    int re_scaling_x, re_scaling_y;

    scale_factor = 17.0;

    re_scaling_x = WINDOW_WIDTH / 2 - ((size->width / 2) * scale_factor);
    re_scaling_y = WINDOW_HEIGHT / 2 - ((size->height / 2) * scale_factor);

    i = 0;
	y = 0;
    while (y < size->height)
    {
		x = 0;
        while (x < size->width)
        {
            int coord_x = (sqrt(3) / 2) * (x - y) * scale_factor + re_scaling_x;
            int coord_y = (sqrt(3) / 2) * (x + y) * scale_factor - map[y][x] * scale_factor + re_scaling_y;
            points[i] = (t_point2D){coord_x, coord_y};
            ft_printf("x = %d && y = %d\n", points[i].x, points[i].y);
            i++;
			x++;
        }
		y++;
    }
}

int main(int argc, char **argv)
{
    int fd;
    t_size size;
    t_point2D *points;
    
    init_structs(&size);
    if (argc <= 1)
        return (0);
    if (argc < 2)
    {
        ft_printf("Usage: %s filename\n", argv[0]);
        return (1);
    }
    ft_get_size(argv[1], &size);
    points = malloc(sizeof(t_point2D) * (size.height * size.width));
    if (!points)
        return (0);
    fd = open(argv[1], O_RDONLY);
    size.map = fill_tab(fd, size);
    show_maps(size);
    get_coordinates_from_map(size.map, &size, points);
    pixel_brain(argv[1], points, &size);
    ft_free_tab(size.map, size.height, points);
    close(fd);
    return (0);
}






	
	// pixel_brain(argv[1]);
	// ft_free_tab(size.map, size.height, points);
	// close(fd);
	// return (0);

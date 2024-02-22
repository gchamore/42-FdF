/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/22 17:23:11 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_render_data *create_render_data()
{
    t_render_data *render_data = malloc(sizeof(t_render_data));
    if (render_data)
	{
		render_data->rotation_data = malloc(sizeof(t_rotation_data));
        render_data->data = malloc(sizeof(t_data));
		render_data->size = malloc(sizeof(t_size));
    }
    return render_data;
}

void	ft_free_tab(int **test , int height) 
{
	int i;
	
	i = 0;
    if (test)
	{
        while (i < height)
		{
            free(test[i]);
            i++;
        }
        free(test);
    }
}

void free_render_data(t_render_data *render_data)
{
    	free(render_data->rotation_data);
    	free(render_data->data);
		free(render_data->points);
		free(render_data->size);
    	free(render_data);
}

void	init_structs(t_render_data *render_data)
{
	render_data->size->height = 0;
	render_data->size->width = 0;
}

void rotate_points(t_render_data *render_data, int num_points, double angle)
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
        new_x = render_data->points[i].x * cos_angle - render_data->points[i].y * sin_angle;
        new_y = render_data->points[i].x * sin_angle + render_data->points[i].y * cos_angle;
        render_data->points[i].x = new_x;
        render_data->points[i].y = new_y;
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
//         // rotate_points(render_data->points, render_data->render_data->size->width * render_data->render_data->size->height, render_data->rotation_data->angle);
//         // return (1);
//     }
// 	else if (keysym == XK_Right)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
//         // render_data->rotation_data->angle += rotation_step;
//         // rotate_points(render_data->points, render_data->render_data->size->width * render_data->render_data->size->height, render_data->rotation_data->angle);
//         // return (1);
//     }
//     return (0);
// }

int	handle_keypress(int keysym, t_render_data *render_data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(render_data->data->mlx_ptr, render_data->data->win_ptr);
		render_data->data->win_ptr = NULL;
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

void ft_render_dot(t_render_data *render_data)
{
    int i;
	int j;

	i = 0;
	j = 0;
    while (i < render_data->size->height)
    {
        j = 0;
        while (j < render_data->size->width - 1)
        {
            int index1 = i * render_data->size->width + j;
            int index2 = i * render_data->size->width + (j + 1);
            ft_render_line(&(render_data->data->img), render_data->points[index1].x, render_data->points[index1].y, render_data->points[index2].x, render_data->points[index2].y, WHITE_PIXEL);
            j++;
        }
        i++;
    }
    j = 0;
    while (j < render_data->size->width)
    {
        i = 0;
        while (i < render_data->size->height - 1)
        {
            int index1 = i * render_data->size->width + j;
            int index2 = (i + 1) * render_data->size->width + j;
            ft_render_line(&(render_data->data->img), render_data->points[index1].x, render_data->points[index1].y, render_data->points[index2].x, render_data->points[index2].y, WHITE_PIXEL);
            i++;
        }
        j++;
    }
}


int ft_render(t_render_data *render_data)
{
    if (render_data->data->win_ptr == NULL)
        return (1);
    render_background(&(render_data->data->img), render_data->color);
    ft_render_dot(render_data);
    mlx_put_image_to_window(render_data->data->mlx_ptr, render_data->data->win_ptr, render_data->data->img.mlx_img, 0, 0);
    return (0);
}

int pixel_brain(char *argv, t_render_data *render_data)
{
    render_data->data->mlx_ptr = mlx_init();
    if (render_data->data->mlx_ptr == NULL)
        return (MLX_ERROR);
    render_data->data->win_ptr = mlx_new_window(render_data->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, argv);
    if (render_data->data->win_ptr == NULL)
        return (MLX_ERROR);
    render_data->data->img.mlx_img = mlx_new_image(render_data->data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    render_data->data->img.addr = mlx_get_data_addr(render_data->data->img.mlx_img, &render_data->data->img.bpp, &render_data->data->img.line_len, &render_data->data->img.endian);
	mlx_loop_hook(render_data->data->mlx_ptr, ft_render, render_data);
	render_data->rotation_data->angle = 0.0;
	// mlx_key_hook(data->win_ptr, handle_rotation, &data);
	mlx_key_hook(render_data->data->win_ptr, handle_keypress, render_data);
    mlx_loop(render_data->data->mlx_ptr);
    mlx_destroy_image(render_data->data->mlx_ptr, render_data->data->img.mlx_img);
    mlx_destroy_display(render_data->data->mlx_ptr);
	free(render_data->data->mlx_ptr);
    return (0);
}

void get_coordinates_from_map(int **map, t_render_data *render_data)
{
    int x, y, i;
    double scale_factor;
    int re_scaling_x, re_scaling_y;

    scale_factor = 17.0;

    re_scaling_x = WINDOW_WIDTH / 2 - ((render_data->size->width / 2) * scale_factor);
    re_scaling_y = WINDOW_HEIGHT / 2 - ((render_data->size->height / 2) * scale_factor);

    i = 0;
	y = 0;
    while (y < render_data->size->height)
    {
		x = 0;
        while (x < render_data->size->width)
        {
            int coord_x = (sqrt(3) / 2) * (x - y) * scale_factor + re_scaling_x;
            int coord_y = (sqrt(3) / 2) * (x + y) * scale_factor - map[y][x] * scale_factor + re_scaling_y;
            render_data->points[i] = (t_point2D){coord_x, coord_y};
            ft_printf("x = %d && y = %d\n", render_data->points[i].x, render_data->points[i].y);
            i++;
			x++;
        }
		y++;
    }
}

int main(int argc, char **argv)
{
    int fd;
	t_render_data *render_data;
	int	**map;
	
	map = NULL;
	render_data = create_render_data();
	if (!render_data)
        return (MLX_ERROR);
    init_structs(render_data);
    if (argc <= 1)
        return (0);
    if (argc < 2)
    {
        ft_printf("Usage: %s filename\n", argv[0]);
        return (1);
    }
    ft_get_size(argv[1], render_data);
    render_data->points = malloc(sizeof(t_point2D) * (render_data->size->height * render_data->size->width));
    if (!render_data->points)
        return (0);
    fd = open(argv[1], O_RDONLY);
    map = fill_tab(fd, map, render_data);
	show_maps(render_data, map);
    get_coordinates_from_map(map, render_data);
	ft_free_tab(map, render_data->size->height);
    pixel_brain(argv[1], render_data);
	free_render_data(render_data);
    close(fd);
    return (0);
}
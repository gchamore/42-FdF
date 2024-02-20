/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/20 14:49:44 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


void	init_structs(t_size *size)
{
	size->height = 0;
	size->width = 0;
}

int handle_keypress(int keysym, t_data *data)
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
        {
            img_pix_put(img, j++, i, color);
        }
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
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void ft_draw(t_data *data, t_point2D *points, t_size *size)
{
    int i;

    i = 0;
    while (i < (size->height * size->width))
    {
        img_pix_put(&(data->img), points[i].x, points[i].y, WHITE_PIXEL);
        i++;
    }
}

int pixel_brain(char *argv, t_point2D *points, t_size *size)
{
    t_data data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);

    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, argv);
    if (data.win_ptr == NULL)
        return (MLX_ERROR);

    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
                                       &data.img.line_len, &data.img.endian);

    render_background(&(data.img), BLACK_PIXEL);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
    ft_draw(&data, points, size);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

    mlx_loop(data.mlx_ptr);

    mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
    return (0);
}

void get_coordinates_from_map(int **map, t_size *size, t_point2D *points)
{
    int x;
    int y;
    int i;
    int coord_x;
    int coord_y;
    double scale_factor = 15.0; // Facteur d'échelle pour agrandir les points

    int offset_x = WINDOW_WIDTH / 2; // Décalage pour ramener les coordonnées à des valeurs positives
    int offset_y = WINDOW_HEIGHT / 2;

    x = 0;
    i = 0;
    while (x < size->height)
    {
        y = 0;
        while (y < size->width)
        {
            coord_x = (sqrt(3) / 2) * (x - y) * scale_factor + offset_x;
            coord_y = (sqrt(3) / 2) * (x + y) * scale_factor - map[x][y] * scale_factor + offset_y;
            
            points[i] = (t_point2D){coord_x, coord_y};
            ft_printf("x = %d && y = %d\n", points[i].x, points[i].y);
            y++;
            i++;
        }
        x++;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/16 17:19:18 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void get_coordinates_from_map(int **map, t_size *size)
{
    int x; 
	int	y;
	int coord_x;
	int coord_y;
	t_point2D points[size->width * size->height];

    x = 0;
    while (x < size->height)
    {
        y = 0;
        while (y < size->width)
        {
            coord_x = (sqrt(3) / 2) * (x - y);
            coord_y = (sqrt(3) / 2) * (x + y) - map[x][y];
            points[x * size->width + y] = (t_point2D){coord_x, coord_y};
			ft_printf("x = %d && y = %d\n", coord_x, coord_y);
            y++;
        }
        x++;
    }
}

int	main(int argc, char **argv)
{
	int fd;
	t_size size;
	
	init_structs(&size);
	if (argc <= 1)
		return (0);
	if (argc < 2)
	{
		ft_printf("Usage: %s filename\n", argv[0]);
		return (1);
	}
	ft_get_size(argv[1], &size);
	fd = open(argv[1], O_RDONLY);
	size.map = fill_tab(fd, size);
	show_maps(size);
	get_coordinates_from_map(size.map, &size);
	// pixel_brain(argv[1]);
	ft_free_tab(size.map, size.height);
	close(fd);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/06 15:11:19 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


t_env *create_env()
{
    t_env *e;

	e = malloc(sizeof(t_env));
    if (e)
	{
		e->mooves = malloc(sizeof(t_mooves));
        e->data = malloc(sizeof(t_data));
		e->size = malloc(sizeof(t_size));
    }
    return e;
}


void	init_structs(t_env *e)
{
	e->size->height = 0;
	e->size->width = 0;
	e->mooves->angle_x = M_PI / 6;
	e->mooves->angle_y = M_PI / 6;
	e->mooves->angle_z = 0;
    e->mooves->scale_factor = 100.0;
    e->mooves->z_scale_factor = 0.4;
	e->mooves->step = 10;
	e->mooves->sign = 1;
	e->mooves->rotation_step = 0.1;
	e->mooves->rotation_angle = 0.1;
	e->mooves->z_scale_step = 0.1;
	e->mooves->color_choice = 1;
}

int main(int argc, char **argv)
{
    int fd;
	t_env *e;

	e = create_env();
	if (!e)
        return (free_env(e), 0);
    init_structs(e);
    if (argc != 2 || ft_get_size(argv[1], e) == 0)
		return (free(e->mooves), free(e->data), free(e->size), free(e), 0);
    e->points = malloc(sizeof(t_point2D) * (e->size->height * e->size->width));
    e->points_3D = malloc(sizeof(t_point3D) * (e->size->height * e->size->width));
	if (!e->points)
        return (0);
    fd = open(argv[1], O_RDONLY);
    e->size->map = fill_tab(fd, e);
	show_maps(e);
	close(fd);
    pixel_brain(argv[1], e);
	ft_free_tab(e->size->map, e->size->height);
	free_env(e);
    return (0);
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

void free_env(t_env *e)
{
    if(e->mooves)
		free(e->mooves);
	if(e->data)
    	free(e->data);
	if(e->points)
		free(e->points);
	if(e->size)
		free(e->size);
	if(e->points_3D)
		free(e->points_3D);
	if(e)
    	free(e);
}
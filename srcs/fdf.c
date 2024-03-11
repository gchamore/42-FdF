/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:56:39 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 15:18:42 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_env	*ft_create_env(void)
{
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (e)
	{
		e->mooves = malloc(sizeof(t_mooves));
		e->data = malloc(sizeof(t_data));
		e->size = malloc(sizeof(t_size));
	}
	return (e);
}

void	ft_init_structs(t_env *e)
{
	e->size->height = 0;
	e->size->width = 0;
	e->mooves->angle_x = M_PI / 6;
	e->mooves->angle_y = M_PI / 6 - 0.7;
	e->mooves->angle_z = 0;
	e->mooves->sf = 15.0;
	e->mooves->z_sf = 0.2;
	e->mooves->step = 5;
	e->mooves->sign = 1;
	e->mooves->rotation_step = 0.05;
	e->mooves->z_scale_step = 0.01;
	e->mooves->color = WHITE_PIXEL;
	e->mooves->keep_scaling = 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_env	*e;

	e = ft_create_env();
	if (!e)
		return (ft_free_env(e), 0);
	ft_init_structs(e);
	if (argc != 2 || ft_get_size(argv[1], e) == 0)
		return (free(e->mooves), free(e->data), free(e->size), free(e), 0);
	e->points_2d = malloc(sizeof(t_point2d) * (e->size->height * \
	e->size->width));
	e->points_3d = \
	malloc(sizeof(t_point3d) * (e->size->height * e->size->width));
	if (!e->points_2d)
		return (0);
	fd = open(argv[1], O_RDONLY);
	e->size->map = ft_fill_tab(fd, e);
	close(fd);
	ft_pixel_brain(argv[1], e);
	ft_free_tab(e->size->map, e->size->height);
	ft_free_env(e);
	return (0);
}

void	ft_free_tab(int **test, int height)
{
	int	i;

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

void	ft_free_env(t_env *e)
{
	if (e->mooves)
		free(e->mooves);
	if (e->data)
		free(e->data);
	if (e->points_2d)
		free(e->points_2d);
	if (e->size)
		free(e->size);
	if (e->points_3d)
		free(e->points_3d);
	if (e)
		free(e);
}

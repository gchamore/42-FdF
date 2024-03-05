/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/05 13:26:21 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


t_env *create_render_data()
{
    t_env *env = malloc(sizeof(t_env));
    if (env)
	{
		env->mooves = malloc(sizeof(t_mooves));
        env->data = malloc(sizeof(t_data));
		env->size = malloc(sizeof(t_size));
    }
    return env;
}


void	init_structs(t_env *env)
{
	env->size->height = 0;
	env->size->width = 0;
	env->mooves->angle_x = M_PI / 6;
	env->mooves->angle_y = M_PI / 6;
	env->mooves->angle_z = 0;
    env->mooves->scale_factor = 30.0;
    env->mooves->z_scale_factor = 0.4;
	env->mooves->step = 10;
	env->mooves->sign = 1;
	env->mooves->rotation_step = 0.1;
	env->mooves->rotation_angle = 0.1;
	env->mooves->z_scale_step = 0.1;
}

int main(int argc, char **argv)
{
    int fd;
	t_env *env;

	env = create_render_data();
	if (!env)
        return (MLX_ERROR);
    init_structs(env);
    if (argc <= 1)
        return (0);
    if (argc < 2)
    {
        ft_printf("Usage: %s filename\n", argv[0]);
        return (1);
    }
    ft_get_size(argv[1], env);
    env->points = malloc(sizeof(t_point2D) * (env->size->height * env->size->width));
    env->points_3D = malloc(sizeof(t_point3D) * (env->size->height * env->size->width));
	if (!env->points)
        return (0);
    fd = open(argv[1], O_RDONLY);
    env->size->map = fill_tab(fd, env);
	show_maps(env);
	close(fd);
    pixel_brain(argv[1], env);
	ft_free_tab(env->size->map, env->size->height);
	free_render_data(env);
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

void free_render_data(t_env *env)
{
    free(env->mooves);
    free(env->data);
	free(env->points);
	free(env->size);
	free(env->points_3D);
    free(env);
}
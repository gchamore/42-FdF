/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:03:01 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/26 16:49:39 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"


t_render_data *create_render_data()
{
    t_render_data *render_data = malloc(sizeof(t_render_data));
    if (render_data)
	{
		render_data->mooves = malloc(sizeof(t_mooves));
        render_data->data = malloc(sizeof(t_data));
		render_data->size = malloc(sizeof(t_size));
    }
    return render_data;
}

void	init_structs(t_render_data *render_data)
{
	render_data->size->height = 0;
	render_data->size->width = 0;
}

int main(int argc, char **argv)
{
    int fd;
	t_render_data *render_data;

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
    render_data->size->map = fill_tab(fd, render_data);
	show_maps(render_data);
	// ft_printf("\nmax -> x = %d && max ->  y = %d\n", render_data->size->max_x, render_data->size->max_y);
	// ft_printf("\nmid -> x = %d && mid ->  y = %d\n", render_data->size->mid_x, render_data->size->mid_y);
	// ft_printf("\nmid_win -> x = %d && mid_win ->  y = %d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    // ft_printf("x = %d && y = %d\n", render_data->points[0].x, render_data->points[0].y);
    pixel_brain(argv[1], render_data);
	ft_free_tab(render_data->size->map, render_data->size->height);
	free_render_data(render_data);
    close(fd);
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

void free_render_data(t_render_data *render_data)
{
    	free(render_data->mooves);
    	free(render_data->data);
		free(render_data->points);
		free(render_data->size);
    	free(render_data);
}
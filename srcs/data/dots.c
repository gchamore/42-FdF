/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/23 16:56:56 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	init_min_max(t_render_data *render_data)
{
	render_data->size->max_x = render_data->points[0].x;
    render_data->size->max_y = render_data->points[0].y;
	render_data->size->min_x = render_data->points[0].x;
    render_data->size->min_y = render_data->points[0].y;
}

void	get_min_max(t_render_data *render_data)
{
	int i;
	int j;
	int	n;

	init_min_max(render_data);
	i = 0;
	n = 0;
    while (i < render_data->size->height)
	{
		j = 0;
        while (j < render_data->size->width)
		{
            if (render_data->points[n].x > render_data->size->max_x)
                render_data->size->max_x = render_data->points[n].x;
			if (render_data->points[n].x < render_data->size->min_x)
                render_data->size->min_x = render_data->points[n].x;
            if (render_data->points[n].y > render_data->size->max_y)
                render_data->size->max_y = render_data->points[n].y;
			if (render_data->points[n].y < render_data->size->min_y)
                render_data->size->min_y = render_data->points[n].y;
			j++;
			n++;
        }
		i++;
    }
}

void get_pivot(t_render_data *render_data)
{
	double delta_x;
	double delta_y;
	int i;
	int j;
	int	n;
	
    get_min_max(render_data);
   	render_data->size->mid_x = (render_data->size->max_x + render_data->size->min_x) / 2;
    render_data->size->mid_y = (render_data->size->max_y + render_data->size->min_y) / 2;
    delta_x = WINDOW_WIDTH / 2 - render_data->size->mid_x;
    delta_y = WINDOW_HEIGHT / 2 - render_data->size->mid_y;
	ft_printf("\nNew pivot\n -> x = %d\n -> y = %d\n", delta_x, delta_y);

	i = 0;
	n = 0;
    while (i < render_data->size->height)
	{
		j = 0;
        while (j < render_data->size->width)
		{
            render_data->points[n].x += delta_x;
            render_data->points[n].y += delta_y;
			j++;
			n++;
        }
		i++;
    }
}

void get_coordinates_from_map(t_render_data *render_data)
{
    int x;
	int	y;
	int	i;
    double scale_factor;
    int re_scaling_x, re_scaling_y;
    int coord_x;
    int coord_y;
	int temp_x;
	int temp_y;

    scale_factor = 50.0;
    re_scaling_x = WINDOW_WIDTH / 2;
    re_scaling_y = WINDOW_HEIGHT / 2;
    i = 0;
    y = 0;
    while (y < render_data->size->height)
    {
        x = 0;
        while (x < render_data->size->width)
        {
            temp_x = x - render_data->size->width / 2;
            temp_y = y - render_data->size->height / 2;
            coord_x = (sqrt(3) / 2) * temp_x * scale_factor + re_scaling_x;
            coord_y = (sqrt(3) / 2) * temp_y * scale_factor - render_data->size->map[y][x] * scale_factor + re_scaling_y;
            render_data->points[i] = (t_point2D){coord_x, coord_y};
            i++;
            x++;
        }
        y++;
    }
}
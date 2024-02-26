/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:54:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/26 16:39:09 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void update_coordinates_and_pivot(t_render_data *render_data)
{
    get_coordinates_from_map(render_data);
    put_middle_map(render_data);
	get_pivot(render_data);
}

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
    get_min_max(render_data);
   	render_data->size->mid_x = (render_data->size->max_x + render_data->size->min_x) / 2;
    render_data->size->mid_y = (render_data->size->max_y + render_data->size->min_y) / 2;
}

void put_middle_map(t_render_data *render_data)
{
	double delta_x;
	double delta_y;
	double	new_mid_x;
	double	new_mid_y;
	int i;
	int j;
	int	n;

    get_min_max(render_data);
   	new_mid_x = (render_data->size->max_x + render_data->size->min_x) / 2;
    new_mid_y = (render_data->size->max_y + render_data->size->min_y) / 2;
    delta_x = render_data->size->mid_x - new_mid_x;
    delta_y = render_data->size->mid_y - new_mid_y;
	printf("\nNew pivot map\n -> x = %0.0lf\n -> y = %0.0lf\n", delta_x, delta_y);
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

void put_middle_window(t_render_data *render_data)
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
	printf("\nNew pivot win\n -> x = %0.0lf\n -> y = %0.0lf\n", delta_x, delta_y);

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
    int x, y, i;
    int re_scaling_x, re_scaling_y;
	int coord_x;
	int coord_y;

    re_scaling_x = WINDOW_WIDTH / 2;
    re_scaling_y = WINDOW_HEIGHT / 2;
    i = 0;
	y = 0;
    while (y < render_data->size->height)
    {
		x = 0;
        while (x < render_data->size->width)
        {
            coord_x = (sqrt(3) / 2) * (x - y) * render_data->mooves->scale_factor + re_scaling_x;
            coord_y = (sqrt(3) / 2) * (x + y) * render_data->mooves->scale_factor - render_data->size->map[y][x] * render_data->mooves->z_scale_factor * render_data->mooves->scale_factor + re_scaling_y;
            render_data->points[i] = (t_point2D){coord_x, coord_y};
            printf("x = %0.0lf && y = %0.0lf\n", render_data->points[i].x, render_data->points[i].y);
            i++;
			x++;
        }
		y++;
    }
}
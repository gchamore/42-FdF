/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/23 17:13:22 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	handle_keypress(int keysym, t_render_data *render_data)
{
	double rotation_step;

	rotation_step = 0.01;
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(render_data->data->mlx_ptr, render_data->data->win_ptr);
		render_data->data->win_ptr = NULL;
	}
	if (keysym == XK_E || keysym == XK_e)
	{
		render_data->rotation_data->angle -= rotation_step;
        rotate_points(render_data, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
        get_pivot(render_data);
		return (1);
    }
	if (keysym == XK_Q || keysym == XK_q)
	{
		render_data->rotation_data->angle += rotation_step;
        rotate_points(render_data, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
		get_pivot(render_data);
		return (1);
    }
	if (keysym == XK_Left)
	{
		render_data->rotation_data->angle += rotation_step;
        rotate_points_3d(render_data, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
		get_pivot(render_data);
		return (1);
    }
	if (keysym == XK_Right)
	{
		render_data->rotation_data->angle += rotation_step;
        rotate_points_3d(render_data, render_data->size->width * render_data->size->height, render_data->rotation_data->angle);
		get_pivot(render_data);
		return (1);
    }
	return (0);
}

void rotate_points_3d(t_render_data *render_data, int num_points, double angle)
{
    int i;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    double pivot_x = render_data->size->mid_x; // Coordonnées du pivot
    double pivot_y = render_data->size->mid_y; // Coordonnées du pivot

    // Par exemple, rotation autour de l'axe y
    for (i = 0; i < num_points; ++i)
    {
        // Translation pour pivoter autour du point pivot
        double translated_x = render_data->points[i].x - pivot_x;
        double translated_y = render_data->points[i].y - pivot_y;

        // Calcul des nouvelles coordonnées après rotation
        double new_x = translated_x * cos_angle - translated_y * sin_angle + pivot_x;
        double new_y = translated_x * sin_angle + translated_y * cos_angle + pivot_y;

        // Mettre à jour les coordonnées avec les nouvelles valeurs
        render_data->points[i].x = new_x;
        render_data->points[i].y = new_y;
    }
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
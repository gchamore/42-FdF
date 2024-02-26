/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/26 16:39:19 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	handle_keypress(int keysym, t_render_data *render_data)
{
	double rotation_step;
	double z_scale_step;
	double	sign;

	rotation_step = 0.01;
	z_scale_step = 0.1;
	sign = 1;

	// Pour quitter le programme

	if (keysym == XK_Escape)
	{
		mlx_destroy_window(render_data->data->mlx_ptr, render_data->data->win_ptr);
		render_data->data->win_ptr = NULL;
		return (0);
	}

	//Pour rotate sur les axes X et Y

	// else if (keysym == XK_D || keysym == XK_d)
	// {
	// 	render_data->mooves->angle -= rotation_step;
	// 	rotate_projection_horizontal(render_data, render_data->mooves->angle);
    // }
	// else if (keysym == XK_A || keysym == XK_a)
	// {
	// 	render_data->mooves->angle += rotation_step;
    //     rotate_projection_horizontal(render_data, render_data->mooves->angle);
    // }
	// else if (keysym == XK_W || keysym == XK_w)
	// {
	// 	render_data->mooves->angle -= rotation_step;
	// 	rotate_projection_vertical(render_data, render_data->mooves->angle);
	// 	return (1);
    // }
	// else if (keysym == XK_S || keysym == XK_s)
	// {
	// 	render_data->mooves->angle += rotation_step;
    //     rotate_projection_vertical(render_data, render_data->mooves->angle);
	// 	return (1);
    // }

	// 1 et 2 (cela sert a agrandir ou aplatir la structure projetee)

	else if (keysym == XK_1)
    {
        render_data->mooves->z_scale_factor += z_scale_step;
    }
    else if (keysym == XK_2)
    {
        render_data->mooves->z_scale_factor -= z_scale_step;
    }

	//FLECHES DE DIRECTION (bouger haut bas gauche droite)

	else if (keysym == XK_Left)
	{
        move_points_x(render_data, -sign);
		get_pivot(render_data);
		return(1);
    }
	else if (keysym == XK_Right)
	{
        move_points_x(render_data, sign);
		get_pivot(render_data);
		return(1);
    }
	else if (keysym == XK_Up)
	{
        move_points_y(render_data, -sign);
		get_pivot(render_data);
		return(1);
    }
	else if (keysym == XK_Down)
	{
        move_points_y(render_data, sign);
		get_pivot(render_data);
		return(1);
    }
	update_coordinates_and_pivot(render_data);
	return (0);
}
// Fonction pour effectuer une rotation horizontale de la projection isométrique (gauche-droite)
// void rotate_projection_horizontal(t_render_data *render_data, double rotation_step)
// {
    
// }

// // Fonction pour effectuer une rotation verticale de la projection isométrique (haut-bas)
// void rotate_projection_vertical(t_render_data *render_data, double rotation_step)
// {
    
// }
void move_points_x(t_render_data *render_data, double sign)
{
	int i;
	
	i = 0;
    while (i < render_data->size->width * render_data->size->height)
	{
		if (sign > 0)
			render_data->points[i].x += 5;
		else
			render_data->points[i].x -= 5;
		++i;
    }
}

void move_points_y(t_render_data *render_data, double sign)
{
	int i;
	
	i = 0;
    while (i < render_data->size->width * render_data->size->height)
	{
		if (sign > 0)
			render_data->points[i].y += 5;
		else
			render_data->points[i].y -= 5;
		++i;
    }
}

// static void	ft_reset(t_fdf *env)
// {
// 	env->camera->x_offset = 0;
// 	env->camera->y_offset = 0;
// 	if (env->camera->iso)
// 	{
// 		env->camera->x_angle = -0.615472907;
// 		env->camera->y_angle = -0.523599;
// 		env->camera->z_angle = 0.615472907;
// 	}
// 	else
// 	{
// 		env->camera->x_angle = -0.523599;
// 		env->camera->y_angle = -0.261799;
// 		env->camera->z_angle = 0;
// 	}
// 	env->camera->z_height = 1;
// 	env->camera->zoom = ft_min(WIDTH / env->map->width / 2,
// 			HEIGHT / env->map->height / 2);
// }
// double	ft_reset_angles(double angle)
// {
// 	if (angle >= M_PI)
// 		return (-2 * M_PI - angle);
// 	else if (angle <= -M_PI)
// 		return (2 * M_PI + angle);
// 	return (angle);
// }
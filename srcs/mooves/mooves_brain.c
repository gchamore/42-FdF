/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves_brain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:49:10 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 11:14:53 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

int	ft_handle_keypress(int keysym, t_env *e)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
		e->data->win_ptr = NULL;
		return (0);
	}
	return (0);
}

int	ft_destroy_red_cross(t_env *e)
{
	mlx_destroy_window(e->data->mlx_ptr, e->data->win_ptr);
	e->data->win_ptr = NULL;
	mlx_destroy_image(e->data->mlx_ptr, e->data->img.mlx_img);
	mlx_destroy_display(e->data->mlx_ptr);
	free(e->data->mlx_ptr);
	ft_free_tab(e->size->map, e->size->height);
	ft_free_env(e);
	exit(0);
}

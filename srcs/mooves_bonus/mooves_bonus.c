/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:23:09 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 11:06:53 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf_bonus.h"

void	init_keys(t_env *e)
{
	int	i;

	i = 0;
	while (i < NUM_KEYS)
	{
		e->bool->keys[i] = false;
		i++;
	}
}

int	ft_check_1(int keysym, t_env *e)
{
	if (keysym == XK_W || keysym == XK_w)
	{
		e->mooves->angle_x += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_S || keysym == XK_s)
	{
		e->mooves->angle_x -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
		e->mooves->angle_y += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_A || keysym == XK_a)
	{
		e->mooves->angle_y -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	return (0);
}

int	ft_check_2(int keysym, t_env *e)
{
	if (keysym == XK_Q || keysym == XK_q)
	{
		e->mooves->angle_z -= e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_E || keysym == XK_e)
	{
		e->mooves->angle_z += e->mooves->rotation_step;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_1 && e->mooves->z_sf < 5)
	{
		e->mooves->z_sf += e->mooves->z_scale_step;
		return (1);
	}
	else if (keysym == XK_2 && e->mooves->z_sf > -5)
	{
		e->mooves->z_sf -= e->mooves->z_scale_step;
		return (1);
	}
	return (0);
}

int	ft_check_3(int keysym, t_env *e)
{
	if (keysym == XK_X || keysym == XK_x)
	{
		if (e->mooves->color_choice == 6)
			e->mooves->color_choice = 1;
		else
			e->mooves->color_choice += 1;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_Z || keysym == XK_z)
	{
		if (e->mooves->color_choice == 1)
			e->mooves->color_choice = 6;
		else
			e->mooves->color_choice -= 1;
		return (ft_get_pivot(e), 1);
	}
	else if (keysym == XK_space)
	{
		ft_put_middle_window(e);
		ft_space_reset(e);
		return (ft_get_pivot(e), 1);
	}
	return (0);
}

int	ft_check_4(int keysym, t_env *e)
{
	if (keysym == XK_Left)
	{
		ft_move_points_x(e, -e->mooves->sign);
		ft_get_pivot(e);
		return (1);
	}
	else if (keysym == XK_Right)
	{
		ft_move_points_x(e, e->mooves->sign);
		ft_get_pivot(e);
		return (1);
	}
	else if (keysym == XK_Up)
	{
		ft_move_points_y(e, -e->mooves->sign);
		ft_get_pivot(e);
		return (1);
	}
	else if (keysym == XK_Down)
	{
		ft_move_points_y(e, e->mooves->sign);
		ft_get_pivot(e);
		return (1);
	}
	return (0);
}

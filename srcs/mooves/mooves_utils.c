/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooves_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:17:14 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/08 17:54:11 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_move_points_x(t_env *e, int sign)
{
	int	i;

	i = 0;
	while (i < e->size->width * e->size->height)
	{
		if (sign > 0)
			e->points_2d[i].x += e->mooves->step;
		else
			e->points_2d[i].x -= e->mooves->step;
		++i;
	}
}

void	ft_move_points_y(t_env *e, int sign)
{
	int	i;

	i = 0;
	while (i < e->size->width * e->size->height)
	{
		if (sign > 0)
			e->points_2d[i].y += e->mooves->step;
		else
			e->points_2d[i].y -= e->mooves->step;
		++i;
	}
}

void	ft_choose_color1(t_env *e)
{
	if (e->mooves->color_choice == 1)
	{
		e->mooves->color1 = DARK_GREEN_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_GREEN_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_GREEN_PIXEL;
		e->mooves->color4 = LIGHT_GREEN_PIXEL;
	}
	else if (e->mooves->color_choice == 2)
	{
		e->mooves->color1 = DARK_YELLOW_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_YELLOW_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_YELLOW_PIXEL;
		e->mooves->color4 = LIGHT_YELLOW_PIXEL;
	}
	else if (e->mooves->color_choice == 3)
	{
		e->mooves->color1 = DARK_BLUE_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_BLUE_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_BLUE_PIXEL;
		e->mooves->color4 = LIGHT_BLUE_PIXEL;
	}
	ft_choose_color2(e);
}

void	ft_choose_color2(t_env *e)
{
	if (e->mooves->color_choice == 4)
	{
		e->mooves->color1 = DARK_ORANGE_RED_PIXEL;
		e->mooves->color2 = MEDIUM_DARK_ORANGE_RED_PIXEL;
		e->mooves->color3 = MEDIUM_LIGHT_ORANGE_RED_PIXEL;
		e->mooves->color4 = LIGHT_ORANGE_RED_PIXEL;
	}
	else if (e->mooves->color_choice == 5)
	{
		e->mooves->color1 = TURQUOISE_PIXEL;
		e->mooves->color2 = PINK_PIXEL;
		e->mooves->color3 = GREEN_PIXEL;
		e->mooves->color4 = YELLOW_PIXEL;
	}
	else if (e->mooves->color_choice == 6)
	{
		e->mooves->color1 = VERY_DARK_BLUE_PIXEL;
		e->mooves->color2 = VERY_DARK_RED_PIXEL;
		e->mooves->color3 = VERY_DARK_GREEN_PIXEL;
		e->mooves->color4 = VERY_DARK_YELLOW_PIXEL;
	}
}

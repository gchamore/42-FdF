/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_brain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:00 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/11 14:16:24 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

int	ft_get_size(char *file, t_env *e)
{
	int		fd;
	int		ct;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	ct = 0;
	line = ft_get_next_line(fd);
	if (!line)
		return (0);
	e->size->width = ft_words_count(line);
	while (line != 0)
	{
		if (e->size->width != ft_words_count(line))
			return (free(line), close(fd), 0);
		if (e->size->width != 0)
		e->size->height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	**ft_fill_tab(int fd, t_env *e)
{
	char	**split;
	char	*line;
	t_tools	v;

	v.i = -1;
	line = ft_get_next_line(fd);
	if (!line)
		return (0);
	e->size->map = malloc(sizeof(int *) * e->size->height);
	if (!e->size->map)
		return (0);
	while (++v.i < e->size->height)
	{
		e->size->map[v.i] = malloc(sizeof(int) * e->size->width);
		if (!e->size->map[v.i])
			return (0);
		v.y = -1;
		split = ft_mod_split(line);
		while (++v.y < e->size->width)
			e->size->map[v.i][v.y] = ft_atoi(split[v.y]);
		free(line);
		ft_free_split(split);
		line = ft_get_next_line(fd);
	}
	return (e->size->map);
}

// void	show_maps(t_env *e)
// {
// 	int	i;
// 	int	y;

// 	i = 0;
// 	ft_printf("\nMAP = \n");
// 	while(i < e->size->height)
// 	{
// 		y = 0;
// 		ft_printf("\n");
// 		while(y < e->size->width)
// 		{
// 			ft_printf("%d ", e->size->map[i][y]);
// 			y++;
// 		}
// 		i++;
// 	}
// 	ft_printf("\n");
// 	ft_printf("\n");
// 	ft_printf("--------------------------------------------");
// 	ft_printf("\n");
// }
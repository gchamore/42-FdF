/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:38:36 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 12:01:11 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

int	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_words_count(char *str)
{
	int	length;
	int	i;
	int	check;

	length = 0;
	i = 0;
	check = 1;
	while (str[i] != '\0')
	{
		if (ft_is_delimiter(str[i]))
			check = 1;
		else if (check == 1)
		{
			length++;
			check = 0;
		}
		i++;
	}
	return (length);
}

int	ft_one_word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !ft_is_delimiter(str[i]))
		i++;
	return (i);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

int	ft_count_rows(char	**tab)
{
	int	row_count;

	row_count = 0;
	while (tab[row_count] != NULL)
	{
		row_count++;
	}
	return (row_count);
}

void	*ft_verif_str(char **split, char *str)
{
	int	row;
	int	collum;

	row = 0;
	while (*str)
	{
		collum = 0;
		split[row] = (char *)malloc(sizeof(char) * (ft_one_word_len(str) + 1));
		if (!split[row])
			return (NULL);
		while (*str && !ft_is_delimiter(*str))
		{
			split[row][collum] = *str;
			str++;
			collum++;
		}
		while (*str && ft_is_delimiter(*str))
			str++;
		split[row][collum] = '\0';
		row++;
	}
	split[row] = NULL;
	return (split);
}

char	**ft_mod_split(char *str)
{
	int		i;
	char	**split;

	i = 0;
	split = (char **)malloc(sizeof(char *) * (ft_words_count(str) + 1));
	if (!split)
		return (NULL);
	while (ft_is_delimiter(*str))
		str++;
	split = ft_verif_str(split, str);
	if (!split)
		return (free(split), NULL);
	return (split);
}

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

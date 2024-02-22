/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:38:36 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/22 17:13:48 by gchamore         ###   ########.fr       */
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
	int		i;

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

// Compte le nombre de lignes dans un tableau de chaînes de caractères.
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

// Vérifie et découpe une chaîne de caractères 'str' en sous-chaînes
// en fonction des espaces, des tabulations et des sauts de ligne.
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

// Découpe une chaîne de caractères en sous-chaînes en fonction
// des espaces, des tabulations et des sauts de ligne.
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


void	ft_get_size(char *file, t_render_data *render_data)
{
	int		fd;
	int		ct;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	ct = 0;
	line = ft_get_next_line(fd);
	if (!line)
		return ;
	render_data->size->width = ft_words_count(line);
	while (line != 0)
	{
		if (render_data->size->width != 0)
		render_data->size->height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
}


int **fill_tab(int fd, int **map,t_render_data *render_data)
{
    char **split;
    char *line;
    int i;
    int y;

    i = 0;
    y = 0;
	line = NULL;
    line = ft_get_next_line(fd);
    if (!line)
        return (0);
    map = malloc(sizeof(int *) * render_data->size->height);
    if (!map)
        return (0);
    while (i < render_data->size->height)
    {
        map[i] = malloc(sizeof(int) * render_data->size->width);
        if (!map[i])
            return (0);
        y = 0;
        split = ft_mod_split(line);
        while (y < render_data->size->width)
        {
			map[i][y] = ft_atoi(split[y]);
            y++;
        }
        free(line);
		ft_free_split(split);
        line = ft_get_next_line(fd);
        i++;
    }
    return (map);
}

void	show_maps(t_render_data *render_data, int **map)
{
	int i;
	int y;

	i = 0;
	ft_printf("\nMAP = \n");
	while(i < render_data->size->height)
	{
		y = 0;
		ft_printf("\n");
		while(y < render_data->size->width)
		{
			ft_printf("%d ", map[i][y]);
			y++;
		}
		i++;
	}
	ft_printf("\n");
	ft_printf("\n");
	ft_printf("--------------------------------------------");
	ft_printf("\n");
}



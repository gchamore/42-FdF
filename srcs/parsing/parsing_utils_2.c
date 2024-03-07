/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:03 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 13:32:37 by gchamore         ###   ########.fr       */
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

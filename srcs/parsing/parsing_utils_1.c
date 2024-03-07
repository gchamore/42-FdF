/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:30:37 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 13:34:52 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/fdf.h"

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

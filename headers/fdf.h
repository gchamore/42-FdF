/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:02:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/16 16:46:53 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define	WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_size
{
	int			**map;
	int			height;
	int			width;
}	t_size;

typedef struct	s_point3D
{
    int	x;
    int	y;
    int	z;
}	t_point3D;

typedef struct	s_point2D
{
	int	x;
	int	y;
}	t_point2D;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//#################################
//#	    	   PARSING		      #
//#################################

void		show_maps(t_size size);
int			**fill_tab(int fd, t_size size);
void		ft_get_size(char *file, t_size *size);
char		**ft_mod_split(char *str);
void		*ft_verif_str(char **split, char *str);
int			ft_count_rows(char	**tab);
void		ft_free_tab(int **map, int height) ;
void		ft_free_split(char **split);
int			ft_one_word_len(char *str);
int			ft_words_count(char *str);
int			ft_is_delimiter(char c);


//#################################
//#	    	   MATRICE		      #
//#################################
void get_coordinates_from_map(int **map, t_size *size);

//#################################
//#	    	   	 FDF	 	      #
//#################################
void		init_structs(t_size *size);

//#################################
//#	    	   	 PIXELS	 	      #
//#################################
void		pixel_brain();
void		ft_put_pixel(t_data *data, int x, int y, int color);

#endif
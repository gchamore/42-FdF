/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:02:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/22 17:14:13 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// colors

#define BLACK_PIXEL 0x000000   // Noir
#define WHITE_PIXEL 0xFFFFFF   // Blanc
#define RED_PIXEL 0xFF0000     // Rouge
#define GREEN_PIXEL 0x00FF00   // Vert
#define BLUE_PIXEL 0x0000FF    // Bleu
#define YELLOW_PIXEL 0xFFFF00  // Jaune
#define ORANGE_PIXEL 0xFFA500  // Orange
#define GRAY_PIXEL 0x808080     // Gris
#define PINK_PIXEL 0xFFC0CB     // Rose
#define MAROON_PIXEL 0x800000   // Marron
#define TURQUOISE_PIXEL 0x40E0D0 // Turquoise
#define GOLD_PIXEL 0xFFD700     // Or
#define SILVER_PIXEL 0xC0C0C0   // Argent

#define MLX_ERROR 1

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>


typedef struct s_size
{
	int			height;
	int			width;
}	t_size;

typedef struct	s_point2D
{
	int	x;
	int	y;
}	t_point2D;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
}	t_data;

typedef struct s_rect
{
    int	x;
    int	y;
    int width;
    int height;
    int color;
}	t_rect;

typedef struct s_rotation_data
{
    double angle;
}	t_rotation_data;

typedef struct s_render_data
{
	t_rotation_data *rotation_data;
    t_data			*data;
    t_point2D		*points;
    t_size			*size;
    int				color;
}	t_render_data;


//#################################
//#	    	   PARSING		      #
//#################################

void		show_maps(t_render_data *render_data, int **map);
int			**fill_tab(int fd, int **map,t_render_data *render_data);
void		ft_get_size(char *file, t_render_data *render_data);
char		**ft_mod_split(char *str);
void		*ft_verif_str(char **split, char *str);
int			ft_count_rows(char	**tab);
void		ft_free_tab(int **test , int height);
void		ft_free_split(char **split);
int			ft_one_word_len(char *str);
int			ft_words_count(char *str);
int			ft_is_delimiter(char c);


//#################################
//#	    	   MATRICE		      #
//#################################

void get_coordinates_from_map(int **map, t_render_data *render_data);

//#################################
//#	    	   	 FDF	 	      #
//#################################
void	init_structs(t_render_data *render_data);

//#################################
//#	    	   	 PIXELS	 	      #
//#################################

t_render_data	*create_render_data();
void			render_background(t_img *img, int color);
int				pixel_brain(char *argv, t_render_data *render_data);
void			render_background(t_img *img, int color);
int				handle_keypress(int keysym, t_render_data *render_data);
// int			handle_rotation(int keysym, t_data *data);
void			img_pix_put(t_img *img, int x, int y, int color);
int				ft_render(t_render_data *render_data);
void			ft_render_dot(t_render_data *render_data);
void			rotate_points(t_render_data *render_data, int num_points, double angle);
void			ft_render_line(t_img *img, int x0, int y0, int x1, int y1, int color);
int				my_abs(int x);
void			free_render_data(t_render_data *render_data);



#endif
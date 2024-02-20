/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:02:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/02/20 14:38:28 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// commands

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
# define SPACE 49
# define KEY_R 15
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define ESCAPE 53

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

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
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

//#################################
//#	    	   PARSING		      #
//#################################

void		show_maps(t_size size);
int			**fill_tab(int fd, t_size size);
void		ft_get_size(char *file, t_size *size);
char		**ft_mod_split(char *str);
void		*ft_verif_str(char **split, char *str);
int			ft_count_rows(char	**tab);
void		ft_free_tab(int **map, int height, t_point2D *points);
void		ft_free_split(char **split);
int			ft_one_word_len(char *str);
int			ft_words_count(char *str);
int			ft_is_delimiter(char c);


//#################################
//#	    	   MATRICE		      #
//#################################

void get_coordinates_from_map(int **map, t_size *size, t_point2D *points);

//#################################
//#	    	   	 FDF	 	      #
//#################################
void	init_structs(t_size *size);

//#################################
//#	    	   	 PIXELS	 	      #
//#################################

void		render_background(t_img *img, int color);
int			pixel_brain(char *argv, t_point2D *points, t_size *size);
void		render_background(t_img *img, int color);
int			handle_keypress(int keysym, t_data *data);
void		img_pix_put(t_img *img, int x, int y, int color);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:02:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/07 14:07:36 by gchamore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// 4320p (8K) : 7 680 x 4 320.
// 2160p (4K) : 3 840 x 2 160.
// 1440p (2K) : 2 560 x 1 440.
// 1080p (HD) : 1 920 x 1 080.
// 720p (HD) : 1 280 x 7 20.
// 480p (SD) : 854 x 480.
// 360p (SD) : 640 x 360.
// 240p (SD) : 426 x 240.

# define WINDOW_WIDTH 854
# define WINDOW_HEIGHT 480
# define SCALE_FACTOR_MAX 110
# define SCALE_FACTOR_MIN 1
# define M_PI 3.14159265358979323846

// colors classiques

# define BLACK_PIXEL 0x000000   // Noir
# define WHITE_PIXEL 0xFFFFFF   // Blanc
# define RED_PIXEL 0xFF0000     // Rouge
# define GREEN_PIXEL 0x00FF00   // Vert
# define BLUE_PIXEL 0x0000FF    // Bleu
# define YELLOW_PIXEL 0xFFFF00  // Jaune
# define ORANGE_PIXEL 0xFFA500  // Orange
# define GRAY_PIXEL 0x808080     // Gris
# define PINK_PIXEL 0xFFC0CB     // Rose
# define MAROON_PIXEL 0x800000   // Marron
# define TURQUOISE_PIXEL 0x40E0D0 // Turquoise
# define GOLD_PIXEL 0xFFD700     // Or
# define SILVER_PIXEL 0xC0C0C0   // Argent

// map vertes
# define DARK_GREEN_PIXEL 0x006400
# define MEDIUM_DARK_GREEN_PIXEL 0x228B22
# define MEDIUM_LIGHT_GREEN_PIXEL 0x3CB371
# define LIGHT_GREEN_PIXEL 0x7FFF00

// map bleu

# define DARK_BLUE_PIXEL 0x00008B
# define MEDIUM_DARK_BLUE_PIXEL 0x4169E1
# define MEDIUM_LIGHT_BLUE_PIXEL 0x4682B4
# define LIGHT_BLUE_PIXEL 0x87CEEB 

// map oranges

# define DARK_ORANGE_RED_PIXEL 0x8B2500
# define MEDIUM_DARK_ORANGE_RED_PIXEL 0xB22222
# define MEDIUM_LIGHT_ORANGE_RED_PIXEL 0xCD5C5C
# define LIGHT_ORANGE_RED_PIXEL 0xFF6347

// map jaune

# define DARK_YELLOW_PIXEL 0x8B8B00
# define MEDIUM_DARK_YELLOW_PIXEL 0xBDB76B
# define MEDIUM_LIGHT_YELLOW_PIXEL 0xFFFFE0
# define LIGHT_YELLOW_PIXEL 0xFFFF00

# define MLX_ERROR 1

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

typedef struct s_tools
{
	int			x;
	int			y;
	int			i;
	int			z;
	int			mid_win_x;
	int			mid_win_y;
	double		delta_x;
	double		delta_y;
	double		new_mid_x;
	double		new_mid_y;
	int			j;
	int			n;
	double		temp_x;
	double		temp_y;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			diff_x;
	int			diff_y;
	int			step_x;
	int			step_y;
	int			error;
	int			error2;
}	t_tools;

typedef struct s_size
{
	int			**map;
	int			height;
	int			width;
	int			max_x;
	int			max_y;
	int			max_z;
	int			min_x;
	int			min_y;
	int			min_z;
	int			mid_x;
	int			mid_y;
}	t_size;

typedef struct s_point2d
{
	double		x;
	double		y;
}	t_point2d;

typedef struct s_point3d
{
	double		x;
	double		y;
	double		z;
	int			color;
}	t_point3d;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	int			cur_img;
}	t_data;

typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	int			color;
}	t_rect;

typedef struct s_mooves
{
	double		angle_x;
	double		angle_y;
	double		angle_z;
	double		z_sf;
	double		z_scale_step;
	double		sf;
	double		rotation_step;
	double		rotation_angle;
	int			sign;
	int			step;
	int			color;
	int			color_choice;
	int			color1;
	int			color2;
	int			color3;
	int			color4;
	int			keep_scaling;
}	t_mooves;

typedef struct s_env
{
	t_mooves	*mooves;
	t_data		*data;
	t_point2d	*points_2d;
	t_point3d	*points_3d;
	t_size		*size;
	int			*color;
}	t_env;

//#################################
//#	    	   	 DOTS	 	      #
//#################################

// dots brain.c
void			ft_get_coordinates_from_map(t_env *e);
void			ft_rotate_point_x(t_point3d *points_3d, double angle);
void			ft_rotate_point_y(t_point3d *points_3d, double angle);
void			ft_rotate_point_z(t_point3d *points_3d, double angle);
// dots.c
void			ft_put_middle_map(t_env *e);
void			ft_put_middle_window(t_env *e);
void			ft_update_coordinates_and_pivot(t_env *e);
// dots_utils.c
void			ft_get_min_max(t_env *e);
void			ft_get_pivot(t_env *e);
void			ft_verify_size(t_env *e);
void			ft_init_min_max(t_env *e);

//#################################
//#	    	   	 MOOVES	 	      #
//#################################

// mooves_brain.c
int				ft_handle_keypress(int keysym, t_env *e);
int				ft_handle_mouse(int button, int x, int y, t_env *e);
int				ft_destroy_red_cross(t_env *e);
void			ft_space_reset(t_env *e);
//mooves.c
int				ft_check_1(int keysym, t_env *e);
int				ft_check_2(int keysym, t_env *e);
int				ft_check_3(int keysym, t_env *e);
int				ft_check_4(int keysym, t_env *e);
//mooves_utils.c
void			ft_move_points_x(t_env *e, int sign);
void			ft_move_points_y(t_env *e, int sign);
void			ft_choose_color1(t_env *e);
void			ft_choose_color2(t_env *e);

//#################################
//#	    	   PARSING		      #
//#################################

// parsing_brain.c
int				ft_get_size(char *file, t_env *e);
int				**ft_fill_tab(int fd, t_env *e);
// parsing_utils_1.c
char			**ft_mod_split(char *str);
void			*ft_verif_str(char **split, char *str);
// parsing_utils_2.c
int				ft_is_delimiter(char c);
int				ft_words_count(char *str);
int				ft_one_word_len(char *str);
void			ft_free_split(char **split);
int				ft_count_rows(char	**tab);

//#################################
//#	    	   	 PIXELS	 	      #
//#################################

// pixel_brain.c
int				ft_pixel_brain(char *argv, t_env *e);
int				ft_render(t_env *e);
void			ft_render_background(t_img *img, int color);
void			ft_render_dot(t_env *e);
// pixel_draw.c
void			ft_init_render_line(t_tools *v, t_env *e, int index1, \
int index2);
void			ft_render_line(t_img *img, t_tools *v, t_env *e);
void			ft_img_pix_put(t_img *img, int x, int y, int color);
void			ft_my_img_pix_put(t_img *img, int x, int y, int color);
// pixel_utils.c
void			ft_make_horizontal(t_env *e, t_tools v);
void			ft_make_vertical(t_env *e, t_tools v);
int				ft_my_abs(int c);
int				ft_get_percent(int max, int min, int z);
void			ft_check_z(t_env *e, int x, int y);

//#################################
//#	    	   	 FDF	 	      #
//#################################

int				main(int argc, char **argv);
t_env			*ft_create_env(void);
void			ft_init_structs(t_env *e);
void			ft_free_tab(int **test, int height);
void			ft_free_env(t_env *e);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchamore <gchamore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:02:55 by gchamore          #+#    #+#             */
/*   Updated: 2024/03/05 15:58:32 by gchamore         ###   ########.fr       */
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

#define WINDOW_WIDTH 854
#define WINDOW_HEIGHT 480
#define SCALE_FACTOR_MAX 70
#define SCALE_FACTOR_MIN 1
#define M_PI 3.14159265358979323846

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


typedef struct	s_tools
{
    int x;
	int y;
	int i;
    int mid_win_x;
	int mid_win_y;
	double delta_x;
	double delta_y;
	double	new_mid_x;
	double	new_mid_y;
	int j;
	int	n;
	double	temp_x;
	double	temp_y;
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

typedef struct	s_point2D
{
	double	x;
	double	y;
}	t_point2D;

typedef struct	s_point3D
{
    double	x;
    double	y;
    double	z;
	int		color;
}	t_point3D;

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

typedef struct s_mooves
{
	double			angle_x;
	double			angle_y;
	double			angle_z;
    double			z_scale_factor;
	double			z_scale_step;
	double			scale_factor;
	double			rotation_step;
	double			rotation_angle;
	int				sign;
	int				step;
}	t_mooves;

typedef struct s_env
{
	t_mooves		*mooves;
    t_data			*data;
    t_point2D		*points;
	t_point3D		*points_3D;
    t_size			*size;
    int				color;
}	t_env;


//#################################
//#	    	   PARSING		      #
//#################################

void		show_maps(t_env *render_data);
int			**fill_tab(int fd, t_env *render_data);
void		ft_get_size(char *file, t_env *render_data);
char		**ft_mod_split(char *str);
void		*ft_verif_str(char **split, char *str);
int			ft_count_rows(char	**tab);
void		ft_free_tab(int **test , int height);
void		ft_free_split(char **split);
int			ft_one_word_len(char *str);
int			ft_words_count(char *str);
int			ft_is_delimiter(char c);

//#################################
//#	    	   	 DOTS	 	      #
//#################################

void			init_min_max(t_env *render_data);
void			get_min_max(t_env *render_data);
void			get_pivot(t_env *render_data);
void			put_middle_window(t_env *render_data);
void			get_coordinates_from_map(t_env *render_data);
void			put_middle_map(t_env *render_data);



//#################################
//#	    	   	 FDF	 	      #
//#################################

t_env	*create_render_data();
void			init_structs(t_env *render_data);
int				handle_keypress(int keysym, t_env *render_data);
int				main(int argc, char **argv);
void			ft_free_tab(int **test , int height);
void			free_render_data(t_env *render_data);


//#################################
//#	    	   	 PIXELS	 	      #
//#################################

void			render_background(t_img *img, int color);
int				my_abs(int c);
void			ft_render_line(t_img *img, int x0, int y0, int x1, int y1, int color);
void			ft_render_dot(t_env *render_data);
int				ft_render(t_env *render_data);
void			ft_img_pix_put(t_img *img, int x, int y, int color);
void			img_pix_put(t_img *img, int x, int y, int color);
int				pixel_brain(char *argv, t_env *render_data);

//#################################
//#	    	   	 MOOVES	 	      #
//#################################

void			update_coordinates_and_pivot(t_env *render_data);
void			move_points_x(t_env *env, int sign);
void			move_points_y(t_env *env, int sign);
void			space_reset(t_env *env);
int				destroy_red_cross(t_env *env);
int				handle_mouse(int button, int x, int y, t_env *env);
void			rotate_point_x(t_point3D *points_3D, double angle);
void			rotate_point_y(t_point3D *points_3D, double angle);
void			rotate_point_z(t_point3D *points_3D, double angle);
void			verify_size(t_env *env);


#endif
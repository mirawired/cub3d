/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:10:47 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/11 12:43:15 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H
# define SPRITENBR 4

typedef struct s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}	t_rgb;
typedef union u_color
{
	int		color;
	t_rgb	s_rgb;
}	t_color;
typedef struct s_pars
{
	_Bool	n;
	_Bool	s;
	_Bool	e;
	_Bool	w;
}	t_pars;
typedef struct s_arg
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_color[3];
	int		c_color[3];
	t_color	*rgb_f;
	t_color	*rgb_c;
	char	**map;
	int		**fmap;
	int		width;
	int		height;
}	t_arg;
typedef struct s_data
{
	char	**raw;
	int		lines;
	int		mlines;
	int		endmap;
	int		fd;
	int		k;
	size_t	err;
	t_pars	pars;
	t_arg	*arg;
}	t_data;
typedef struct s_stash
{
	char			*str;
	struct s_stash	*next;
}	t_stash;
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;
typedef struct s_int_point
{
	int	x;
	int	y;
}	t_int_point;
typedef struct s_player {
	t_point	pos;
	double	angle;
	t_point	dir_vector;
	t_point	plane_vector;
	t_point	init_pos;
	int		init_angle;
	double	size;
}	t_player;
typedef struct s_buffer
{
	void	*img;
	char	*address;
	int		bit_per_pixel;
	int		line_length;
	int		endian;
}	t_buffer;
typedef struct s_texture
{
	t_color	*texture;
	int		width;
	int		height;
}	t_texture;
typedef struct s_sprite
{
	double		x;
	double		y;
	t_texture	**texture;
}	t_sprite;
typedef struct s_cs
{
	double	spritex;
	double	spritey;
	double	inv_det;
	double	transx;
	double	transy;
	int		sprite_screen_x;
	int		v_move_screen;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
}	t_cs;
typedef struct s_spr
{
	t_sprite	*curr;
	t_sprite	sprite[SPRITENBR];
	double		zbuffer[WIDTH];
	int			sprite_order[SPRITENBR];
	double		sprite_dist[SPRITENBR];
	t_cs		cs;
	int			spr_i;
}	t_spr;
typedef struct s_raydata
{
	void			*mlx;
	void			*mlx_win;
	t_buffer		*img_buffer;
	t_buffer		*img_menu;
	t_player		*player;
	int				map_width;
	int				map_height;
	int				**map;
	t_texture		**texture;
	t_color			ceil_color;
	t_color			floor_color;
	long			last_frame;
	t_spr			*spr;
	t_arg			*arg;
	t_game_state	game_state;
}	t_raydata;
typedef struct s_r
{
	double			perp_wall_dist;
	t_color			ray_color;
	t_texture_index	texture_index;
	int				grid_size_x;
	int				grid_size_y;
	t_point			pos;
	double			camerax;
	t_point			ray_dir;
	int				map_x;
	int				map_y;
	t_point			side_dist;
	t_point			delta_dist;
	int				step_x;
	int				step_y;
	int				side;
	int				hit;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
}	t_r;
typedef struct s_h
{
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	int		p;
	float	posz;
	float	rawdist;
	float	floorstepx;
	float	floorstepy;
	float	floorx;
	float	floory;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
}	t_h;
typedef struct s_map
{
	double	grid_size_x;
	double	grid_size_y;
	t_color	grid_color;
	t_color	nmi_color;
}	t_map;
typedef struct s_draw_player
{
	t_point	front;
	t_point	left;
	t_point	right;
	double	player_angle;
	t_point	player_pos;
	t_color	player_color;
}	t_draw_player;
#endif

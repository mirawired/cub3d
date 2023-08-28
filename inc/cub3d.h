/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:15:14 by avassor           #+#    #+#             */
/*   Updated: 2023/08/28 14:58:37 by avassor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>

# define GNL_BUFFER_SIZE 1
# define NOARG 129
# define MLLOC 130
# define ARGRR 131
# define EMPT 132
# define DIR 133
# define EXT 134
# define RFD 135
# define NOID 136
# define MAPERROR 137

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
	_Bool	N;
	_Bool	S;
	_Bool	E;
	_Bool	W;
}	t_pars;

typedef struct s_arg
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F[3];
	int		C[3];
	t_color	*rgbF;
	t_color	*rgbC;
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
	int		fd;
	size_t	err;
	t_pars	pars;
	t_arg	*arg;
}	t_data;

// ..................... PARSING ............................................

t_data	*init_data(void);
_Bool	is_cub(char *arg);
_Bool	is_dir(char *arg);
_Bool	chk_arg(t_data *data, char *arg);
_Bool	get_arg(t_data *data);
void	clean_raw(t_data *data);
_Bool	copy_line(t_data *data, char *line);
_Bool	upscale_raw(t_data *data);
int		ft_strlen(const char *s);
int		rror(int err, t_data *data);
_Bool	ft_sprstrncmp(char *s1, char *s2);
_Bool	pars_map(t_data *data);
_Bool	search_id(t_data *data, char **fill, char *id);
_Bool	copy_id(t_data *data, char **fill, char *raw);
_Bool	ft_strncmp(char *needle, char *haystack, int size);
_Bool	copy_nbr(t_data *data, int *arr, char *raw);
_Bool	search_id_nbr(t_data *data, int *arr, char *id);
int		ft_atoi(const char *p);
_Bool	convert_nbr(t_data *data, int *arr, char *raw, int l, int k);
void	ft_strncpy(char *prev, char *new, int nbr);
void	clear_line(char *raw);
_Bool	chk_bottop(t_data *data, char *line, int j);
_Bool	search_map(t_data *data, char **raw);
_Bool	chk_origin(t_data *data,  char *line, char id, int i);
_Bool	chk_line(t_data *data, char *line, int j);
_Bool	is_origin(char id);
_Bool	chk_edges(t_data *data, char c, char d);
_Bool	convert_map(t_data *data, t_arg *arg);
_Bool	to_integers(t_data *data, t_arg *arg);
_Bool	convert_rgb(t_arg *arg);

// ..................... GNL ................................................

typedef struct s_stash
{
	char			*str;
	struct s_stash	*next;
}	t_stash;

char			*get_next_line(int fd);
void			ft_reader(int fd, t_stash **stash);
void			ft_addline(t_stash *stash, char **line);
void			ft_addbuff(char *buf, t_stash **stash, int i);
void			ft_recover(t_stash **stash);
size_t			line_chk2(char *a, char *b);
char			*limited(t_stash **stash, char *line, int fd);
void			ft_left(t_stash **stash, t_stash *new, char *p1, char *p2);
int				ft_scanner(t_stash *stash);
t_stash			*ft_lst_get_last(t_stash *stash);
void			ft_unleash(t_stash *stash);
int				ft_linkbrows(t_stash *stash);
void			ft_strcpy(char *prev, char *new);

// ..................... GARBAGE COLLECTION ............................................
#include "gc.h"
t_garbage **gc_add(t_garbage *ptr);
void	gc_free(void);
int	gc_del(void *ptr);
void	*gc_alloc(size_t nmemb, size_t size);

// ..................... RAYCAST ............................................

# define BUFFER_SIZE 2048
# define RADIAN 0.0174532925
# define PI 3.14159265359
# define WIDTH 600
# define OFFSET_3D 600
# define HEIGHT 600
# define TWIDTH 1200
# define GRID_WIDTH 20
# define GRID_HEIGHT 20
# define SPRITENBR 2

typedef struct s_point
{
	double x;
	double y;
}	t_point;

typedef struct s_int_point
{
	int x;
	int y;
}	t_int_point;

typedef struct s_player {
	t_point pos;
	double angle;
    t_point dir_vector;
    t_point plane_vector;
	double size;
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
    t_color *texture;
    int     width;
    int     height;
}   t_texture;

typedef struct s_sprite
{
	double		x;
	double		y;
	t_texture	*texture;
}	t_sprite;

typedef struct s_spr
{
	t_sprite	sprite[SPRITENBR];
	double		Zbuffer[WIDTH];
	int			sprite_order[SPRITENBR];
	double		spride_dist[SPRITENBR];
}	t_spr;

typedef struct s_raydata
{
	void		*mlx;
	void		*mlx_win;
	t_buffer	*img_buffer;
	t_player	*player;
    int        map_width;
    int        map_height;
	int			**map;
    t_texture    *NO;
    t_texture    *SO;
    t_texture    *WE;
    t_texture    *EA;
	// t_texture	*sprt1;
	// t_texture	*sprt2;
    t_color     ceil_color;
    t_color     floor_color;
	long		last_frame;
	t_spr		*spr;
}	t_raydata;

int		render(t_raydata *raydata);
int		key_pressed(int keycode, t_raydata *raydata);
int		my_mlx_pixel_put(t_buffer *raydata, t_color color, t_int_point coord);
void	draw_line(t_raydata *raydata, t_color color, t_point from, t_point to);
int		ft_abs(int n);
void	clear_buffer(t_raydata *raydata);
void	draw_player(t_raydata *raydata);
void	fill_rectangle(t_raydata *raydata, t_color color, t_point top_left, t_point bottom_right);
void	draw_rays(t_raydata *raydata);
t_point	calc_point(t_point from, double angle, double distance);

int		raycast(t_arg *arg);
void	grab_arg(t_raydata *raydata, t_arg *arg);

void	draw_sprites(t_raydata * data, double perpWallDist, t_point pos);

#endif

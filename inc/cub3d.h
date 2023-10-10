/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avassor <avassor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:34:08 by avassor           #+#    #+#             */
/*   Updated: 2023/10/10 21:19:25 by avassor          ###   ########.fr       */
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
# include "config.h"
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
# define BLACK -16777216
# include "gc.h"
# include "enums.h"
# include "data_structures.h"

// ..................... PARSING ............................................
t_data			*init_data(void);
_Bool			is_cub(char *arg);
_Bool			is_dir(char *arg);
_Bool			chk_arg(t_data *data, char *arg);
_Bool			get_arg(t_data *data);
void			clean_raw(t_data *data);
_Bool			copy_line(t_data *data, char *line);
_Bool			upscale_raw(t_data *data);
int				ft_strlen(const char *s);
int				rror(int err, t_data *data);
_Bool			ft_sprstrncmp(char *s1, char *s2);
_Bool			pars_map(t_data *data);
_Bool			search_id(t_data *data, char **fill, char *id);
_Bool			copy_id(t_data *data, char **fill, char *raw);
_Bool			ft_strncmp(char *needle, char *haystack, int size);
_Bool			copy_nbr(t_data *data, int *arr, char *raw);
_Bool			search_id_nbr(t_data *data, int *arr, char *id);
int				ft_atoi(const char *p);
_Bool			convert_nbr(t_data *data, int *arr, char *raw, int l);
void			ft_strncpy(char *prev, char *new, int nbr);
void			clear_line(char *raw);
_Bool			chk_bottop(t_data *data, char *line, int j);
_Bool			search_map(t_data *data, char **raw);
_Bool			chk_origin(t_data *data, char *line, char id, int i);
_Bool			chk_line(t_data *data, char *line, int j);
_Bool			is_origin(char id);
_Bool			chk_edges(t_data *data, char c, char d);
_Bool			convert_map(t_data *data, t_arg *arg);
_Bool			to_integers(t_data *data, t_arg *arg);
_Bool			convert_rgb(t_arg *arg);
void			do_conv(t_arg *arg, int i, int j);
_Bool			map_op(t_data *data, char **raw, int i, int j);
// ..................... GNL ................................................
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
// ..................... GARBAGE COLLECTION ..................................

t_garbage		**gc_add(t_garbage *ptr);
void			gc_free(void);
int				gc_del(void *ptr);
void			*gc_alloc(size_t nmemb, size_t size);
// ..................... RAYCAST ............................................
# define RADIAN 0.0174532925
# define SPRITENBR 4

void			init_mlx(t_raydata *raydata);
void			starting_data_init(t_arg *arg, t_raydata *raydata);
void			ennemies_textures_init(t_raydata *raydata);
void			wall_textures_init(t_arg *arg, t_raydata *raydata);
void			player_init_position(t_arg *arg, t_raydata *raydata);
int				find_player(t_raydata *raydata, int i, double gz_x,
					double gs_y);
void			launch_game_loop(t_raydata *raydata);
int				render(t_raydata *raydata);
int				key_pressed(int keycode, t_raydata *raydata);
int				my_mlx_pixel_put(t_buffer *raydata, t_color color,
					t_int_point coord);
void			draw_line(t_raydata *raydata, t_color color,
					t_point from, t_point to);
int				ft_abs(int n);
void			clear_buffer(t_raydata *raydata);
void			draw_player(t_raydata *raydata);
void			fill_rectangle(t_raydata *raydata, t_color color,
					t_point top_left, t_point bottom_right);
void			draw_rays(t_raydata *raydata);
t_point			calc_point(t_point from, double angle, double distance);
void			clamp_player(t_raydata *raydata);
void			move_forward(t_raydata *raydata);
void			move_backward(t_raydata *raydata);
void			turn_left(t_raydata *raydata);
void			turn_right(t_raydata *raydata);
void			strafe_right(t_raydata *raydata);
void			strafe_left(t_raydata *raydata);
int				raycast(t_arg *arg);
void			grab_arg(t_raydata *raydata, t_arg *arg);
_Bool			init_alloc(t_data *data);
void			draw_sprites(t_raydata *data, t_point pos);
void			sort_sprites(t_spr	*spr, t_point pos);
void			comp_sprites(t_raydata *data, t_sprite *curr, t_point pos);
void			sprite_pxl(t_raydata *data, t_cs *cs, t_sprite *curr);
void			comp_long(t_raydata *data, t_cs *cs);
t_texture		*load_texture(void *mlx, char *path);
void			draw_minimap(t_raydata *raydata);
void			ray_comp_1(t_r *r);
void			ray_comp_2(t_raydata *data, t_r *r);
void			ray_comp_3(t_r *r);
t_r				*r_init(t_raydata *data);
void			set_color(t_color *color, t_texture *texture,
					float txtr_pos, t_r *r);
int				check_collision(t_raydata *raydata, t_point new_pos);
void			draw_horiz(t_raydata *data, t_point pos);
void			draw_menu(t_raydata *raydata);
// ..................... Ennemies AI ...................................
t_int_point		bfs(t_raydata *data, t_int_point start, t_int_point end);
void			nmi_ai(t_raydata *raydata);
int				check_nmi_collision(t_raydata *raydata);
void			data_reset(t_raydata *raydata);
void			clamp_sprites(t_raydata *raydata);
int				is_within_bounds(t_raydata *raydata, int x, int y);
t_int_point		find_direction(t_raydata *raydata, int x, int y,
					t_int_point inc);
int				find_inc(int dest, int src);
void			ray_inc_h(t_r *r);
void			ray_inc_v(t_r *r);
#endif

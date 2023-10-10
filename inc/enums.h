/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corecaps <corecaps@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:10:34 by corecaps          #+#    #+#             */
/*   Updated: 2023/10/10 16:10:39 by corecaps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_game_state {
	MENU,
	PLAYING,
	GAME_OVER,
	WIN
}t_game_state;
typedef enum e_ai_state {
	AI_IDLE,
	AI_CHASE,
	AI_FLEE
}t_ai_state;

typedef enum e_texture_index
{
	NO,
	SO,
	WE,
	EA,
	FLOOR,
	CEIL,
	SPRITE
}	t_texture_index;
#endif //CUB3D_ENUMS_H

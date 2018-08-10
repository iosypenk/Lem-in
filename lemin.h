/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 13:18:16 by iosypenk          #+#    #+#             */
/*   Updated: 2018/02/20 13:18:22 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H

# define LEMIN_H

# include "libft/libft.h"

typedef struct				s_lemin_struct
{
	char					*buff;
	int						nbr_ant;
	int						ant;
	char					*start;
	int						start_x;
	int						start_y;
	char					*end;
	int						end_x;
	int						end_y;
	int						k;
	int						s;
	int						e;
	int						room;
	int						link;
	int						start_end;
}							t_lemin_struct;

t_lemin_struct				g_s;

typedef struct				s_room
{
	struct s_room			*next;
	char					*name;
	int						room_x;
	int						room_y;
	int						pos;
	int						count_ant;
	int						nbr_ant;
	struct s_room			*link;
}							t_room;

int							id_comment(char *line);
int							id_ants(char *line);
int							id_link(char *l);

int							valid_room_line(char *l);
void						get_room(char *line, t_room **head);

int							valid_link_line(char *line);
int							get_link(char *line, t_room **head);
t_room						*link_new(void const *content);

void						move_ants(t_room *lst);

void						save_map(char *line, t_room **head);
void						ft_add_list_back(t_room **head, t_room *new);
int							ft_intlen(int nb);
void						error(void);
void						print_map(t_room *head);

#endif

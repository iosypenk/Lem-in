/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:01:19 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/15 17:01:21 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				valid_room_line(char *l)
{
	int	i;

	i = 0;
	if (l[i] && ft_isspace(l[0]))
		return (0);
	while (l[i] && ft_isprint(l[i]) && !ft_isspace(l[i]))
		i++;
	(l[i] == ' ') ? i++ : 0;
	while (l[i] && ft_isdigit(l[i]) && !ft_isspace(l[i]))
		i++;
	(l[i] == ' ') ? i++ : 0;
	while (l[i] && ft_isdigit(l[i]) && !ft_isspace(l[i]))
	{
		if (l[i + 1] == '\0')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int				valid_room_coord(t_room *new, t_room *lst)
{
	while (lst)
	{
		if (!ft_strcmp(lst->name, new->name) ||
			(lst->room_x == new->room_x && lst->room_y == new->room_y))
			return (0);
		lst = lst->next;
	}
	return (1);
}

static void		save_start_end(t_room *lst)
{
	lst->pos = -1;
	lst->count_ant = 0;
	lst->nbr_ant = 0;
	if (g_s.s == 1)
	{
		g_s.start = g_s.buff;
		lst->pos = 0;
		lst->count_ant = g_s.nbr_ant;
		g_s.s = 2;
		g_s.k = 0;
	}
	if (g_s.e == 1)
	{
		g_s.end = g_s.buff;
		lst->pos = -2;
		g_s.e = 2;
		g_s.k = 0;
	}
}

void			get_room(char *line, t_room **head)
{
	t_room		*new;
	t_room		*list;
	int			size;

	list = *head;
	size = 0;
	while (line[size] && line[size] != ' ')
		size++;
	if (!(new = malloc(sizeof(t_room))))
		return ;
	g_s.room = 1;
	g_s.buff = ft_strsub(line, 0, size);
	new->name = g_s.buff;
	save_start_end(new);
	new->room_x = ft_atoi(line + size);
	new->room_y = ft_atoi(line + size + ft_intlen(new->room_x) + 1);
	new->next = NULL;
	new->link = NULL;
	if (!valid_room_coord(new, *head))
	{
		free(new);
		error();
	}
	ft_add_list_back(head, new);
}

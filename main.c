/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 13:30:55 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/29 13:30:58 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		get_null(void)
{
	g_s.buff = NULL;
	g_s.nbr_ant = 0;
	g_s.ant = 0;
	g_s.start = NULL;
	g_s.start_x = 0;
	g_s.start_y = 0;
	g_s.end = NULL;
	g_s.end_x = 0;
	g_s.end_y = 0;
	g_s.k = 0;
	g_s.s = 0;
	g_s.e = 0;
	g_s.room = 0;
	g_s.link = 0;
	g_s.start_end = 0;
}

static int		create_queue(t_room *link, t_room **q, int level)
{
	int		res;

	res = 0;
	if (!link || !q)
		return (0);
	while (link)
	{
		if (!(*q))
		{
			if (link->link->pos != -2)
				link->link->pos = level + 1;
			*q = link_new(link->link);
		}
		else if (link->link->pos == -1)
		{
			link->link->pos = level + 1;
			ft_add_list_back(q, link_new(link->link));
		}
		if (link->link->pos == -2)
			res = 1;
		link = link->next;
	}
	return (res);
}

static int		get_path(t_room *room)
{
	t_room		*q;
	t_room		*tmp;
	int			level;
	int			res;

	q = NULL;
	if (!room)
		return (0);
	res = 0;
	level = 0;
	while (room && room->next && room->pos != 0)
		room = room->next;
	create_queue(room->link, &q, level);
	while (q)
	{
		tmp = q;
		if (create_queue(q->link->link, &q, q->link->pos) == 1)
		{
			res = 1;
		}
		q = q->next;
		free(tmp);
	}
	return (res);
}

static int		read_map(char *l, t_room **lst, t_room **map)
{
	if (l && l[0] == '#')
		if (!id_comment(l))
			return (0);
	if (l && g_s.ant == 0 && l[0] != '#' && l[0] != 'L')
	{
		(!id_ants(l)) ? error() : 0;
	}
	else if (l && l[0] != '#' && !id_link(l) && g_s.ant == 1 && l[0] != 'L')
	{
		if (valid_room_line(l))
			get_room(l, lst);
		else
			return (0);
	}
	if (l && id_link(l) && l[0] != 'L' && valid_link_line(l))
	{
		(g_s.start == NULL || g_s.end == NULL) ? error() : 0;
		if (!get_link(l, lst))
			return (0);
	}
	save_map(l, map);
	return (1);
}

int				main(void)
{
	char		*line;
	t_room		*lst;
	t_room		*map;

	line = NULL;
	lst = NULL;
	map = NULL;
	get_null();
	while (get_next_line(0, &line) > 0)
	{
		if (!read_map(line, &lst, &map))
		{
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
	if (g_s.link == 0 || g_s.room == 0 || g_s.end == NULL)
		error();
	if (!get_path(lst) && g_s.start_end != 1)
		error();
	print_map(map);
	move_ants(lst);
	return (0);
}

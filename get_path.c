/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iosypenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 14:19:00 by iosypenk          #+#    #+#             */
/*   Updated: 2018/03/16 14:19:02 by iosypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*find_the_shortest_path(t_room *room)
{
	t_room		*small;
	t_room		*head;

	small = room->link->link;
	head = room->link;
	while (head)
	{
		if (head->link->pos >= 0 && small->pos > head->link->pos)
		{
			small = head->link;
		}
		head = head->next;
	}
	return (small);
}

static void		choose_next_link(t_room *lst, t_room **next)
{
	t_room	*neighbor;

	neighbor = lst->link;
	while (neighbor)
	{
		if (neighbor->link->pos == (lst->pos - 1))
		{
			*next = neighbor->link;
			break ;
		}
		neighbor = neighbor->next;
	}
}

static void		if_need_move(t_room *prev, t_room *lst, t_room *next, int nbr)
{
	next->pos == 0 ? lst->nbr_ant = nbr : 0;
	prev->nbr_ant = lst->nbr_ant;
	lst->count_ant++;
	next->count_ant--;
	ft_printf("L%d-%s", lst->nbr_ant, lst->name);
	if (lst->count_ant != g_s.nbr_ant)
		ft_printf(" ");
}

static int		calculate_ants(t_room *lst, t_room *room, int nbr)
{
	t_room	*next;
	t_room	*prev;
	int		i;

	i = 1;
	next = room;
	prev = lst;
	while (lst)
	{
		if (lst->pos == 0)
			return (1);
		if (i == 1)
		{
			next = room;
			i = 2;
		}
		else
			choose_next_link(lst, &next);
		if (next->count_ant > 0)
			if_need_move(prev, lst, next, nbr);
		prev = lst;
		lst = next;
	}
	return (0);
}

void			move_ants(t_room *lst)
{
	int		count;
	t_room	*path;

	if (!lst)
		return ;
	count = 1;
	path = NULL;
	while (lst && lst->next && lst->pos != -2)
		lst = lst->next;
	path = find_the_shortest_path(lst);
	while (lst->count_ant != g_s.nbr_ant)
	{
		if (calculate_ants(lst, path, count) == 1)
			count++;
		ft_printf("\n");
	}
}

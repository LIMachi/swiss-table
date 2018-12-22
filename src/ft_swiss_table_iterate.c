/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_iterate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>
#include <stdio.h>

/*
** usage example (with keys and values being null terminated strings):
** char *key;
** char *value;
** size_t it = 0;
** while (ft_flat_hash_map_iterate(map, &it, (void**)&key, (void**)&value) == 1)
**   printf("'%s': '%s'\n", key, value);
*/

#ifdef __SSE2__

int	ft_swiss_table_iterate(t_swt_map *map,
		size_t *it,
		SWT_KEY_TYPE *key_retriever,
		SWT_VALUE_TYPE *value_retriever)
{
	t_swt_group	g;
	int			i;
	int			match;

	while (*it < map->nb_groups << 4)
	{
		g = map->groups[*it >> 4];
		match = _mm_movemask_epi8(g.control);
		i = *it & 0xF;
		while (i < 0x10 && match & (1 << i))
			++i;
		if (i != 0x10)
		{
			*it = (*it & ~0xF) | i;
			*key_retriever = g.key[i];
			*value_retriever = map->values[*it];
			++*it;
			return (1);
		}
		*it = (*it & ~0xF) + 0x10;
	}
	return (*it == map->nb_groups << 4 ? 0 : -1);
}

#else

int	ft_swiss_table_iterate(t_swt_map *map,
		size_t *it,
		SWT_KEY_TYPE *key_retriever,
		SWT_VALUE_TYPE *value_retriever)
{
	t_swt_group	g;
	int			i;

	while (*it < map->nb_groups << 4)
	{
		g = map->groups[*it >> 4];
		i = *it & 0xF;
		while (i < 0x10 && g.control[i] & 1 << 7)
			++i;
		if (i != 0x10)
		{
			*it = (*it & ~0xF) | i;
			*key_retriever = g.key[i];
			*value_retriever = map->values[*it];
			++*it;
			return (1);
		}
		*it = (*it & ~0xF) + 0x10;
	}
	return (*it == map->nb_groups << 4 ? 0 : -1);
}

#endif
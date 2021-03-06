/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_expand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>

static inline t_swt_map	i_tmp_map(t_swt_map *map, int factor)
{
	t_swt_map		tmp;

	tmp = (t_swt_map){.pair_count = 0, .nb_groups = map->nb_groups * factor,
		.hashfun = map->hashfun, .cmpfun = map->cmpfun,
		.groups = malloc(sizeof(t_swt_group) * map->nb_groups * factor),
		.values = malloc(sizeof(SWT_VALUE_TYPE) * map->nb_groups * factor)};
	if (tmp.groups == NULL || tmp.values == NULL)
	{
		free(tmp.groups);
		tmp.groups = NULL;
		free(tmp.values);
		tmp.values = NULL;
	}
	return (tmp);
}

#ifdef __SSE2__

int						ft_swiss_table_expand(t_swt_map *map, int factor)
{
	t_swt_map		tmp;
	size_t			i;
	int				match;
	int				j;
	t_swt_group		g;

	if ((tmp = i_tmp_map(map, factor)).groups == NULL)
		return (-1);
	i = -1;
	while (++i < map->nb_groups)
	{
		g = map->groups[i];
		match = _mm_movemask_epi8(g.control);
		j = -1;
		while (++j < SWT_CONTROL_SIZE)
			if (!(match & (1 << i)))
				if (__builtin_expect(
					ft_swiss_table_insert(&tmp, g.key[j],
						map->values[i * SWT_CONTROL_SIZE + j]), 0))
					return (-1);
	}
	ft_swiss_table_destroy(map);
	*map = tmp;
	return (0);
}

#else

int						ft_swiss_table_expand(t_swt_map *map, int factor)
{
	t_swt_map		tmp;
	size_t			i;
	int				j;
	t_swt_group		g;

	if ((tmp = i_tmp_map(map, factor)).groups == NULL)
		return (-1);
	i = -1;
	while (++i < map->nb_groups)
	{
		g = map->groups[i];
		j = -1;
		while (++j < SWT_CONTROL_SIZE)
			if (!(g.control[j] & (1 << 7)))
				if (__builtin_expect(
					ft_swiss_table_insert(&tmp, g.key[j],
						map->values[i * SWT_CONTROL_SIZE + j]), 0))
					return (-1);
	}
	ft_swiss_table_destroy(map);
	*map = tmp;
	return (0);
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>

#ifdef __SSE2__

int					ft_swiss_table_insert(t_swt_map *map,
										SWT_KEY_TYPE key,
										SWT_VALUE_TYPE value)
{
	t_swt_hash	hash;
	size_t		gi;
	int			i;
	int			match;

	if (map->pair_count >= SWT_LOAD_FACTOR * map->nb_groups * SWT_CONTROL_SIZE)
		if (ft_swiss_table_expand(map, SWT_EXPAND_FACTOR))
			return (-1);
	hash.s = map->hashfun(key, map->nb_groups * SWT_CONTROL_SIZE);
	gi = hash.h.position % map->nb_groups;
	while (1)
	{
		if ((match = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_set1_epi8(
				(char)SWT_EMPTY), map->groups[gi].control))) && (i = -1))
			while (++i < SWT_CONTROL_SIZE)
				if (match & (1 << i))
				{
					((char *)&map->groups[gi].control)[i] = (char)hash.h.meta;
					map->groups[gi].key[i] = key;
					map->values[gi * SWT_CONTROL_SIZE + i] = value;
					++map->pair_count;
					return (0);
				}
		gi = (gi + 1) % map->nb_groups;
	}
}

#else

static inline int	i_get_match_mask(unsigned char byte, t_swt_i128 control)
{
	int	i;
	int	out;

	out = 0;
	i = SWT_CONTROL_SIZE;
	while (i--)
		if (control[i] == byte)
			out |= 1 << i;
	return (out);
}

int					ft_swiss_table_insert(t_swt_map *map,
										SWT_KEY_TYPE key,
										SWT_VALUE_TYPE value)
{
	t_swt_hash	hash;
	size_t		gi;
	int			i;
	int			match;

	if (map->pair_count >= SWT_LOAD_FACTOR * map->nb_groups * SWT_CONTROL_SIZE)
		if (ft_swiss_table_expand(map, SWT_EXPAND_FACTOR))
			return (-1);
	hash.s = map->hashfun(key, map->nb_groups * SWT_CONTROL_SIZE);
	gi = hash.h.position % map->nb_groups;
	while (1)
	{
		if ((match = i_get_match_mask(SWT_EMPTY, map->groups[gi].control))
				&& (i = -1))
			while (++i < SWT_CONTROL_SIZE)
				if (match & (1 << i))
				{
					((char *)&map->groups[gi].control)[i] = (char)hash.h.meta;
					map->groups[gi].key[i] = key;
					map->values[gi * SWT_CONTROL_SIZE + i] = value;
					++map->pair_count;
					return (0);
				}
		gi = (gi + 1) % map->nb_groups;
	}
}

#endif

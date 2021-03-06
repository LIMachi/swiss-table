/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_delete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>

#ifdef __SSE2__

static inline SWT_VALUE_TYPE	i_ft_swiss_table_delete(t_swt_map *map,
														int control,
														int i,
														size_t gi)
{
	map->groups[gi].control &= ~(SWTI1280XFF << (i << 8));
	if (__builtin_expect(!control, 1))
	{
		map->groups[gi].control |= SWTI128EMPTY << (i << 8);
		--map->pair_count;
	}
	else
		map->groups[gi].control |= SWTI128DELETED << (i << 8);
	return (map->values[gi * SWT_CONTROL_SIZE + i]);
}

SWT_VALUE_TYPE					ft_swiss_table_delete(t_swt_map *map,
													SWT_KEY_TYPE key,
												SWT_VALUE_TYPE no_match_return)
{
	t_swt_hash		hash;
	size_t			gi;
	int				i;
	t_swt_group		g;
	int				match;

	hash.s = map->hashfun(key, map->nb_groups * SWT_CONTROL_SIZE);
	gi = hash.h.position % map->nb_groups;
	while (1)
	{
		i = -1;
		g = map->groups[gi];
		match = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_set1_epi8(
				hash.h.meta), g.control));
		while (++i < SWT_CONTROL_SIZE)
			if (match & (1 << i)
					&& __builtin_expect(!map->cmpfun(g.key[i], key), 1))
				return (i_ft_swiss_table_delete(map, !_mm_movemask_epi8(
						_mm_cmpeq_epi8(_mm_set1_epi8((char)SWT_EMPTY),
						g.control)), i, gi));
				if (__builtin_expect(match != 0b1111111111111111, 1))
			return (no_match_return);
		gi = (gi + 1) % map->nb_groups;
	}
}

#else

static inline int				i_get_match_mask(unsigned char byte,
												t_swt_i128 control)
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

static inline SWT_VALUE_TYPE	i_ft_swiss_table_delete(t_swt_map *map,
														int control,
														int i,
														size_t gi)
{
	if (__builtin_expect(!control, 1))
	{
		map->groups[gi].control[i] = SWT_EMPTY;
		--map->pair_count;
	}
	else
		map->groups[gi].control[i] = SWT_DELETED;
	return (map->values[gi * SWT_CONTROL_SIZE + i]);
}

SWT_VALUE_TYPE					ft_swiss_table_delete(t_swt_map *map,
													SWT_KEY_TYPE key,
												SWT_VALUE_TYPE no_match_return)
{
	t_swt_hash		hash;
	size_t			gi;
	int				i;
	t_swt_group		g;
	int				match;

	hash.s = map->hashfun(key, map->nb_groups * SWT_CONTROL_SIZE);
	gi = hash.h.position % map->nb_groups;
	while (1)
	{
		i = -1;
		g = map->groups[gi];
		match = i_get_match_mask(hash.h.meta, g.control);
		while (++i < SWT_CONTROL_SIZE)
			if (match & (1 << i)
					&& __builtin_expect(!map->cmpfun(g.key[i], key), 1))
				return (i_ft_swiss_table_delete(map,
					!i_get_match_mask(SWT_EMPTY, g.control), i, gi));
				if (__builtin_expect(match != 0b1111111111111111, 1))
			return (no_match_return);
		gi = (gi + 1) % map->nb_groups;
	}
}

#endif

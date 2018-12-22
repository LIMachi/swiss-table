/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_clear.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>

/*
** iterate over the map and fill all controls with FHM_EMPTY and set
** map->pair_count to 0, effectively recycling the table
*/

int	ft_swiss_table_clear(t_swt_map *map)
{
	(void)map;
	/*
	size_t		i;
	int			mmatch;
	__m128i		control;
	__m128i		match;

	i = -1;
	while (++i < map->nb_groups)
	{
		control = map->groups[i].control;
		match = _mm_cmpeq_epi8(_mm_set1_epi8((char)FHM_DELETED), control);
		control &= ~match;
		control |= match & _mm_set1_epi8((char)FHM_EMPTY);
		map->groups[i].control = control;
		mmatch = _mm_movemask_epi8(match);
		while (mmatch)
		{
			if (mmatch & 1)
				--map->pair_count;
			mmatch >>= 1;
		}
	}*/
	return (0);
}

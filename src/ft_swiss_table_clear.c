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
** iterate over the map and fill all controls with SWT_EMPTY and set
** map->pair_count to 0, effectively recycling the table
** return the available size
*/

#ifdef __SSE2__

int	ft_swiss_table_clear(t_swt_map *map)
{
	size_t	gi;

	gi = map->nb_groups;
	while (gi--)
		map->groups[gi].control = _mm_set1_epi8((char)SWT_EMPTY);
	map->pair_count = 0;
	return (map->nb_groups * SWT_CONTROL_SIZE);
}

#else

int	ft_swiss_table_clear(t_swt_map *map)
{
	size_t	gi;
	size_t	i;

	gi = map->nb_groups;
	while (gi--)
	{
		i = SWT_CONTROL_SIZE;
		while (i--)
			map->groups[gi].control[i] = SWT_EMPTY;
	}
	map->pair_count = 0;
	return (map->nb_groups * SWT_CONTROL_SIZE);
}

#endif

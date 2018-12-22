/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table_create.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>

#ifdef __SSE2__

t_swt_map	ft_swiss_table_create(t_swt_hashfun hash,
											t_swt_cmpfun cmp)
{
	t_swt_map	out;
	size_t		i;

	out = (t_swt_map){.pair_count = 0, .nb_groups = SWT_BASE_SIZE,
		.hashfun = hash, .cmpfun = cmp,
		.groups = malloc(sizeof(t_swt_group) * SWT_BASE_SIZE),
		.values = malloc(sizeof(void*) * SWT_BASE_SIZE)};
	if (out.groups == NULL || out.values == NULL)
	{
		free(out.groups);
		free(out.values);
		out = (t_swt_map){.groups = NULL, .nb_groups = 0, .cmpfun = NULL,
			.hashfun = NULL, .pair_count = 0};
		return (out);
	}
	i = out.nb_groups;
	while (i--)
		out.groups[i].control = _mm_set1_epi8((char)SWT_EMPTY);
	return (out);
}

#else

t_swt_map	ft_swiss_table_create(t_swt_hashfun hash,
											t_swt_cmpfun cmp)
{
	t_swt_map	out;
	size_t		i;
	size_t		j;

	out = (t_swt_map){.pair_count = 0, .nb_groups = SWT_BASE_SIZE,
		.hashfun = hash, .cmpfun = cmp,
		.groups = malloc(sizeof(t_swt_group) * SWT_BASE_SIZE),
		.values = malloc(sizeof(void*) * SWT_BASE_SIZE)};
	if (out.groups == NULL || out.values == NULL)
	{
		free(out.groups);
		free(out.values);
		out = (t_swt_map){.groups = NULL, .nb_groups = 0, .cmpfun = NULL,
			.hashfun = NULL, .pair_count = 0};
		return (out);
	}
	i = out.nb_groups;
	while (i-- && (j = SWT_BASE_SIZE))
		while (j--)
			out.groups[i].control[j] = SWT_EMPTY;
	return (out);
}

#endif
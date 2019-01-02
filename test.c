/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_swiss_table.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	t_swt_map	map;
	size_t		it;
	char		*key;
	char		*data;

	map = ft_swiss_table_create((t_swt_hashfun)ft_basic_hash,
		(t_swt_cmpfun)strcmp);
	ft_swiss_table_insert(&map, "test", "1");
	ft_swiss_table_insert(&map, "sak", "2");
	ft_swiss_table_insert(&map, "cool", "3");
	data = ft_swiss_table_find(&map, "sak");
	printf("data: '%s'\n", data);
	printf("iterate:\n");
	it = 0;
	while (ft_swiss_table_iterate(&map, &it, (void**)&key,
			(void**)&data) == 1)
		printf("%zu '%s': '%s'\n", it, key, data);
	ft_swiss_table_delete(&map, "cool");
	printf("pair_count: %zu\n", map.pair_count);
	it = 0;
	while (ft_swiss_table_iterate(&map, &it, (void**)&key,
									(void**)&data) == 1)
		printf("%zu '%s': '%s'\n", it, key, data);
	ft_swiss_table_destroy(&map);
	return (0);
}

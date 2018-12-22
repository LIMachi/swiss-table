/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
** uses FNV-1a hash:
** https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
*/

size_t	ft_basic_hash(char *str, size_t tab_size)
{
	size_t	hash;
	size_t	prime;

	(void)tab_size;
	hash = sizeof(size_t) == 8 ? 0xcbf29ce484222325ull : 0x811c9dc5ull;
	prime = sizeof(size_t) == 8 ? 1099511628211ull : 16777619ull;
	while (*str != '\0')
	{
		hash ^= *str++;
		hash *= prime;
	}
	return (hash);
}

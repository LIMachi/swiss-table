/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swiss_table.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** addapted from: https://www.youtube.com/watch?v=ncHmEUmJZf4
*/

#ifndef FT_SWISS_TABLE_H
# define FT_SWISS_TABLE_H

# include <stdlib.h>
# include <stddef.h>

# ifndef SWT_KEY_TYPE
#  define SWT_KEY_TYPE void*
# endif

# ifndef SWT_VALUE_TYPE
#  define SWT_VALUE_TYPE void*
# endif

/*
** note: changing the following defines will produce undefined behavior
*/

# define SWT_BASE_CONTROL_SIZE (16)
# define SWT_BASE_GROUP_SIZE (16)
# define SWT_BASE_VALUE_SIZE (SWT_BASE_CONTROL_SIZE * SWT_BASE_GROUP_SIZE)
# define SWT_LOAD_FACTOR (0.75)
# define SWT_EXPAND_FACTOR (2)

# ifdef __SSE2__
#  include <emmintrin.h>
#  include <immintrin.h>

#  define SWTI128 __m128i

#  define SWTI1280XFF _mm_cvtsi32_si128(0xFF)
#  define SWTI128DELETED _mm_cvtsi32_si128(SWT_DELETED)
#  define SWTI128EMPTY _mm_cvtsi32_si128(SWT_EMPTY)

# else
#  pragma message "Missing SSE2 processor instructions"
#  pragma message "Using slower functions instead"

typedef char		t_swt_i128[SWT_BASE_CONTROL_SIZE];

#  define SWTI128 t_swt_i128

# endif

typedef enum		e_swt_control
{
	SWT_EMPTY = 0b10000000,
	SWT_DELETED = 0b11111111,
	SWT_FULL_MASK = 0b01111111
}					t_swt_control;

/*
** __m128i control -> t_swt_control(char)[16]
*/

typedef struct		s_swt_group
{
	SWTI128			control;
	SWT_KEY_TYPE	key[SWT_BASE_CONTROL_SIZE];
}					t_swt_group;

struct				s_swt_hash
{
	size_t			meta : 7;
	size_t			position : (__SIZEOF_SIZE_T__ << 3) - 7;
};

typedef union		u_swt_hash
{
	struct s_swt_hash	h;
	size_t				s;
}					t_swt_hash;

typedef int			(*t_swt_cmpfun)(void *, void *);

typedef size_t		(*t_swt_hashfun)(void *, size_t);

typedef struct		s_swt_map
{
	size_t			nb_groups;
	size_t			pair_count;
	t_swt_cmpfun	cmpfun;
	t_swt_hashfun	hashfun;
	t_swt_group		*groups;
	SWT_VALUE_TYPE	*values;
}					t_swt_map;

t_swt_map			ft_swiss_table_create(t_swt_hashfun hash,
											t_swt_cmpfun cmp);

int					ft_swiss_table_insert(t_swt_map *map,
											SWT_KEY_TYPE key,
											SWT_VALUE_TYPE value);

int					ft_swiss_table_expand(t_swt_map *map, int factor);

SWT_VALUE_TYPE		ft_swiss_table_find(t_swt_map *map, SWT_KEY_TYPE key);

SWT_VALUE_TYPE		ft_swiss_table_delete(t_swt_map *map, SWT_KEY_TYPE key);

void				ft_swiss_table_destroy(t_swt_map *map);

size_t				ft_basic_hash(char *str, size_t tab_size);

int					ft_swiss_table_iterate(t_swt_map *map,
											size_t *it,
											SWT_KEY_TYPE *key_retriever,
											SWT_VALUE_TYPE *value_retriever);

int					ft_swiss_table_clear(t_swt_map *map);

#endif

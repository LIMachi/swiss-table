include ../Makefiles/default_var.mk

NAME := swiss_table.a

SRCS := src/ft_swiss_table_create.c  \
        src/ft_swiss_table_destroy.c \
        src/ft_swiss_table_insert.c  \
        src/ft_swiss_table_find.c    \
        src/ft_swiss_table_delete.c  \
        src/ft_swiss_table_iterate.c \
        src/ft_swiss_table_clear.c   \
        src/ft_swiss_table_expand.c  \
        src/ft_basic_hash.c

include ../Makefiles/lib.mk
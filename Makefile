NAME := swiss_table.a

ARG_TEST +=

OBJ_DIR := .obj

TEST_SRCS := test.c

SRCS := src/ft_swiss_table_create.c  \
        src/ft_swiss_table_destroy.c \
        src/ft_swiss_table_insert.c  \
        src/ft_swiss_table_find.c    \
        src/ft_swiss_table_delete.c  \
        src/ft_swiss_table_iterate.c \
        src/ft_swiss_table_clear.c   \
        src/ft_swiss_table_expand.c  \
        src/ft_basic_hash.c

CFLAGS += -Iinc
LDLIBS +=
PRE_TEST :=
CLIB :=

include ../Makefiles/lib.mk
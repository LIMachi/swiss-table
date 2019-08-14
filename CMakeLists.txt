cmake_minimum_required(VERSION 3.13)
project(swiss_table.a)
include_directories(inc /Users/hmartzol/.brew/include)
add_library(swiss_table.a ./test.c  src/ft_basic_hash.c src/ft_swiss_table_clear.c src/ft_swiss_table_create.c src/ft_swiss_table_delete.c src/ft_swiss_table_destroy.c src/ft_swiss_table_expand.c src/ft_swiss_table_find.c src/ft_swiss_table_insert.c src/ft_swiss_table_iterate.c)

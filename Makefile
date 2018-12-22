NAME := ft_swiss_table.a

OBJ_DIR := .obj

_OBJS := ft_swiss_table_create.o  \
         ft_swiss_table_destroy.o \
         ft_swiss_table_insert.o  \
         ft_swiss_table_find.o    \
         ft_swiss_table_delete.o  \
         ft_swiss_table_iterate.o \
         ft_swiss_table_clear.o   \
         ft_swiss_table_expand.o  \
         ft_basic_hash.o

OBJS := $(addprefix $(OBJ_DIR)/, $(_OBJS))

TEST_OBJ := $(OBJ_DIR)/test.o

CFLAGS += -Iinc

ifneq ($(DEBUG), )
CFLAGS += -g
endif

ifneq ($(SANITIZE), )
CFLAGS += -g -fsanitize=address
LDLIBS += -fsanitize=address
endif

#if neither DEBUG nor SANITIZE is set
ifneq ($(DEBUG), )
ifneq ($(SANITIZE), )
CFLAGS += -O3
endif
endif

ifneq ($(SWT_KEY_TYPE), )
CFLAGS += -DSWT_KEY_TYPE=$(SWT_KEY_TYPE)
endif

ifneq ($(SWT_VALUE_TYPE), )
CFLAGS += -DSWT_VALUE_TYPE=$(SWT_VALUE_TYPE)
endif

all: $(NAME)

test: test.bin
	./test.bin $(TEST_ARG)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

test.bin: $(TEST_OBJ) $(NAME)
	$(CC) $(LDFLAGS) $< $(LDLIBS) $(NAME) -o $@

$(OBJ_DIR):
	mkdir $@

$(TEST_OBJ): test.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJ_DIR)
	$(RM) -f test.bin

fclean: clean
	$(RM) -rf $(NAME)

re: | fclean all

.PHONY: all clean fclean re test
NAME = pipex
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

LIBFT = lib/libft
UNITY = unity

HDRS = -I./include -I $(LIBFT)/include -I $(UNITY)/src/unity.h
LIBS = $(LIBFT)/build/libft.a
SRCS = child.c error.c path.c utils.c tokenize.c
TEST_SRCS = test.c
OBJS = $(SRCS:%.c=%.o)
TEST_OBJS = $(TEST_SRCS:%.c=%.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

unity:
	@cmake $(UNITY) -B $(UNITY)/build && make -C $(UNITY)/build

test: libft $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(UNITY)/libunity.a $(LIBS) $(HDRS) -o run_test
	@echo "[pipex] Running test..."
	@./run_test

%.o : %.c
	@echo "\033[32m[pipex] Compiling $< into $@\033[0m"
	@$(CC) $(CCFLAGS) -o $@ -c $< $(HDRS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HDRS) -o $(NAME) -fsanitize=address
	@echo "[pipex] Built target pipex"

clean:
	@rm -rf $(OBJS) $(TEST_OBJS)
	@make clean -C $(LIBFT)
	@echo "[pipex] Object files cleaned."

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/build
	@rm -rf $(UNITY)/build
	@rm -rf run_test
	@echo "[pipex] Everything deleted."

re: fclean all
	@echo "[pipex] Everything rebuilt."

.PHONY: all clean fclean re libft




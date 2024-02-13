NAME = pipex
CFLAGS = -Wall -Wextra -Werror -std=c99 -fsanitize=address -g

LIBFT = lib/libft
UNITY = test/unity/src/unity.c

HDRS = -I./include -I $(LIBFT)/includes -I $(UNITY)/src
LIBS = $(LIBFT)/build/libft.a
SRCS = path.c 
TEST_SRCS = test_path.c
OBJS = $(SRCS:%.c=%.o)
TEST_OBJS = $(TEST_SRCS:%.c=%.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

test: libft $(TEST_OBJS) $(OBJS)
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) $(UNITY) $(LIBS) $(HDRS) -o run_test
	@echo "[pipex] Running test..."
	@./run_test

%.o : %.c
	@echo "\033[32m[pipex] Compiling $< into $@\033[0m"
	@$(CC) $(CCFLAGS) -o $@ -c $< $(HDRS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HDRS) -o $(NAME) -fsanitize=address
	@echo "[pipex] Built target pipex"

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@echo "[pipex] Object files cleaned."

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/build
	@echo "[pipex] Everything deleted."

re: fclean all
	@echo "[pipex] Everything rebuilt."

.PHONY: all clean fclean re libft




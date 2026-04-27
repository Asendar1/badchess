NAME = badchess

SRCS = main.cpp \
		srcs/board.cpp

CXX = g++ -Wall -Werror -Wextra -Iinclude

OBJS_DIR = obj
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CXX) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

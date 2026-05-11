NAME = badchess

SRCS = main.cpp \
		srcs/board.cpp srcs/piece.cpp srcs/undo.cpp

# don't forget the -Werror
CXX = g++ -Wall -Wextra -Werror -Iinclude -g -fsanitize=address

LIBS = -lsfml-graphics -lsfml-window -lsfml-system


OBJS_DIR = obj
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LIBS)

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

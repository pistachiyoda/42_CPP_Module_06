NAME = serialization
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp Serializer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ 
clean:
	$(RM) -f $(OBJS)
fclean:
	$(RM) -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
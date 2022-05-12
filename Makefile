NAME			= Easy_find

DIR				= srcs
HEADERS_DIR		= includes/
INCLUDES		= -I$(HEADERS_DIR)
SRCS			= $(shell find $(DIR) -name *.cpp)
OBJECTS			= $(patsubst %.cpp, %.o, $(SRCS))
D_FILES			= ${patsubst %.cpp, %.d, ${SRCS}}

CC		= c++
CFLAGS	= -Werror -Wall -Wextra -std=c++98

all	: 	$(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@ -MMD

clean:
		@rm -f $(OBJECTS) $(D_FILES)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all

include $(wildcard $(D_FILES))

.PHONY:	all clean fclean re

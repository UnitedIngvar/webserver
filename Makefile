NAME			= Webserver

DIR				= srcs
HEADERS_DIR		= $(shell find $(DIR) -type d -name "includes")
INCLUDES		= -I$(HEADERS_DIR)
SRCS			= $(shell find $(DIR) -name *.cpp)
OBJECTS			= $(patsubst %.cpp, %.o, $(SRCS))
D_FILES			= ${patsubst %.cpp, %.d, ${SRCS}}

CC		= c++
CFLAGS	= -std=c++98 #-Werror -Wall -Wextra

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

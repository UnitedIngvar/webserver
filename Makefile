NAME			= Webserver

DIR				= srcs
HEADERS_DIR		= $(shell find $(DIR) -type d -name "includes")
INCLUDES		= $(patsubst %, -I%, $(HEADERS_DIR))
SRCS			= $(shell find $(DIR) -name *.cpp)
OBJECTS			= $(patsubst %.cpp, %.o, $(SRCS))
D_FILES			= ${patsubst %.cpp, %.d, ${SRCS}}

TEST_DIR		= tests
CC		= c++
CFLAGS	= -std=c++98 -pthread -g #-Werror -Wall -Wextra

all: 	$(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@ -MMD

clean:
		@rm -f $(OBJECTS) $(D_FILES)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all

test:	tests/Makefile
	$(MAKE) -C $(TEST_DIR)
	$(MAKE) -C $(TEST_DIR) fclean

include $(wildcard $(D_FILES))

.PHONY:	all clean fclean re

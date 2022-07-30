NAME			= test_executable

# PROJECT UNDER TEST FILES
PROJ_DIR		= ../srcs
PROJ_HEADERS	= $(shell find $(PROJ_DIR) -type d -name "includes")
PROJ_INCLUDES	= $(patsubst %, -I%, $(PROJ_HEADERS))
PROJ_SRCS		= $(shell find $(PROJ_DIR) -name *.cpp)
PROJ_OBJECTS	= $(patsubst %.cpp, %.o, $(PROJ_SRCS))
PROJ_D_FILES	= ${patsubst %.cpp, %.d, ${PROJ_SRCS}}

# TEST FILES
TEST_DIR		= project_tests
TEST_HEADERS	= $(shell find $(TEST_DIR) -type d -name "includes")
TEST_INCLUDES	= $(patsubst %, -I%, $(TEST_HEADERS))
TEST_SRCS		= $(shell find $(TEST_DIR) -name *.cpp)
TEST_OBJS		= $(patsubst %.cpp, %.o, $(TEST_SRCS))
TEST_D_FILES	= ${patsubst %.cpp, %.d, ${TEST_SRCS}}

# DOCTEST FILES
DOC_DIR			= doctest_files/doctest
DOC_INCLUDES	= -I$(DOC_DIR)

# ASSEMBLE
DIR				= project_tests
INCLUDES		:= $(PROJ_INCLUDES) $(TEST_INCLUDES) $(DOC_INCLUDES)
SRCS			:= $(PROJ_SRCS) $(TEST_SRCS)
SRCS			:= $(filter-out $(PROJ_DIR)/main.cpp, $(SRCS))
OBJECTS			:= $(PROJ_OBJECTS) $(TEST_OBJS)
OBJECTS			:= $(filter-out $(PROJ_DIR)/main.o, $(OBJECTS))
D_FILES			= ${patsubst %.cpp, %.d, ${SRCS}}

CC		= g++
CFLAGS	= -std=c++11 -pthread #doctest is c++11 or older compilant

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

include $(wildcard $(D_FILES))

.PHONY:	all clean fclean re

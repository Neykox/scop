#-----------------------------------------------#
################### PATHS #######################
#-----------------------------------------------#
HEAD_PATH	=	./include/
SRCS_PATH	=	./src/
OBJ_PATH	=	./objects/

#-----------------------------------------------#
################## SOURCES ######################
#-----------------------------------------------#
SRCS_NAME =		main.cpp glad.cpp
OBJ_NAME = ${SRCS_NAME:.cpp=.o}

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

#-----------------------------------------------#
################## HEADERS ######################
#-----------------------------------------------#
HEADERS = include/scop.hpp

#-----------------------------------------------#
################### OTHER #######################
#-----------------------------------------------#

NAME = scop

CC = g++

FLAGS = #-Wall -Wextra -Werror -std=c++17 #-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

#-----------------------------------------------#
################### RULES #######################
#-----------------------------------------------#

all : $(NAME)

$(NAME) : $(GLAD_BS) $(OBJ)
	$(CC) $(FLAGS) $^ -o $(NAME) -lglfw -lGL -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

$(GLAD_BS) :
	gcc -c -std=c99 -o glad.o src/glad.c

$(OBJ_PATH):
	mkdir -p $@

$(OBJ_PATH)%.o : $(SRCS_PATH)%.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ) : Makefile $(HEADERS) | $(OBJ_PATH)

clean :
	rm -rf $(OBJ_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re diff main


# $@ : produit (ou but) de la règle
# $< : nom de la première dépendance (ou source)
# $? : toutes les dépendances plus récentes que le but
# $^ : toutes les dépendances
# $+ : idem mais chaque dépendance apparait autant de fois qu'elle est cité et l'ordre d'apparition est conservé.

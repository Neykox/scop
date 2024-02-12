#-----------------------------------------------#
################### PATHS #######################
#-----------------------------------------------#
HEAD_PATH	=	./#includes/
SRCS_PATH	=	./#scr/
OBJ_PATH	=	./objects/

#-----------------------------------------------#
################## SOURCES ######################
#-----------------------------------------------#
SRCS_NAME =		main.cpp
OBJ_NAME = ${SRCS_NAME:.cpp=.o}

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

#-----------------------------------------------#
################## HEADERS ######################
#-----------------------------------------------#
HEADERS =

#-----------------------------------------------#
################### OTHER #######################
#-----------------------------------------------#

NAME = scop

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++17 #-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

#-----------------------------------------------#
################### RULES #######################
#-----------------------------------------------#

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $^ -o $(NAME) -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

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

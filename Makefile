SRC	=	src/main.cpp \
		src/core/engineCore.cpp \
		src/core/loadObject.cpp \
		src/core/light.cpp \
		src/object/object.cpp \
		src/math/matrix.cpp \
		src/math/normalization.cpp \
		src/math/vector.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	3DEngine

CPPFLAGS	=	-std=c++20

SFMLFLAGS	=	-L/opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-system -lsfml-window

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(SFMLFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f test

re: fclean all

.PHONY: all clean fclean re

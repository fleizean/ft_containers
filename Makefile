NAME = ft_containers
GXX = c++
GXXFLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic -fsanitize=address
INCLUDES = -I$(HEADER_DIR)

HEADER_DIR = ./includes/
HEADER_LIST =	iterator_base.hpp \
				random_access_iterator.hpp \
				reverse_iterator.hpp \
				type_traits.hpp \
				algorithm.hpp \
				utility.hpp \
				RBTree.hpp \
				vector.hpp \
				stack.hpp \
				map.hpp \
				set.hpp \
				container.hpp

HEADERS = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

SOURCE_DIR = ./sources/
SOURCE_LIST = main.cpp
SOURCES = $(addprefix $(SOURCE_DIR), $(SOURCE_LIST))

OBJECT_DIR = ./objects/
OBJECTS_LIST = $(patsubst %.cpp, %.o, $(SOURCE_LIST))
OBJECTS = $(addprefix $(OBJECT_DIR), $(OBJECTS_LIST))

RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJECT_DIR) $(OBJECTS)
	@$(GXX) $(GXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "\n$(BLUE)$(NAME): object files created$(RESET)"
	@echo "$(BLUE)$(NAME): $(NAME) created$(RESET)"

std:
	@$(MAKE) fclean
	@make CXXFLAGS="-Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address -D STD_MODE=1" all

$(OBJECT_DIR):
	@mkdir -p $(OBJECT_DIR)
	@echo "$(BLUE)$(NAME): $(OBJECT_DIR) created$(RESET)"

$(OBJECT_DIR)%.o : $(SOURCE_DIR)%.cpp $(HEADERS)
	@$(GXX) $(GXXFLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(BLUE).$(RESET)\c"

clean:
	@rm -rf $(OBJECT_DIR)
	@echo "$(RED)$(NAME): $(OBJECT_DIR) deleted$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME): $(NAME) deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re std
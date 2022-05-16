FT_MACRO = -D LIB=ft
STD_MACRO = -D LIB=std
NAMEFT = ft_containers.a
NAMESTD = std_containers.a

SRCFOL = srcs

SRC = \
	main.cpp \
	stack_test.cpp \
	map_test.cpp \
	vector_test.cpp \

FOLFT = obj_ft
FOLSTD = obj_std

OBJFT = $(addprefix $(FOLFT)/, $(SRC:.cpp=.o))
OBJSTD = $(addprefix $(FOLSTD)/, $(SRC:.cpp=.o))

CC = c++

CFLAGS = -Werror -Wextra -Wall -std=c++98

RM = rm -rf
HEADER = \
		 -I containers/ \
		 -I iterators/ \
		 -I utils/ \
		 -I includes/ \

all: creat_ft $(NAMEFT) creat_std $(NAMESTD)

creat_ft:
	@mkdir -p $(FOLFT)

creat_std:
	@mkdir -p $(FOLSTD)

$(NAMEFT): $(OBJFT)
	$(CC) $(CFLAGS) $(FT_MACRO) $(HEADER) $(OBJFT) -o $@

$(NAMESTD): $(OBJSTD) 
	$(CC) $(CFLAGS) $(STD_MACRO) $(HEADER) $(OBJSTD) -o $@

$(FOLFT)/%.o: $(SRCFOL)/%.cpp
	$(CC) $(CFLAGS) $(FT_MACRO) $(HEADER) -c $< -o $@

$(FOLSTD)/%.o: $(SRCFOL)/%.cpp
	$(CC) $(CFLAGS) $(STD_MACRO) $(HEADER) -c $< -o $@
	
compare:
	mkdir -p output_folder/
	./$(NAMEFT)  > "output_folder/ft_output.txt"
	./$(NAMESTD) > "output_folder/std_output.txt"
	@diff output_folder/ft_output.txt output_folder/std_output.txt > "output_folder/difference.txt"

clean:
	$(RM) $(FOLFT) $(FOLSTD)
	$(RM) output_folder

fclean: clean
	$(RM) $(NAMEFT) $(NAMESTD)

re: fclean all

.PHONY: all fclean clean re creat_ft creat_std compare
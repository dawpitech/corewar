##
## EPITECH PROJECT, 2023
## Minishell
## File description:
## Main Makefile of the project
##

CC	:=	gcc -std=gnu11

CFLAGS	=	-W
CFLAGS	+=	-Wall
CFLAGS	+=	-Wextra
CFLAGS	+=	-Wundef
CFLAGS	+=	-Wshadow
CFLAGS	+=	-Wunreachable-code
CFLAGS	+=	-Wmissing-prototypes
CFLAGS	+=	-Wno-unknown-pragmas
CFLAGS	+=	-Wno-dangling-pointer
CFLAGS	+=	-pedantic
CFLAGS	+=	-I./include/
CFLAGS	+=	-MMD -MP

T_CFLAGS	:= $(CFLAGS)
T_CFLAGS	+=	-g3
T_CFLAGS	+=	-lcriterion
T_CFLAGS	+=	--coverage

LIBS_FLAGS	=	-L./lib/ -lmy

BDIR	=	.build
T_BDIR	=	.buildTests

NAME	=	corewar
T_NAME	=	unit_tests

SRC	=	./sources/corewar.c
SRC	+=	./sources/op.c
SRC	+=	./sources/arguments.c
SRC	+=	./sources/arena.c
SRC	+=	./sources/utils/reader.c
SRC	+=	./sources/utils/writer.c
SRC	+=	./sources/utils/memory.c
SRC	+=	./sources/execute/executor.c
SRC	+=	./sources/execute/decoder.c
SRC	+=	./sources/execute/instructions/live.c
SRC	+=	./sources/execute/instructions/ld.c
SRC	+=	./sources/execute/instructions/st.c
SRC	+=	./sources/execute/instructions/add.c
SRC	+=	./sources/execute/instructions/sub.c
SRC	+=	./sources/execute/instructions/and.c
SRC	+=	./sources/execute/instructions/or.c
SRC	+=	./sources/execute/instructions/xor.c
SRC	+=	./sources/execute/instructions/zjmp.c
SRC	+=	./sources/execute/instructions/ldi.c
SRC	+=	./sources/execute/instructions/sti.c
SRC	+=	./sources/execute/instructions/fork.c
SRC	+=	./sources/execute/instructions/lld.c
SRC	+=	./sources/execute/instructions/lldi.c
SRC +=	./sources/execute/instructions/lfork.c
SRC +=	./sources/execute/instructions/aff.c
SRC	+=	./sources/decoder/instruction_decoder.c

T_SRC	:=	$(SRC)

SRC	+=	./main.c

GCOVR_OUTPUT = gcovr

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
DEPS	=	$(OBJ:%.o=%.d)

T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)
T_DEPS	=	$(T_OBJ:%.o=%.d)

all:	$(NAME)

-include $(DEPS)
-include $(T_DEPS)

$(NAME):	build_lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS_FLAGS)

$(T_NAME):	fclean build_lib $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME) $(LIBS_FLAGS)

$(T_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CFLAGS)

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

asan:	CFLAGS += -fsanitize=address,leak,undefined -g3
asan: re

tests_run:	$(T_NAME)
	@ -./$(T_NAME)

tests_run_pp:	$(T_NAME)
	@ -./$(T_NAME) --verbose --full-stats --color=always -j8
	@ mkdir -p $(GCOVR_OUTPUT)
	@ gcovr --exclude=tests --html-details $(GCOVR_OUTPUT)/output.html

build_lib:
	@ make -C ./lib/my/

clean:
	@ rm -f $(T_OBJ)
	@ rm -f $(OBJ)
	@ rm -rf $(T_BDIR)
	@ rm -rf $(BDIR)
	@ rm -rf $(GCOVR_OUTPUT)

fclean:	clean
	@ rm -f $(NAME)
	@ rm -f $(T_NAME)
	@ make -C ./lib/my/ fclean

.NOTPARALLEL: re
re:	fclean all

.PHONY : all asan tests_run_pp tests_run build_lib clean fclean re

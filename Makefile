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

GRH_CFLAGS	:= $(CFLAGS)

LIBS_FLAGS	=	-L./lib/ -lmy

GRH_LIBS_FLAGS	=	$(LIBS_FLAGS)
GRH_LIBS_FLAGS	+=	-lncurses

BDIR	=	.build/release/
T_BDIR	=	.build/tests/
GRH_BDIR	=	.build/graphical/

NAME	=	corewar
T_NAME	=	unit_tests
GRH_NAME	=	graphical

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

GRH_SRC	:=	$(SRC)
GRH_SRC	+=	./bonus/sources_graphical/visuals.c

SRC	+=	./sources/fake_visuals.c

GCOVR_OUTPUT = gcovr

OBJ	=	$(SRC:%.c=$(BDIR)/%.o)
DEPS	=	$(OBJ:%.o=%.d)

T_OBJ	=	$(T_SRC:%.c=$(T_BDIR)/%.o)
T_DEPS	=	$(T_OBJ:%.o=%.d)

GRH_OBJ	=	$(GRH_SRC:%.c=$(GRH_BDIR)/%.o)
GRH_DEPS	=	$(GRH_OBJ:%.o=%.d)

.PHONY: all
all:	$(NAME)

-include $(DEPS)
-include $(T_DEPS)

$(NAME):	build_lib $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LIBS_FLAGS)

$(T_NAME): build_lib $(T_OBJ)
	$(CC) $(T_OBJ) $(T_CFLAGS) -o $(T_NAME) $(LIBS_FLAGS)

$(GRH_NAME): build_lib $(GRH_OBJ)
	$(CC) $(GRH_OBJ) $(GRH_CFLAGS) -o $(GRH_NAME) $(GRH_LIBS_FLAGS)

$(T_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CFLAGS)

$(BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

$(GRH_BDIR)/%.o:	%.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(GRH_CFLAGS)

.PHONY: asan
asan:	CFLAGS += -fsanitize=address,leak,undefined -g3
asan: re

.PHONY: tests_run
tests_run:	$(T_NAME)
	@ -./$(T_NAME)

.PHONY: tests_run_pp
tests_run_pp:	$(T_NAME)
	@ -./$(T_NAME) --verbose --full-stats --color=always -j8
	@ mkdir -p $(GCOVR_OUTPUT)
	@ gcovr --exclude=tests --html-details $(GCOVR_OUTPUT)/output.html

.PHONY: build_lib
build_lib:
	@ make -C ./lib/my/

.PHONY: clean
clean:
	@ rm -f $(GRH_OBJ)
	@ rm -f $(T_OBJ)
	@ rm -f $(OBJ)
	@ rm -rf .build
	@ rm -rf $(GCOVR_OUTPUT)

.PHONY: fclean
fclean:	clean
	@ rm -f $(NAME)
	@ rm -f $(T_NAME)
	@ rm -f $(GRH_NAME)
	@ make -C ./lib/my/ fclean

.PHONY: re
.NOTPARALLEL: re
re:	fclean all

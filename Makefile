#TODO dependency to ".h"
################################################################################
# Basics #######################################################################
NAME	:=	21sh
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra #-Werror

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--leak-check=full --track-origins=yes --show-leak-kinds=all \
				--show-reachable=no

# Includes #####################################################################
INCL_DIR	:=	includes libft #libft needed ?
INCL_CMD	:=	$(addprefix -I,$(INCL_DIR))

INCL_FILES	:=	tosh.h #needed ? lexer.h ast.h

LIB_INCL	:=	-Llibft -lft
LIBFT_A		:=	libft/libft.a

# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	ENV_DIR		:=	environment
	ERRORS_DIR	:=	errors
	LEXER_DIR	:=	lexer
	PARSER_DIR	:=	token_parser
	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(ENV_DIR) $(ERRORS_DIR) $(LEXER_DIR) $(PARSER_DIR)

#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	handle_input.c prompt.c free.c main.c \
				test_pipe.c 
	#srcs subfiles names
	ENV_FILES		:=	environ_set.c environ_utils.c init_env.c shlvl.c
	ERRORS_FILES	:=	errors.c
	LEXER_FILES		:=	lexer.c lexer_tools.c lexer_op_chart.c get_token.c\
						tklst_utils.c
	PARSER_FILES	:=	token_parser.c

#list of all .c files
C_FILES	:=	$(SRC_FILES) $(ENV_FILES) $(ERRORS_FILES) $(LEXER_FILES)\
			$(PARSER_FILES)

# Complete path of each .c files ###############################################
SRC_PATH		:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
ENV_PATH		:=	$(addprefix $(ENV_DIR)/,$(ENV_FILES))
ERRORS_PATH		:=	$(addprefix $(ERRORS_DIR)/,$(ERRORS_FILES))
LEXER_PATH		:=	$(addprefix $(LEXER_DIR)/,$(LEXER_FILES))
PARSER_PATH		:=	$(addprefix $(PARSER_DIR)/,$(PARSER_FILES))

#list of all "path/x.c"
SRCS	:=	$(addprefix $(SRC_DIR)/,$(ENV_PATH)) \
			$(addprefix $(SRC_DIR)/,$(ERRORS_PATH)) \
			$(addprefix $(SRC_DIR)/,$(LEXER_PATH)) \
			$(addprefix $(SRC_DIR)/,$(PARSER_PATH)) \
			$(SRC_PATH)

# Object #######################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test ask_lib

all: ask_lib $(NAME) tag
	@./$(NAME)

ask_lib:
	@$(MAKE) -qC libft ; if [ $$? != "0" ] ; then\
		$(MAKE) -C libft;\
		$(MAKE) $(NAME);\
		fi

fsa: $(SRCS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)
	$(OPT) ./$(NAME)

val: $(SRCS) $(LIBFT_A)
	$(CC) $(DEBUG_FLAG) $(INCL_CMD) $(LIB_INCL) $^ -o $(NAME)
	valgrind $(VAL_FLAGS) $(OPT) ./$(NAME)

rmh:
	./script/42header_c_rm.sh $(SRCS)

adh: rmh
	vim -ns script/42header_add.keys $(SRCS)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(INCL_CMD) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFlAGS) $(INCL_CMD) -o $@ -c $<
	@echo Compiling $@

tag:
	@ctags -R .

clean: 
	$(MAKE) clean -C libft
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

d: all
	$(OPT) ./$(NAME)

vim:
	vim srcs/handle_input.c

norm: adh
	norminette $(SRCS)
	norminette includes/*.h

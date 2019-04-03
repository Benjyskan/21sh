################################################################################
# Basics #######################################################################
NAME	:=	21sh
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--leak-check=full --track-origins=yes --show-leak-kinds=all \
				--show-reachable=no

# Includes #####################################################################
INCL_DIR	:=	includes libft #libft needed ?
INCL_CMD	:=	$(addprefix -I,$(INCL_DIR))

INCL_FILES	:=	tosh.h #needed ?

LIB_INCL	:=	-Llibft -lft
LIBFT_A		:=	libft/libft.a

# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	ENV_DIR		:=	environment
	ERRORS_DIR	:=	errors
	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(ENV_DIR) $(ERRORS_DIR)

#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	cmd_lst_utils.c handle_input.c main.c prompt.c free.c \
				lexer.c my_strsplit.c test_pipe.c
	#srcs subfiles names
	ENV_FILES		:=	environ_set.c environ_utils.c init_env.c shlvl.c
	ERRORS_FILES	:=	errors.c

#list of all .c files
C_FILES	:=	$(SRC_FILES) $(ENV_FILES) $(ERRORS_FILES)

# Complete path of each .c files ###############################################
SRC_PATH		:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
ENV_PATH		:=	$(addprefix $(ENV_DIR)/,$(ENV_FILES))
ERRORS_PATH		:=	$(addprefix $(ERRORS_DIR)/,$(ERRORS_FILES))

#list of all "path/*.c"
SRCS	:=	$(addprefix $(SRC_DIR)/,$(ENV_PATH)) \
			$(addprefix $(SRC_DIR)/,$(ERRORS_PATH)) $(SRC_PATH)

#Object ########################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test ask_libft

all: ask_libft $(NAME) tag

ask_libft:
	@$(MAKE) -qC libft ; if [ $$? != "0" ] ; then\
		$(MAKE) -C libft;\
		$(MAKE) $(NAME);\
		else\
		echo "nothing to be done for $(LIBFT_A)";\
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
	ctags -R .

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

norm: adh
	norminette $(SRCS)
	norminette includes/*.h

test:
	@echo "-----------------------------------"
	$(MAKE) -qC libft/ ; echo answer=$$?

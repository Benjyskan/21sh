#include "ast.h"
#include "history.h"
#include "reader.h"



/*	OUTDATED
**	Function to reset the st_cmd without freeing it. Does not reset
**	everything, but only what needs to be reset to continue reading without
**	losing the initial text.

void		reset_st_cmd(t_st_cmd *st_cmd) //only modifies loal copy ?
{
	ft_bzero(st_cmd->st_txt->txt, st_cmd->st_txt->data_size);
	st_cmd->total_data_size = 0;
	st_cmd->tracker = 0;
	st_cmd->current_data_size = 0;
	retrieve_pos(&st_cmd->start_pos);
	ft_memdel((void*)&st_cmd->prompt);
	if (!(st_cmd->prompt = ft_strdup("psh $ "))) //protect //define PROMPT ?
		ERROR_MEM;
	st_cmd->append_txt = st_cmd->txt;
}
*/

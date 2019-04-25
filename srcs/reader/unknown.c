/*
**	Moves every character in the string `shift_no' bytes to the left
*/

void	shift_chars(char *str, unsigned int shift_no)
{
	size_t i;

	i = 0;
	while (str[i] && str[i + shift_no])
	{
		str[i] = str[i + shift_no];
		i++;
	}
	str[i] = str[i + shift_no];
	while (shift_no)
	{
		str[i + shift_no] = 0;
		shift_no--;
	}
}

/*
**	Deletes the character located on the left side of the cursor. Equivalent to
**	pressing backspace on a regular shell.
*/

void		delete_left(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	st_txt->tracker--;
	st_txt->data_size -= 1;
	reposition_cursor(st_cmd);
	execute_str(ERASE_ENDLINE);
	shift_chars(&st_txt->txt[st_txt->tracker], 1);
	ft_putstr_tty(&st_txt->txt[st_txt->tracker]); //shoud be special write function ?
}

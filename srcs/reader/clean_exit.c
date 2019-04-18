#include "reader.h"

void	clean_exit(int exitno)
{
	reset_terminal_settings();
	exit(exitno);
}

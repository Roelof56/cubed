#include "cubed.h"

// Exit the program as the failure u r.
// convert this to error_on_load(of iinit) - do cleaning.
int ft_strerror(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

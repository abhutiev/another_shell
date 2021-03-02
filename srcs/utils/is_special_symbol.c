#include "../../includes/minishell.h"

int	is_special_symbol(char c)
{
	if (c == '$' || c == '\'' || c == '\"'
		|| c == '\\' || c == ' ' || c == '\0')
		return (1);
	return (0);
}

#include "../../includes/minishell.h"

void	signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal_mode)
		{
			g_lobal = 1;
			ft_putstr_fd("\b\b  \b\b", 1);
			ft_putchar_fd('\n', 1);
			ft_putstr_fd(SHL_NAME, 1);
		}
		else
		{
			ft_putstr_fd("\n", 1);
			g_lobal = 130;
		}
	}
}

void	signal_ctrl_backslash(int sig)
{
	int		pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGQUIT)
	{
		if (!pid)
		{
			ft_putendl_fd("Quit: 3", 1);
			g_lobal = 131;
		}
		else
		{
			ft_putstr_fd("\b\b  \b\b", 1);
		}
	}
}

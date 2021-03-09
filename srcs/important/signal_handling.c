#include "../../includes/minishell.h"

void	signal_ctrl_c(int sig)
{
	int		pid;

	pid = waitpid(-1, NULL, WUNTRACED);
	if (sig == SIGINT)
	{
		g_lobal = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putendl_fd("", 1);
		if (pid)
		{
			return ;
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

void	fake_signal_ctrl_backslash(int sig)
{
	(void)sig;
}

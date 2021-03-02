#include "../../includes/minishell.h"

static int	cd_to_home(t_all *all)
{
	if (look_for_env(all, "HOME") == NULL)
	{
		ft_putendl_fd("bash: cd: HOME not set", 1);
		delete_environment(all, "?");
		add_environment(all, "?", "1");
		return (2);
	}
	add_environment(all, "OLDPWD", look_for_env(all, "PWD"));
	chdir(look_for_env(all, "HOME"));
	add_environment(all, "PWD", look_for_env(all, "HOME"));
	change_exitcode_success(all);
	return (1);
}

static int	cd_last(t_all *all)
{
	char	*tmp1;
	char	*tmp2;

	if (chdir(look_for_env(all, "OLDPWD")) == -1)
		return (2);
	tmp1 = ft_strdup(look_for_env(all, "PWD"));
	tmp2 = ft_strdup(look_for_env(all, "OLDPWD"));
	delete_environment(all, "PWD");
	delete_environment(all, "OLDPWD");
	add_environment(all, "PWD", tmp2);
	add_environment(all, "OLDPWD", tmp1);
	free(tmp1);
	free(tmp2);
	change_exitcode_success(all);
	return (1);
}

static int	cd_from_root_directory(t_all *all, size_t j)
{
	chdir("/");
	if (!ft_strcmp(all->command[j].args[1], "/"))
		return (1);
	if (cd_from_current_directory(all, j) == 2)
	{
		chdir(look_for_env(all, "PWD"));
		delete_environment(all, "?");
		add_environment(all, "?", "1");
		return (2);
	}
	change_exitcode_success(all);
	return (1);
}

static int	cd_from_home_directory(t_all *all, size_t j)
{
	chdir(look_for_env(all, "HOME"));
	if (cd_from_current_directory(all, j) == 2)
	{
		chdir(look_for_env(all, "PWD"));
		delete_environment(all, "?");
		add_environment(all, "?", "1");
		return (2);
	}
	change_exitcode_success(all);
	return (1);
}

int	cd(t_all *all, size_t j)
{
	if (all->command[j].args[1] == NULL)
		return (cd_to_home(all));
	else if (!ft_strcmp(all->command[j].args[1], "-"))
		return (cd_last(all));
	else if (all->command[j].args[1][0] == '/')
		return (cd_from_root_directory(all, j));
	else if (all->command[j].args[1][0] == '~')
		return (cd_from_home_directory(all, j));
	else
		return (cd_from_current_directory(all, j));
}

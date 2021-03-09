#include "../../includes/minishell.h"

static void	get_ready_for_cd(t_all *all, t_cd *cd, size_t j)
{
	cd->save_pwd = look_for_env(all, "PWD");
	cd->i = 0;
	cd->tmp = getcwd(NULL, -1);
	cd->splitted_path = split(cd->tmp, '/');
	free(cd->tmp);
	cd->splitted_directories = split(all->command[j].args[1], '/');
	if (all->command[j].args[1][0] == '~')
	{
		free(cd->splitted_directories[0]);
		cd->i++;
	}
}

static void	cd_up(t_cd *cd)
{
	cd->k = 0;
	while (cd->splitted_path[cd->k])
		cd->k++;
	if (cd->k == 0)
	{
		free(cd->splitted_directories[cd->i]);
		return ;
	}
	free(cd->splitted_path[cd->k - 1]);
	cd->splitted_path[cd->k - 1] = NULL;
	free(cd->splitted_directories[cd->i]);
}

static void	memory_cleaning_and_forming_of_path(t_cd *cd)
{
	free(cd->splitted_directories);
	cd->k = 0;
	cd->path = ft_calloc(1, 1);
	while (cd->splitted_path[cd->k])
	{
		cd->tmp = cd->path;
		cd->path = strjoin_for_path(cd->path, cd->splitted_path[cd->k]);
		free(cd->splitted_path[cd->k++]);
		free(cd->tmp);
	}
	free(cd->splitted_path);
	if (cd->k == 0)
	{
		chdir("/");
		free(cd->path);
		return ;
	}
}

static int	changing_of_directory_replacing_env(t_all *all, t_cd *cd, size_t j)
{
	if (chdir(cd->path) == -1)
	{
		change_exitcode_and_errno(all, "1", j);
		free(cd->path);
		return (2);
	}
	delete_environment(all, "OLDPWD");
	add_environment(all, "OLDPWD", cd->save_pwd);
	cd->tmp = getcwd(NULL, -1);
	add_environment(all, "PWD", cd->tmp);
	free(cd->tmp);
	free(cd->path);
	return (1);
}

int	cd_from_current_directory(t_all *all, size_t j)
{
	t_cd	cd;

	get_ready_for_cd(all, &cd, j);
	while (cd.splitted_directories[cd.i])
	{
		if (!ft_strcmp("..", cd.splitted_directories[cd.i]))
			cd_up(&cd);
		else if (!ft_strcmp(".", cd.splitted_directories[cd.i]))
			free(cd.splitted_directories[cd.i]);
		else
		{
			cd.k = 0;
			while (cd.splitted_path[cd.k])
				cd.k++;
			cd.splitted_path[cd.k] = cd.splitted_directories[cd.i];
		}
		cd.i++;
	}
	memory_cleaning_and_forming_of_path(&cd);
	if (changing_of_directory_replacing_env(all, &cd, j) == 2)
		return (2);
	return (1);
}

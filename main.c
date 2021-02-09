/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "includes/minishell.h"
# include <unistd.h>
# include <stdio.h> //
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

//void	count_commands(t_all *all)
//{
//	all->command.number_of_commands = 1;
//	while (all->buffer.line_1[all->buffer.iter_1])
//	{
//		if (/*all->buffer.line_1[all->buffer.iter_1] == '<' || */all->buffer.line_1[all->buffer.iter_1] == '|')
//			all->command.number_of_commands++;
////		if (all->buffer.line_1[all->buffer.iter_1] == '>')
////		{
////			all->command.number_of_commands++;
////			if (all->buffer.line_1[all->buffer.iter_1 + 1] == '>')
////				all->buffer.iter_1++;
////		}
//		all->buffer.iter_1++;
//	}
//	printf("%zu\n", all->command.number_of_commands);
//	all->buffer.iter_1 = 0;
//}
//
//void	second_circle_of_parsing(t_all *all, size_t i)
//{
//	all->buffer.iter_1 = 0;
//	all->buffer.iter_2 = 0;
//	all->buffer.line_1 = all->requests.line_with_substitutions[i];
//	count_commands(all);
////
////	while (all->buffer.line_1[all->buffer.iter_1])
////	{
////		if (all->buffer.line_1[all->buffer.iter_1] == ' ' && is_shielded(all->buffer.line_1[all->buffer.iter_1] == ' '))
////		{}
////	}
//}
//
////void	distribution_and_execution(t_all *all, size_t i)
////{
////	if (ft_strcmp("env", ))
////	{
////		env(all);
////	}
////	else if (ft_strcmp("pwd", ))
////	{
////		pwd(all);
////	}
////	else if
////
////}
//
//void	parsing_and_execution(t_all *all)
//{
//	size_t	i;
//
//	i = 0;
//	while (all->requests.separated[i])
//	{
//		first_circle_of_parsing(all, i);
//		second_circle_of_parsing(all, i);
//		printf("%s\n", all->requests.line_with_substitutions[i]);
//		free(all->requests.line_with_substitutions[i]);
//		//distribution_and_execution(all, i);
//		i++;
//	}
//	free(all->requests.separated[i]);
//	free(all->requests.separated);
//	free(all->requests.line_with_substitutions[i]);
//	free(all->requests.line_with_substitutions);
//}

int		main(int argc, char **argv, char **env)
{
	//t_all	all;

	//pregame_ritual(&all, argc, argv, env);
//	while (1)
//	{
//		write(1, SHELL_NAME, ft_strlen(SHELL_NAME));
//		get_next_line(0, &(all.buffer.line_1));
//		count_requests(&all);
//		separate_requests(&all);
//		parsing_and_execution(&all);
//	}

	char *ar[3];
	int fd[2];

	ar[0] = strdup("/usr/bin/grep");
	ar[1] = strdup("a");
	ar[2] = NULL;
	int save_out = dup(1);


	pipe(fd);
	dup2(fd[1], 1);
	dup2(fd[0], 0);
	pid_t	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		execve("/usr/bin/env", argv, env);
	}
	pid_t pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(save_out, 1);
		execve("/usr/bin/grep", ar, env);
		exit(0);
	}
	return (0);
}

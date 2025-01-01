/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:58:06 by femullao          #+#    #+#             */
/*   Updated: 2024/12/27 16:15:48 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

static void	first_process(char **av, char **env, int pp[2])
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (access(av[1], F_OK) != -1 && access(av[1], R_OK) == -1)
		{
			ft_putstr_fd("Permission Denied: ", 2);
			ft_putendl_fd(av[1], 2);
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(av[1], 2);
		exit(EXIT_FAILURE);
	}
	close(pp[0]);
	dup2(fd, 0);
	close(fd);
	dup2(pp[1], 1);
	close(pp[1]);
	run_command(av[2], env);
}

static void	second_process(char **av, char **env, int pp[2])
{
	int	fd;

	fd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (access(av[4], W_OK) == -1)
		{
			ft_putstr_fd("permission denied: ", 2);
			ft_putendl_fd(av[4], 2);
			exit(EXIT_FAILURE);
		}
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(av[4], 2);
		exit(EXIT_FAILURE);
	}
	dup2(pp[0], 0);
	close(pp[0]);
	dup2(fd, 1);
	close(fd);
	close(pp[1]);
	run_command(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	ch;
	int		fd[2];

	if (ac != 5)
		return (ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2), 1);
	if (pipe(fd) == -1)
	{
		perror("pipe failed: ");
		exit(EXIT_FAILURE);
	}
	ch = fork();
	if (ch == 0)
		first_process(av, env, fd);
	waitpid(ch, NULL, 0);
	second_process(av, env, fd);
}

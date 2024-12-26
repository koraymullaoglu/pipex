/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:18:14 by femullao          #+#    #+#             */
/*   Updated: 2024/12/23 16:12:49 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// pipex file1 cmd1 cmd2 file2

void first_process(char **av, char**env, int fd[2])
{
	int f1;
	pid_t ch;

	f1 = open(av[1], O_RDONLY);
	if (f1 == -1)
	{
		ft_putendl_fd("pipex: no such file or directory: file1", 2);
		return;
	}
	ch = fork();
	if (ch == 0)
	{
		close(fd[0]);
		dup2(f1, 0);
		close(f1);
		dup2(fd[1], 1);
		close(fd[1]);
		//run command1;
		exit(127);
	}
	
}

void second_process(char **av, char **env, int fd[2])
{
	int f2;
	
	f2 = open(av[4], O_CREAT, O_WRONLY);
	if (f2 == -1)
	{
		ft_putendl_fd("pipex: valla acilmadi : file2", 2);
		return;
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(av[4],1);
	close(av[4]);
	//run command2
	exit(127);
}





void run_pipex(char **av, char **env, int fd[2])
{
	first_process(av,env,fd);
	second_process(av,env,fd);
}


int main(int ac, char **av, char **env)
{
	int fd[2];
	if (ac != 5)
	{
		ft_putendl_fd("./pipex file1 cmd1 cmd2 file2", 2);
	}
	else
	{
		run_pipex(av,env,fd);
	}
}
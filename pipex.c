#include "pipex.h" 


void first_process(char **av, char **env, int pp[2])
{
	int fd;

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
	dup2(pp[1], 1);
	close(fd);
	close(pp[1]);
	run_command(av[2], env);
}

void second_process(char **av, char **env, int pp[2])
{
	int fd;

	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(av[4], 2);
		return ;
	}
	close(pp[1]);
	dup2(pp[0], 0);
	dup2(fd, 1);
	close(pp[0]);
	close(fd);
	run_command(av[3], env);
}


int main(int ac, char **av , char **env)
{
	pid_t ch;
	int fd[2];
	pipe(fd);

	if (ac == 5)
	{
		ch = fork();
		if (ch == 0)
			first_process(av, env, fd);
		waitpid(ch, NULL, 0);
		second_process(av, env, fd);
	}
	ft_putstr_fd("./pipex file1 cmd1 cmd2 file2\n", 2);
	return (1);

}	

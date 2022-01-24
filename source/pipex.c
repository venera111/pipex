/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:45:05 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 12:20:09 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pars_envp(char **envp, char	**cmd, int i, int k)
{
	char	**out;
	char	*path;

	while (envp[i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_strrchr(path, '=');
			out = ft_split(path, ':');
			while (out[k])
			{
				i = 0;
				out[k] = ft_strjoin(out[k], "/");
				out[k] = ft_strjoin(out[k], cmd[0]);
				execve(out[k], cmd, NULL);
				k++;
			}
			ft_perror("Wrong command");
		}
		i++;
	}
}

void	child_process(t_data *data, char **envp, int *fd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	close(fd[0]);
	if (dup2(data->file1, 0) < 0)
		ft_perror(DUP2_FILE);
	if (dup2(fd[1], 1) < 0)
		ft_perror(DUP2_PIPE);
	close(fd[1]);
	close(data->file1);
	pars_envp(envp, data->cmd1, i, k);
}

void	parent_process(t_data *data, char **envp, int *fd)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		ft_perror(DUP2_PIPE);
	if (dup2(data->file2, 1) < 0)
		ft_perror(DUP2_FILE);
	close(fd[0]);
	close(data->file2);
	pars_envp(envp, data->cmd2, i, k);
}

void	check_argv(int argc, t_data *data, char **argv)
{
	if (argc == 5)
	{
		data->cmd1 = ft_split(argv[2], ' ');
		data->cmd2 = ft_split(argv[3], ' ');
		data->file1 = open(argv[1], O_RDONLY);
		data->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->file1 == -1 || data->file2 == -1)
			ft_perror(FILE_ERROR);
	}
	else
		ft_perror(ARGC_ERROR);

}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		fd[2];
	t_data	data;

	if (pipe(fd) == -1)
		ft_perror(PIPE_ERROR);
	check_argv(argc, &data, argv);
	pid = fork();
	if (pid == -1)
		ft_perror(PID_ERROR);
	if (pid == 0)
		child_process(&data, envp, fd);
	else
		parent_process(&data, envp, fd);
	return (0);
}

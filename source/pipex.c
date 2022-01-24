/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:45:05 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 14:06:36 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pars_envp(char **envp, char	**cmd, int i, int j)
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
			while (out[j])
			{
				i = 0;
				out[j] = ft_strjoin(out[j], "/");
				out[j] = ft_strjoin(out[j], cmd[0]);
				execve(out[j], cmd, NULL);
				j++;
			}
			ft_perror("Wrong");
		}
		i++;
	}
}

void	child_process(t_data *data, char **envp, int *fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	close(fd[0]);
	if (dup2(data->file1, 0) < 0)
		ft_perror(DUP2_FILE);
	if (dup2(fd[1], 1) < 0)
		ft_perror(DUP2_PIPE);
	close(fd[1]);
	close(data->file1);
	pars_envp(envp, data->cmd1, i, j);
}

void	parent_process(t_data *data, char **envp, int *fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		ft_perror(DUP2_PIPE);
	if (dup2(data->file2, 1) < 0)
		ft_perror(DUP2_FILE);
	close(fd[0]);
	close(data->file2);
	pars_envp(envp, data->cmd2, i, j);
}

void	check_argv(int argc, t_data *data, char **argv)
{
	if (argc == 5)
	{
		data->cmd1 = ft_split(argv[2], ' ');
		data->cmd2 = ft_split(argv[3], ' ');
		handler_file(data, argv);
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

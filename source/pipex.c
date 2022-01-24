/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:45:05 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 20:49:04 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*pars_envp(char **envp, char **cmd, t_data *data)
{
	data->i = 0;
	while (!ft_strnstr(envp[data->i], "PATH=", 5))
	{
		data->i++;
		if (!envp[data->i])
			ft_perror("");
	}
	data->out = ft_split(envp[data->i] + 5, ':');
	data->j = 0;
	while (data->out[data->j])
	{
		data->line = ft_strjoin(data->out[data->j], "/");
		data->comm = ft_strjoin(data->line, cmd[0]);
		free(data->line);
		if (access(data->comm, F_OK) == 0)
		{
			ft_free(data->out);
			return (data->comm);
		}
		free(data->comm);
		data->j++;
	}
	return (0);
}

void	child_process(t_data *data, char **envp, int *fd)
{
	char	*line;

	if (dup2(data->file1, 0) < 0)
		ft_perror(DUP2_FILE);
	if (dup2(fd[1], 1) < 0)
		ft_perror(DUP2_PIPE);
	if (close(fd[0]) == -1 || close(fd[1]) == -1 || close(data->file1) == -1)
		ft_perror(CLOSE_ERR);
	line = pars_envp(envp, data->cmd1, data);
	if (execve(line, data->cmd1, envp) == -1)
		ft_perror("");
}

void	parent_process(t_data *data, char **envp, int *fd)
{
	char	*line;

	if (dup2(fd[0], 0) < 0)
		ft_perror(DUP2_PIPE);
	if (dup2(data->file2, 1) < 0)
		ft_perror(DUP2_FILE);
	if (close(fd[1]) == -1 || close(fd[0]) == -1 || close(data->file2) == -1)
		ft_perror(CLOSE_ERR);
	line = pars_envp(envp, data->cmd2, data);
	if (execve(line, data->cmd2, envp) == -1)
		ft_perror("");
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:45:05 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/22 17:10:05 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*part_path;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH=", 5))
	{
		i++;
		if (!envp[i])
			ft_perror(PATH_ERROR);
	}
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd[0]);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

void	child_process(char **envp, int *fd, t_data *data)
{
	char *path;

	if (dup2(data->file_fd[0], 0) < 0)
		ft_perror(DUP2_ERROR);
	if (dup2(fd[1], 1) < 0)
		ft_perror(DUP2_PIPE);
	close(fd[0]);
	close(fd[1]);
	close(data->file_fd[0]);
	path = get_path(data->cmd1, envp);
	execve(path, data->cmd1, envp);
}

void	parent_process(char **envp, int *fd, t_data *data)
{
	char *path;

	if (dup2(data->file_fd[1], 1) < 0)
		ft_perror(DUP2_ERROR);
	if (dup2(fd[0], 0) < 0)
		ft_perror(DUP2_PIPE);
	close(fd[0]);
	close(fd[1]);
	close(data->file_fd[1]);
	path = get_path(data->cmd2, envp);
	execve(path, data->cmd2, envp);
}

void	check_argv(int argc, char **argv, t_data *data)
{
	if (argc == 5)
	{
		data->cmd1 = ft_split(argv[2], ' ');
		data->cmd2 = ft_split(argv[3], ' ');
		if (access(argv[1], F_OK) != 0 || access(argv[1], R_OK) != 0)
			ft_perror(NO_FILE);
		data->file_fd[0] = open(argv[1], O_RDONLY, 0777);
		data->file_fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->file_fd[0] == -1 || data->file_fd[1] == -1)
			ft_perror(FILE_ERROR);
	}
	else
		ft_perror(ARGV_ERROR);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		fd[2];
	int		pid;

	if (envp[0] == NULL)
		return (EXIT_SUCCESS);
	check_argv(argc, argv, &data);
	if (pipe(fd) == -1)
		ft_perror(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		ft_perror(PID_ERROR);
	if (pid == 0)
		child_process(envp, fd, &data);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(envp, fd, &data);
	}
	return (0);
}

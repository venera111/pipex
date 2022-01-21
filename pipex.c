/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:45:05 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/21 21:36:27 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *cmd, char **envp)						// написать проверку нахождения PATH в списке
{
	int		i;
	char	*path;
	char	**paths;
	char	*path2;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)				// пока не нашли PATH в переменных
		i++;
	paths = ft_split(envp[i] + 5, ':');							// как тольк нашли PATH, ищем : в строке и дробим на части
	i = 0;
	while (paths[i])
	{
		path2 = ft_strjoin(paths[i], "/");						// создаем путь к переменной соединяя шлэшем
		path = ft_strjoin(path2, cmd);							// создаем путь к текущей команде
		free(path2);
		if (access(path, F_OK) == 0)							// проверяем работает ли путь/существование команды
			return (path);
		i++;
	}
	return (0);
}

void	ft_execute(char *argv2, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv2, ' ');									// получаем строки нашей cmd1
	path = get_path(cmd[0], envp);								// передаем команду без флагов и переменные окружения
	if (execve(path, cmd, envp) == -1)							// исполняет команду по ее пути и не возвращает управление
		ft_perror(COM_ERROR);
}

void	child_process(char **argv, char **envp, int *fd)
{
	if ((open(argv[1], O_RDONLY, 0777)) == -1)
		ft_perror(FILE_ERROR);									// не удалось открыть файл
	if (access(argv[1], F_OK) != 0)								// F_OK проверяет существование файла
		ft_perror(NO_FILE);
	else if (access(argv[1], R_OK) != 0)						// R_OK проверяет, существует ли файл, и предоставляет права на чтение
		ft_perror(PERM_DEN);
	dup2(fd[1], 1);												// копируем f[1] на запись pipe()
	dup2(open(argv[1], O_RDONLY, 0777), 0);						// копируем fd файла1
	close(fd[0]);												// закрываем fd[0] на чтение pipe()
	ft_execute(argv[2], envp);									// cmd1 и envs: функция исполнения команды cmd1
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fdes;

	fdes = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fdes == -1)
		ft_perror(FILE_ERROR);
	dup2(fd[0], 0);
	dup2(fdes, 1);
	close(fd[1]);
	ft_execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (envp[0] == NULL)
		return (EXIT_SUCCESS);
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_perror(PIPE_ERROR);
		pid = fork();
		if (pid == -1)
			ft_perror(PID_ERROR);
		if (pid == 0)
			child_process(argv, envp, fd);
		waitpid(pid, NULL, 0); // Функция waitpid приостанавливает выполнение текущего процесса до тех пор, пока дочерний процесс, указанный в параметре pid, не завершит выполнение
		parent_process(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> file2\n", 1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:20:35 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 14:13:45 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	print_stdout_error(char *error, char *name)
{
	write(STDERR_FILENO, error, ft_strlen(error));
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "\n", 1);
}

void	handler_file(t_data *data, char **argv)
{
	if (access(argv[1], R_OK) != -1)
	{
		data->file1 = open(argv[1], O_RDONLY);
		if (data->file1 == -1)
			ft_perror(FILE_ERR);
	}
	else
		print_stdout_error(NO_PERM, argv[1]);
	if (access(argv[1], F_OK) == -1)
		print_stdout_error(FILE_OR_DIR, argv[1]);
	if (access(argv[4], F_OK) != -1
		&& (access(argv[4], R_OK) == -1
			|| access(argv[4], W_OK) == -1))
		print_stdout_error(NO_PERM, argv[4]);
	else if (access(argv[4], F_OK) != -1)
		data->file2 = open(argv[4], O_WRONLY | O_APPEND);
	else if (access(argv[4], F_OK) != -1)
		data->file2 = open(argv[4], O_WRONLY | O_TRUNC);
	else
		data->file2 = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (data->file2 == -1)
		ft_perror(FILE_ERR);
}

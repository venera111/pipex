/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:20:35 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 20:44:49 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **comm)
{
	int	i;

	i = 0;
	while (comm[i])
		free(comm[i++]);
	free(comm);
}

void	ft_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	handler_file(t_data *data, char **argv)
{
	if (access(argv[1], F_OK) != 0)
		ft_perror(FILE_OR_DIR);
	if (access(argv[1], R_OK) != 0)
		ft_perror(FILE_ERR);
	data->file1 = open(argv[1], O_RDONLY, 0777);
	data->file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->file1 == -1 || data->file2 == -1)
		ft_perror(FILE_ERR);
}

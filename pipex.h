/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:22:48 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/22 17:07:47 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h> // EXIT_FAILURE
#include <fcntl.h> // O_RDONLY
#include <unistd.h> // pipe()
#include <stdio.h> // perror()
#include "error.h"
#include "libft/libft.h"

typedef struct s_data
{
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;
	int		file_fd[2];

}	t_data;

void	ft_perror(char *str);

#endif

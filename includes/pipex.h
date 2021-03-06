/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:22:48 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 18:33:36 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <error.h>
# include <libft.h>

typedef struct s_data
{
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;
	int		file1;
	int		file2;
	int		i;
	int		j;
	char	**out;
	char	*line;
	char	*comm;

}	t_data;

void	ft_perror(char *str);
void	handler_file(t_data *data, char **argv);
void	ft_free(char **comm);

#endif

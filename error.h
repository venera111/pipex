/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:26:58 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/22 14:17:56 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define PIPE_ERROR "Error pipe\n"
# define PID_ERROR "Error fork\n"
# define COM_ERROR "The command was not executed\n"
# define FILE_ERROR "Failed to open file\n"
# define NO_FILE "pipex: no such file or directory: \n"
# define PERM_DEN "pipex: permission denied:\n"
# define ARGV_ERROR "Not enough arguments\n"
# define DUP2_ERROR "dup2() error\n"
# define DUP2_PIPE "Couldn't write the pipe\n"
#endif

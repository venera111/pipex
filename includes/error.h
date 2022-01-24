/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:26:58 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/24 13:41:55 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define PIPE_ERROR "Error pipe\n"//
# define PID_ERROR "Error fork\n"//
# define ARGC_ERROR "pipex: wrong number of arguments"//
# define DUP2_FILE "dup2() error\n"//
# define DUP2_PIPE "Couldn't write the pipe\n"//
# define FILE_ERR "Permission Denied"
# define FILE_OR_DIR ": no such file or directory: "
# define NO_PERM ": permission denied: "
# define COMMAND_NOT_FOUND ": command not found: "
#endif

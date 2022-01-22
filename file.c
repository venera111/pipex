/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qestefan <qestefan@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:18:16 by qestefan          #+#    #+#             */
/*   Updated: 2022/01/22 21:05:15 by qestefan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int num_chars;
	int file;
	int num_process;
	int buff[100];
	int fd[2];

	// buff[7] = 34243;
	// buff[8] = 234234;

	printf("fd[0] %i fd[1] %i\n", buff[7], buff[8]);
	pipe(&buff[7]);
	printf("fd[0] %i fd[1] %i\n", buff[7], buff[8]);

	file = open("file1", O_RDONLY);
	num_chars = read(file, buff, 5);
	printf("%10s : %i\n", "num_chars", num_chars);
	close(file);

	file = open("file1", O_RDONLY | O_CREAT | O_TRUNC, 0777);
	num_chars = read(file, buff, 5);
	printf("%10s : %i\n", "num_chars", num_chars);
	close(file);

	// num_process = 0;
	// for (size_t i = 0; i < 2; i++)
	// {
	// 	++num_process;
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		printf("%10s : %i\n%10s : %i\n", "process", num_process, "fd", file);
	// 		exit(0);
	// 	}
	// }
	// sleep(20);
	return 0;
}

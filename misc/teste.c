/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrianofaus <adrianofaus@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:21:37 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/03/15 13:27:41 by adrianofaus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

/* QUAL É A CONCLUSÃO?
	// Dentro da função execve o primeiro argumento 
	precisa necessariamente ser o comando
	// "desexpandido", ou seja, se vier no input g"r"ep, 
	o primeiro argumento de execve tem que
	// ser "/usr/bin/grep", caso contrário dá ruim. 
	e tudo bem dentro do array estar g"r"ep! 
*/
/*
int	main(int argc, char *argv[], char *envp[])
{
	char	*arr[] = { "/usr/bin/ls", "-la", NULL};
	printf("%s\n", "\0");
	printf("%p\n", arr[0]);
	if (-1 == execve(arr[0], arr, envp))
		printf("deu ruim\n");
	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/11 18:07:51 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv)
{
    int id = 0;
    int fd[2];
    int nb = 22;
    int nb2;
    
    // fd[0] = open(argv[1], O_RDONLY);
    // fd[1] = open(argv[2], O_RDONLY);
    pipe(fd);
    id = fork();
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &nb, sizeof(int));
        close(fd[1]);
    }
    if (id != 0)
    {
        close(fd[1]);
        read(fd[0], &nb2, sizeof(int));
        printf("%d\n", nb2);
        close(fd[0]);
    }
    
    
}

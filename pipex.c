/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/13 13:49:31 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv)
{
    int id = 0;
    int id2 = 0;
    int fd[2];
    char    buffer[100];
    int     fd2[2];
    

    // DOUBLE PIP
    // pipe(fd);
    // pipe(fd2);
    // id = fork();
    // if (id == 0)
    // {
    //     int nb = 5;
    //     close(fd[0]);
    //     write(fd[1], &nb, sizeof(int));
    //     close(fd[1]);

    //     close(fd2[1]);
    //     read(fd2[0], &nb, sizeof(int));
    //     close(fd2[0]);
    //     printf("%d\n", nb);
    // }
    // if (id != 0)
    // {
    //     int nb2;
    //     close(fd[1]);
    //     read(fd[0], &nb2, sizeof(int));
    //     close(fd[0]);
    //     // printf("%d\n", nb2);
    //     nb2 *= 2;

    //     close(fd2[0]);
    //     write(fd2[1], &nb2, sizeof(int));
    //     close(fd2[1]);
    // }
    // TEST PROCESS ID //////////////////////////////////////////////////////
    // id = fork();
    // id2 = fork();
    // if (id == 0)
    // {
    //     if (id2 == 0)
    //     {
    //         printf("child2\n");
    //     }
    //     else
    //     {
    //         // wait(NULL);
    //         printf("parent\n");
    //     }
    // }
    // else 
    // {
    //     if (id2 == 0)
    //     {
    //         printf("child1\n");
    //     }
    //     else
    //     {
    //         printf("main\n");
    //     }
    // }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/14 16:37:44 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int argc, char **argv, char **env)
{
    int     id = 0;
    int     id2 = 0;
    int     fd[2];
    char    buffer[100];
    int     fd2[2];
    char    *path_line;
    char    **commands;
    char    **paths;
    char    **final_paths;
    int     i = 0;
    t_var   var;
    // GET INPUT //////////////////////////////////////////////////////////////
    
    commands = ft_split1(argv[2], ' ');
    // ft_print(commands);
    // free_strs(commands);
    
    // GET PATHS //////////////////////////////////////////////////////////////
    
    // while (*env) {
    //     printf("%s\n", *env);
    //     env++;
    // }
    find_path_line(&path_line, env);
    // ft_printf("%s\n", path_line);
    paths = ft_split(path_line + 5, ':');
    if (!paths)
        return (0);
    if (join_paths(paths, commands[0], &final_paths) == 1)
        return (0);
    // ft_print(final_paths);
    while (final_paths[i])
    {
        if (access(final_paths[i], F_OK) == 0)
        break;
        i++;
    }
    // free_strs(paths);
    // free_strs(final_paths);
    
    // USE EXECVE //////////////////////////////////////////////////////////////
    
    fd[1] = open(argv[1], O_RDONLY);
    dup2(fd[1], STDIN_FILENO);
    // dup2(fd[1], STDOUT_FILENO);
    execve(final_paths[i], commands, env);

    // DOUBLE PIPE ////////////////////////////////////////////////////////////
    
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

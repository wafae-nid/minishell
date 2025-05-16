/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:04:08 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/11 20:45:32 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *extract_the_cd_path(char *readline)
// {
//         char **splited;


//         splited = ft_split(readline, ' ');
//         if(!splited)
//                 return(NULL);
//         else
//         {
//                 if(count_words(readline, ' ') == 2)
//                         return (splited[1]);
//                 else
//                         return(NULL);
//         }
// }

void  pwd_execution(t_com   *command)
{
    char *PWD;

    if ((command->command)[1])
    {
        printf("error msg");
        return;
    }
    PWD = getcwd(NULL,0);
    if(!PWD )
        perror("problem finding current directory");
    else
        printf("%s\n", PWD);
    
}

 //int main()
// {
//     char *new_path;
//     char *new;
//     char *PWD;
//     char *OLDPWD;
//     char *prompt;
//     char *read_line;

//     //PWD=getcwd(NULL,0);
//     //PWD=getcwd(NULL,0);
//    // if(!PWD)
//        // printf("Current directory has been deleted.\n");

//    // else
//       //  printf("%s", PWD);
//       new = ft_strjoin("\\","\n");
//       printf("%s", new);
// }

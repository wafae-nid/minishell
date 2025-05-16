/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 08:12:05 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/10 05:55:51 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int identify_the_arg(char **str, int *i)
{
    int j ;
    j = 0;

   while(str[*i])
    {
        if (str[*i][0] == '-')
        {
            j = 1;
            while(str[*i][j])
            {
                if(str[*i][j] != 'n')
                    return(0);
                j++;
            }
        }
        else 
            return(0);
        (*i)++;
    }
    return(1);
    
}


void echo_execution(t_com *command)
{
    int i;
    int new_line;

    new_line = 0;
    i = 1;
    if(!identify_the_arg((command->command), &i))
    {
        if(i != 1 )//cause if i != 1 of course we did pass one valid argument   
            new_line = 1; 
    }
    while((command->command)[i])
    {
        printf("%s",(command->command)[i]);
        if((command->command)[i+1] != NULL)
            printf(" ");
        i++;
    }
    if(new_line == 0)
        printf("\n");
    
}

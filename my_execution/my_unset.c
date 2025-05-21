/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:32:44 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/21 01:37:34 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void unsetting_input(char *variable, t_environ **environ)
{
    
    t_environ *tmp;
    t_environ *current;
    
    tmp = (*environ);
    while(tmp)
    {
        if((tmp->next) && !strcmp((tmp->next)->var, variable))
        {
            tmp->next = (tmp->next)->next;
            break;
        }
        tmp=tmp->next;     
    }
}
static int unsetting_input_parsing(char *variable, t_environ **environ)
{
    t_environ *current;
    
    current = *environ;
    while(current)
    {
        if(!ft_strcmp(variable,(current)->var))
        {
            return(1);
        }
        current = current->next; 
    }
    return(0);
}
void unset_executing(t_com *command, t_environ **environ)
{
    int i;

    t_environ *current;
    
    if(command->command)
    {
        i = 1;
        while(command->command[i])
        {
            if(unsetting_input_parsing(command->command[i], environ))
            {
                unsetting_input(command->command[i], environ);
            }
            else 
            return;
            i++;
        }
    }
    current = (*environ);
    while(current)
    {
        printf("%s\n", current->var);
        current = current->next;
    }
    
}

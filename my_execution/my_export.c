/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:53:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/25 00:55:46 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_is_a_numb(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    else
        return(0);
}
static int is_while_space(char c)
{
    if((c > 8 && c <= 13) || c == ' ')
        return(1);
    return(0);
}


static int valid_position_export(char *str)
{
    int i;

    i = 0;
    
    if(!str)
        return(-1);
    while(str[i])
    {
        if(((str[i] == '=') && ((i == 0) || is_while_space(str[i-1])) )|| ((str[i] =='+') && ((i ==0) || is_while_space(str[i-1]))))
            return(0);
        i++; 
    }
    return(1);
}

static int var_name_end(char *str)
{
    int i;
    
    int count;

    i = 0;
    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i]=='+' && str[i+1] == '=' && i!=1)
        {
            i--;
            return(i);
        }
        else if(str[i] == '=' && i!= 1)
        {
            i--;
            return(i);
        }
        i++;
    }
    return(i);
}
static int non_valid_identifier(char c)
{
    if(c == '*' || c == '%' || c == '#' 
         || c == '-' || c == '(' || c == ')' 
         || c == '!' || c == '{' || c == '}' 
         || c == '[' || c == ']' || c == '?' || c == '&'
         || c == '~' || c == '.' || c == '@' || c == ';' || c == ':')
    {
        return(1);
    }
    else
        return(0);
}

static int valid_var_name(char *str, int count)
{
    int i;
    
    if(!str)
    {
        return(-1);
    }
    if(ft_is_a_numb(str[0]))
        return(0);
    i = 0;
    while(i < count)
    {
        if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
        {
            return(0);
        }
        
        i++;
    }
    return(1);
    
}

static void start_of_arguments(t_com *command,char **oldpromt)
{
    int i;
    
    i = 0;

     while((*oldpromt) && is_while_space((*oldpromt)[0]))
    {
        (*oldpromt)++;
    }
    while((*oldpromt)[0] && (command->command[0] && (command->command)[0][0] == (*oldpromt)[0]))
    {
        (command->command[0])++;
        (*oldpromt)++;
    }
    while((*oldpromt) && is_while_space((*oldpromt)[0]))
    {
        (*oldpromt)++;
    }
}
static int count_lengh_value_str_export(char *str)
{
    int i;

    int count;
    
    i = 0;
    count = 0;
    if(!str)
        return(-1);
    if(str[i] && (str[i] == '=' || str[i] == '+'))
    {
        if(str[i] && str[i]=='=')
            i++;
        i++; 
    }
    while(str[i])
    {
        i++;
        count++;
    }
    return(count);
   
    
}

static int count_lengh_var_str_export(char *str)
{
    int i ;
    
    i = 0;
    while(str[i] &&(str[i] != '=' && str[i]!= '+'))
    {
        i++;
    }
    return (i);  
}
 static void fill_in_environ(char *str,char ***splited_export_char)
{
    int i;
    int j;
    
    i = 0;
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        
        (*splited_export_char)[0][i] = str[i];
        i++;
    }
    (*splited_export_char)[0][i] = '\0';
    j = 0;
    if(str[i] == '=' || str[i] == '+')
    {
        if(str[i] == '+')
        {
            (*splited_export_char)[1][j]='+';
            i++;
            j++;
        }
        (*splited_export_char)[1][j]='=';
        i++;
        j++;
    }
    if((*splited_export_char)[1])
        (*splited_export_char)[1][j]='\0';
    j = 0;
    while(str[i])
    {
        (*splited_export_char)[2][j]=str[i];
        j++;
        i++;
    }
    if((*splited_export_char)[2])
        (*splited_export_char)[2][j] = '\0';
}


static char  **split_environ(char *str)
{
    char **splited_export_char;
    int  lengh_of_var_str;
    int lengh_of_var_value;
    
    if(!str)
        return(NULL);

    lengh_of_var_str = count_lengh_var_str_export(str);
    lengh_of_var_value = count_lengh_value_str_export((str + lengh_of_var_str));
    splited_export_char = (char **)malloc(4*sizeof(char *));
    if(!splited_export_char)
        return(NULL);
    splited_export_char[0] =(char *)malloc((size_t)(lengh_of_var_str + 1));
    if(str[lengh_of_var_str] == '=')
        splited_export_char[1] = (char *)malloc((size_t)(2));
    else if(str[lengh_of_var_str] == '+')
        splited_export_char[1] = (char *)malloc((size_t)(3));
    else
    {
        splited_export_char[1] = NULL;
        splited_export_char[2] = NULL;
        fill_in_environ(str,&splited_export_char);
        return(splited_export_char);
    }
    splited_export_char[2]= (char *)malloc((size_t)(lengh_of_var_value + 10));
    splited_export_char[3] = NULL ;
    if(!splited_export_char[0] || !splited_export_char[1] || !splited_export_char[2])
        return(NULL);
    fill_in_environ(str,&splited_export_char);
     return(splited_export_char);
}
t_environ  *ft_lstnew_environ(char *str)
{
	t_environ	*newnode;
    char       **splited_export;

	newnode = (t_environ *)malloc(sizeof(t_environ));
	if (!newnode)
		return (NULL);
    // if(!strcmp(str, ""))
    // {
    //     newnode->var =NULL;
    //     newnode->operator= NULL;
    //     newnode->value= NULL;
    //     newnode->next = NULL;
    // }
    // else
    // {
    splited_export = split_environ(str);
    if(!splited_export)
        return(NULL);
	newnode->var =splited_export[0];
    newnode->operator= splited_export[1];
    newnode->value= splited_export[2];
	newnode->next = NULL;
    return(newnode);
}
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new)
{
	t_environ	*temp;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while ((temp)->next != NULL)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = new;
}

static int is_the_var_in_environ(char *variable, t_environ *environ)
{
    t_environ *current = environ;
   while(current)
   {
       
       if(!strcmp(current->var ,variable))
       {
           return(1);
       }
       current = current->next;
   }
   return(0);
}
// static void replace_node(t_environ **new, t_environ **environ) {
//     t_environ *tmp = *environ;
//     t_environ *prev = NULL; // Keeps track of the previous node
//     char *new_value;

//     while (tmp) {
//         if (!strcmp(tmp->var, (*new)->var)) {
//             // If operator is "+=", concatenate values
//             if (!strcmp((*new)->operator, "+=")) {
//                 new_value = ft_strjoin(tmp->value, (*new)->value, GLOBAL);
//                 if (!new_value)
//                     return; // Exit if memory allocation fails
//                 free((*new)->value); // Free old value of *new
//                 (*new)->value = new_value;
//             }

//             // Update pointers
//             (*new)->next = tmp->next; // New node points to the next of the old one
//             if (prev)
//                 prev->next = *new; // Previous node points to the new one
//             else
//                 *environ = *new; // Update the head of the list if replacing the first node

//             free(tmp); // Free old node
//             return;    // Exit after replacement
//         }
//         prev = tmp;
//         tmp = tmp->next; // Move to the next node
//     }
// }

static void replace_node(t_environ **new, t_environ **environ)
{
    t_environ *tmp;
    t_environ *current;
    
    char *new_value;
    
    tmp = (*environ);
    while(tmp)
    {
        if((tmp->next) && !strcmp((tmp->next)->var, (*new)->var))
        {
            current = tmp;
            // if((tmp->next)->next);
            tmp = (tmp->next)->next;
            if(!strcmp((*new)->operator, "+="))
            {
                new_value = ft_strjoin((current->next)->value, (*new)->value, GLOBAL);
                if(!new_value)
                    return;
                (*new)->value = new_value;
            }
            (*new)->next = tmp;
            current->next = *new;
            break;
        }
        tmp=tmp->next;     
    }
}

static void handling_new_changes(t_environ **new, t_environ **environ)
{
    char *new_value;
    char *new_operator;
    

    if(!((*new)->value))
        return;
    else if(!ft_strcmp((*new)->operator, "+=") && !strcmp((*new)->value,""))
        return;
    replace_node(new, environ); 
}

static void make_export_struct(char **splited_arg, t_environ **environ)
{
    t_environ *new;
    t_environ *current;
    int count ;
    int i;
    
    
    
   (1&& (count = 0), (i = 0 ));
    if(splited_arg)
    {
        while(splited_arg[i])
        {
            new = ft_lstnew_environ(splited_arg[i]);
            if(is_the_var_in_environ(new->var, *environ))
            {
                handling_new_changes(&new, environ);
            }
            else 
            {
                ft_lstadd_back_environ(environ, new);
            }   
            i++;
        }
        // current = *environ;
        // while(current)
        // {
        //     printf("%s\n", current->var);
        //     current= current->next;
        // }  
    }
}
static void input_struct_handling(char *oldpromt, t_environ **environ)
{
    char **splited_arg;
    int var_name_end_;
    int i;
    
    if(!ft_strcmp(oldpromt, ""))
        return;
    else
    {
        splited_arg = cstm_split(oldpromt, " ");
        if(!splited_arg)
            return;
        i = 0;
        while(splited_arg[i])
        {
            var_name_end_=(var_name_end(splited_arg[i]));
            
            if(!valid_var_name(splited_arg[i], var_name_end_))
            {
                printf("syntax error!");
                    return;
            }
            i++;
        }
        make_export_struct(splited_arg, environ);
    } 
}
    
int export_parssing(t_com *command, char *oldpromt, t_environ **environ)
{
    int i;
    
    t_environ *current;
        
    if(command->command)
    {
        start_of_arguments(command,&oldpromt);
        if(valid_position_export(oldpromt))
        {
            input_struct_handling(oldpromt, environ);
            if(environ == NULL)
                printf("oooo\n");
            else 
            {
                // current = *environ;
                // while(current)
                // {
                //     printf("%s", current->var);
                //     if(current->operator)
                //          printf("=");
                //     if(current->value)
                //         printf("\"%s\"",current->value );
                //     printf("\n");
                //     current = current->next;
                // }
                return (1);
            }
        }
        else 
        {
            printf("syntax error!");
            return(0); 
        }          
    }
    return(-1);
}


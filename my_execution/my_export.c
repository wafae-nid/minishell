/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:53:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/16 17:09:29 by wnid-hsa         ###   ########.fr       */
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


// static int allowed_special_char(char c)
// {
//     if(c == '$' || c == '+' || c == '_' || c == '=')
    
// }

// static int valid_name_char(char *str)
// {
//     int i;

//     i = 0;
//     if(!str)
    
//         return(-1);
//     while(str[i])
//     {
// 		if(!(ft_isalpha(str[i]) == 1 || str[i] == '_' || str[i] == '=' || ft_is_a_numb(str[i]))) 
//             return(0);
//         i++;
//     }
//         return(0);
// }
static int var_name_end(char *str) // to know the end of my variable name;
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
    return(0);
}
static int valid_var_name(char *str, int count)
{
    int i;
    i = 0;
    
    if(!str)
        return(-1);
    while(i < count)
    {
        if(!(ft_isalpha(str[i]) == 1 || str[i] == '_' || str[i] == '=' || ft_is_a_numb(str[i]))) 
            return(0);
        if((ft_is_a_numb(str[i])) && i == 0)
            return(0);
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
static void fill_in_export(char *str,char ***splited_export_char)
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
    (*splited_export_char)[1][j]='\0';
    j = 0;
    while(str[i])
    {
        (*splited_export_char)[2][j]=str[i];
        j++;
        i++;
    }
    (*splited_export_char)[2][j] = '\0';
}


static char  **split_export(char *str)
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
    splited_export_char[0] =(char *)malloc((size_t)(count_lengh_var_str + 1));
    if(str[lengh_of_var_str] == '=')
        splited_export_char[1] = (char *)malloc((size_t)(2));
    else if(str[lengh_of_var_str] == '+')
        splited_export_char[1] = (char *)malloc((size_t)(3));
    else
        splited_export_char[1] = (char *)malloc((size_t)(1));
    splited_export_char[2]= (char *)malloc((size_t)(lengh_of_var_value + 1));
    splited_export_char[3] = NULL ;
    if(!splited_export_char[0] || !splited_export_char[1] || !splited_export_char[2])
        return(NULL);
    fill_in_export(str,&splited_export_char);
     return(splited_export_char);
}
static t_export  *ft_lstnew_export( char *str)
{
	t_export	*newnode;
    char       **splited_export;

	newnode = (t_export *)malloc(sizeof(t_export));
	if (!newnode)
		return (NULL);
    if(!strcmp(str, ""))
    {
        newnode->var =ft_strdup("");
        newnode->operator= ft_strdup("");;
        newnode->value= ft_strdup("");
        newnode->next = NULL;
    }
    else
    {
        splited_export = split_export(str);
        if(!splited_export)
            return(NULL);
	    newnode->var =splited_export[0];
        newnode->operator= splited_export[1];
        newnode->value= splited_export[2];
	    newnode->next = NULL;
    }
    return(newnode);
}
static void	ft_lstadd_back_export(t_export **lst, t_export *new)
{
	t_export	*temp;

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


static t_export *make_export_struct(char **splited_arg)
{
    t_export *s_export;
    t_export *new;
    int count ;
    int i;
    
    s_export = NULL;
    count = 0;
    if(splited_arg)
    {
        if(!strcmp(splited_arg[0],""))
        {
            new = ft_lstnew_export((splited_arg[0]));
            ft_lstadd_back_export(&s_export, new);
            return(s_export);
        }
        i = 0;
        while(splited_arg[i])
        {
            // printf("%s\n", splited_arg[i]);
            new = ft_lstnew_export(splited_arg[i]);
            ft_lstadd_back_export(&s_export, new);
            i++;
        }
        return(s_export);
    }
    else 
        return(NULL);
}


int export_parssing(t_com *command, char *oldpromt)
{
    int i;

    int var_name_end_;
    t_export *s_export;
    

    i = 1;
    char **splited_arg;
    if(command->command)
    {
        start_of_arguments(command,&oldpromt);
        // if(ft_strlen(oldpromt) <= 1)
        //
            //  return (1);
        if(valid_position_export(oldpromt))
        {
            if(!ft_strcmp(oldpromt, ""))
                s_export =make_export_struct(&oldpromt);
            else
            {
                splited_arg = cstm_split(oldpromt, " ");
            
                if(!splited_arg)
                {
                    return(-1);
                }
                 i = 0;
                while(splited_arg[i])
                {
                    var_name_end_=(var_name_end(splited_arg[i]));
                    if(!valid_var_name(splited_arg[i], var_name_end_))
                    {
                        printf("syntax error!");
                        return(-1);
                    }
                    i++;
                }
                s_export =make_export_struct(splited_arg);
            }
            while(s_export)
            {
                printf("*****%s****\n", s_export->var);
                printf("#####%s####\n", s_export->operator);
                printf("??????%s?????\n", s_export->value);
                s_export = s_export->next;
            }
        }
        else 
        {
            printf("syntax error!");
            return(0); 
        }          
    }
    else 
        return(-1);
}

// void export_execution(t_com *command ,t_environ *s_environ)
// {
//     if(comand)
// }
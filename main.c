#include "minishell.h"

extern int    g_signal_received;

void    minishell_loop(t_shell *data, char *cmd_line_args, struct termios *term)
{
    char *PWD;
    char *prompt;
    char *old_pompt;

    while (1)
    {
        data->heredoc_index = 0;
        signals_init();
        PWD = getenv("PWD");
        prompt = ft_strjoin_(PWD, "> ");
        cmd_line_args = readline(prompt);       //readline(prompt(data));
        old_pompt = cmd_line_args;
        if (g_signal_received)
            data->exit_status = 1;
        if (!cmd_line_args)
            break ;
        g_signal_received = 0;
        if (set_command(data, cmd_line_args)
            && !is_spaces(cmd_line_args))
        {
            print_command(data->command);
            execution_entery(data->command, PWD, old_pompt);
            // Enter ur execution code here !

        //     if (data->command && data->command->command)
        //     data->exit_status =  wafae_execution(data->command);//ft_execute_command(data);
        }
        // if (cmd_line_args)
        //     add_history(cmd_line_args);
        // free(cmd_line_args);
        // gc_free_all(LOCAL);
        // disable_echoctl(term);
    }
}

int    main(int argc, char *argv[], char **envp)
{
    char            cmd_line_args;
    struct termios    term;
    t_shell            data;
    
    (void)argv;
    (void)argc;
    init_shell_data_config(&data, envp);
    if (isatty(STDIN_FILENO))
    {
        if (tcgetattr(STDIN_FILENO, &term) == -1)
        {
            perror("tcgetattr");
            gc_free_all(LOCAL);
            gc_free_all(GLOBAL);
            exit(EXIT_FAILURE);
        }
    }
    else
        return (ft_printf(2, "Error: Not a TTY\n"), EXIT_FAILURE);
    minishell_loop(&data, &cmd_line_args, &term);
    gc_free_all(GLOBAL);
    gc_free_all(LOCAL);
    return (data.exit_status);
}

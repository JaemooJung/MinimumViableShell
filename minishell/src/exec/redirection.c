#include "minishell.h"

void	keep_stdio(int *origin) // dup errorhandling
{
	origin[0] = dup(STDIN_FILENO);
	origin[1] = dup(STDOUT_FILENO);
}

void restore_stdio(int *origin) // dup errorhandling
{
	dup2(origin[0], STDIN_FILENO);
	dup2(origin[1], STDOUT_FILENO);
}
//argument should include if there is a pipe in mother, original fdarr,
void	run_token(t_list *env) // yesfork
{
	char	**envv;
	int		pipe[2];
	pid_t	pid;

	envv = to_vector(env);
	if (envv == NULL)
		; //dosomething
	// check if there is pipe
//	if (i have to do pipe)
//		if (pipe(pipe) == -1)
//			err!!
	pid = fork();
//	if (pid == -1)
//		err!
	if (pid == 0) // child
	{
//		child_redirection -> STDIN // STDOUT redirect
//		execve(filepath, argv, envv);
	}
	else // mother
	{
//		mom_redirection
		waitpid(pid, 0, 0);
	}
//	free_vector(envv);
//	fd_restore();
}

void	run_builtin(t_list *env) // nofork
{
	int		pipe[2];

	// check if there is pipe
//	do_redirection -> STDIN // STDOUT redirect
//	execve(filepath, argv, envv);
//	free_vector(envv);
}
/* readline doesn't seem to work */
void	here_doc(int infile, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			ft_free_str(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
		ft_free_str(line);
	}
	close(infile);
	infile = open("mvs_temp", O_RDONLY, 0777);
}

typedef struct s_necessities
{
	int		exit_status;
	int		pipe[2];
	int 	fd[2];
	int 	prev_dir;
	char	*remainder;
	char	*fullpath;
	t_list	*env;
}	t_love;

void	do_nothing(void)
{

}

void	lets_pipe(t_love *love)
{
	if (pipe(love->pipe) == -1)
		;//dosomething
	//redir to pipe;
}

void	teach_me_direction(char *content, t_love *love)
{
	if (ft_strncmp(content, "<", 2) == 0)
		love->prev_dir = IN_REDIR;
	else if (ft_strncmp(content, "<<", 3) == 0)
		love->prev_dir = IN_HEREDOC;
	else if (ft_strncmp(content, ">", 2) == 0)
		love->prev_dir = OUT_REDIR;
	else if (ft_strncmp(content, ">>", 3) == 0)
		love->prev_dir = OUT_APPEND;
}

void	join_remainder(char *content, t_love *love)
{
	int 	space_loc;
	char	*temp;

	space_loc = 0;
	while (content[space_loc] != ' ')
		++space_loc;
	temp = love->remainder;
	love->remainder = ft_strjoin(love->remainder, &content[space_loc + 1]);
	if (temp != NULL)
		ft_free_str(temp);
	content[space_loc] = '\0';
}

int	mvs_open(char *file, int mode)
{
	int	fd;

	if (mode == READ)
	{
		fd = open(file, O_RDONLY, 0777);
//		if (fd == -1)
//			error(ERR);
	}
	else if (mode == WRITE)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
//		if (fd == -1)
//			error(ERR);
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
//		if (fd == -1)
//			error(ERR);
	}
	return (fd);
}

void	redir_n_join_remainder(char *content, t_love *love)
{
	int 	fd;

	if (ft_strchr(content, ' ') != NULL)
		join_remainder(content, love);
	if (love->prev_dir == IN_REDIR)
	{
		love->fd[INFILE] = mvs_open(content, READ);
		dup2(love->fd[INFILE], STDIN_FILENO);
	}
	else if (love->prev_dir == IN_HEREDOC)
	{
		love->fd[INFILE] = mvs_open("mvs_temp", WRITE);
		here_doc(love->fd[INFILE], content);
		dup2(love->fd[INFILE], STDIN_FILENO);
	}
	else if (love->prev_dir == OUT_REDIR)
	{
		love->fd[OUTFILE] = mvs_open(content, WRITE);
		dup2(love->fd[OUTFILE], STDOUT_FILENO);
	}
	else if (love->prev_dir == OUT_APPEND)
	{
		love->fd[OUTFILE] = mvs_open(content, APPEND);
		dup2(love->fd[OUTFILE], STDOUT_FILENO);
	}
}

char	*concat_path(char *cmd, t_list *env)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	paths = ft_split(get_value(env, "PATH") + 5, ':');
//	if (paths == 0)
//		error(ERR);
	i = 0;
	while (paths[i] != 0)
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], temp);
		free(temp);
		if (access(path, X_OK) == 0) // access is not allowed!
			return (path);
		++i;
		ft_free_str(path);
	}
	return (0);
}

void	get_fullpath(char *content, t_love *love)
{
	/* have to filter builtins */
	love->fullpath = concat_path(content, love->env);
//	if (love->fullpath == 0)
//		error(ERR);
}

void	lets_exec(char *content, t_love *love)
{
	char	**cmd_splitted;
	char	**envp;
	char 	*temp;
	pid_t	pid;

	temp = content;
	envp = to_vector(love->env);
	content = ft_strjoin(content, love->remainder);
//	if (content == NULL)
//		;
	cmd_splitted = mvs_split(content);

	pid = fork();
	if (pid == 0)
	{
		if (execve(love->fullpath, cmd_splitted, envp) == -1)
			;
//		error(ERR);
	}
	waitpid(pid, NULL, WUNTRACED);
	ft_free_str(love->remainder);
	//have to free cmd_splitted
	/* have to filter builtins */
	/* strjoin love->remainder and free. then split */
	/* have to clear love->remainder in parent proc */
}
/* have to handle errors for ftstrjoins.... */
/* in the function that use search_tree,
 * we need to use keep_stdio and restore_stdio*/
void	execute_tree(t_ast_node *node, t_love *love)
{
	if (node->node_type == NODE_PIPE && node->right != NULL)
		lets_pipe(love);
//	else if (node->node_type == NODE_PHRASE)
//		do_nothing();
//	else if (node->node_type == NODE_REDIRS)
//		do_nothing();
//	else if (node->node_type == NODE_IO_REDIR)
//		do_nothing();
//	else if (node->node_type == NODE_COMMAND)
//		do_nothing();
	else if (node->node_type == NODE_REDIR_TYPE)
		teach_me_direction(node->content, love);
	else if (node->node_type == NODE_FILE_NAME)
		redir_n_join_remainder(node->content, love);
	else if (node->node_type == NODE_FILE_PATH)
		get_fullpath(node->content, love);
	else if (node->node_type == NODE_ARGV)
		lets_exec(node->content, love);
}

void search_tree(t_ast_node *node, t_love *love)
{
	execute_tree(node, love);
	if (node->left != NULL)
		search_tree(node->left, love);
	if (node->right != NULL)
		search_tree(node->right, love);
}

void run_tokens(t_ast_node *node, t_list *env)
{
	int origin[2];
	t_love love;

	love.env = env;
	keep_stdio(origin);
	search_tree(node, &love);
	restore_stdio(origin);
}
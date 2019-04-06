int	execute_ast(t_ast *root)
{
	if (root->type == ';')
	{
		execute_ast(root->left);
		execute_ast(root->right);
	}
	else if (root->type == '&')
	{
		mode_background;
		execute_ast(root->left);
		execute_ast(root->right);
	}
	else if (root->type == "&&")
		return (execute_ast(root->left) && execute_ast(root->right));
	else if (root->type == "||")
		return (execute_ast(root->left) || execute_ast(root->right));
	else
		return (parse_pipeline(root));
}

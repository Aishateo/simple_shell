#include "shell.h"

/**
 * shellFree_info - Frees memory associated with the p_info struct.
 *
 * @info: Pointer to the p_info struct.
 * @all: Flag indicating whether to free all resources.
 * Return: None.
 */
void shellFree_info(p_info *info, int all)
{
	s_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuf)
			free(info->arg);
		if (info->env)
			shellFreeList(&(info->env));
		if (info->history)
			shellFreeList(&(info->history));
		if (info->alias)
			shellFreeList(&(info->alias));
		s_free(info->environ);
			info->environ = NULL;
		p_free((void **)info->cmdBuf);
		if (info->readFD > 2)
			close(info->readFD);
		shell_putchar(BUF_FLUSH);
	}
}

/**
 * shellSet_info - Sets the values of the
 * p_info struct using the command arguments.
 *
 * @info: Pointer to the p_info struct.
 * @av: Array of command arguments.
 * Return: None.
 */
void shellSet_info(p_info *info, char **av)
{
	int it = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splits_strToWrd(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = shell_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (it = 0; info->argv && info->argv[it]; it++)
			;
		info->argc = it;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * shellClear_info - Clears the values of the p_info struct.
 *
 * @info: Pointer to the p_info struct.
 * Return: None.
 */
void shellClear_info(p_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

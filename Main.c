#include "shell_func.h"

/**
 * main - entry point of the project.
 * @ac: argument count
 * @av: argument vector
 * return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	shell_infomat_t infomat[] = { infomat_INIT };
	int f_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f_d)
		: "r" (f_d));

	if (ac == 2)
	{
		f_d = open(av[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				is_eputs(av[0]);
				is_eputs(": 0: Can't open ");
				is_eputs(av[1]);
				is_eput_character('\n');
				is_eput_character(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infomat->read_f_d = f_d;
	}
	increase_env_list(infomat);
	read_history(infomat);
	shell_hash(infomat, av);
	return (EXIT_SUCCESS);
}

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define NICE_FUNCTION 1
#define BAD_FUNCTION 0
#define INTERNAL_ERROR -1

void	alarm_handler(int signum)
{
	(void)signum;
}

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t			pid;
	pid_t			wpid;
	int			wstatus;
	struct sigaction	act;

	act.sa_handler = alarm_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGALRM, &act, NULL) == -1)
	{
		printf("sigaction failed\n");
		return (INTERNAL_ERROR);
	}
	pid = fork();
	if (pid == -1)
	{
		printf("fork failed\n");
		return (INTERNAL_ERROR);
	}
	if (pid == 0)
	{
		f();
		exit(0);
	}
	else
	{
		alarm(timeout);
		wpid = waitpid(pid, &wstatus, 0);
		alarm(0);
		if (wpid == -1)
		{
			if (errno == EINTR)
			{
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
				kill(pid, SIGKILL);
				waitpid(pid, NULL, 0);
				return (BAD_FUNCTION);
			}
			return (INTERNAL_ERROR);
		}
		if (WIFSIGNALED(wstatus))
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(WTERMSIG(wstatus)));
			return (BAD_FUNCTION);
		}
		if (WIFEXITED(wstatus))
		{
			int exit_code = WEXITSTATUS(wstatus);
			if (exit_code != 0)
			{
				if (verbose)
					printf("Bad function: exited with code %d\n", exit_code);
				return (BAD_FUNCTION);
			}
		}
		if (verbose)
			printf("Nice function!\n");
		return (NICE_FUNCTION);
	}
}

/* Test */

void nice_function(void)
{
	for (int i = 0; i < 5; i++)
	{
		printf("Counting: %d\n", i);
		sleep(1);
	}
}

void bf1(void)
{
	printf("This function is about to crash.\n");
	int *ptr = NULL;
	*ptr = 42; // Dereferencing a null pointer
}

void bf2(void)
{
	printf("Infinite loop started...\n");
	while (1) {} // Never stops
}

#include <time.h>

void bf3(void)
{
	srand(time(NULL));
	int behavior = rand() % 3;

	if (behavior == 0)
	{
		printf("I will crash now.\n");
		int *ptr = NULL;
		*ptr = 42; // Cause a crash
	}
	else if (behavior == 1)
	{
		printf("I will loop forever.\n");
		while (1) {} // Infinite loop
	}
	else
	{
		printf("I will exit with a bad code.\n");
		exit(1); // Non-zero exit status
	}
}

int main(void)
{
	printf("Testing nice function 1:\n");
	sandbox(nice_function, 10, true); // fonction, timeout, verbose

	printf("\n\nTesting bad function:\n");
	sandbox(bf1, 3, true);

	printf("\nTesting bad function:\n");
	sandbox(bf2, 3, true);

	printf("\nTesting very bad function:\n");
	sandbox(bf3, 3, true);

	return (0);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include "config.h"

void
kill_process_with_pid (int pid)
{
  kill (pid, SIGTERM);
  printf ("Killed the process with pid : %d\nWho's next?\n", pid);
}

void
terminate (void)
{
  char output[1000][1000];
  char buf[1000];
  int count = 0, random, pid;

  FILE *cmd = popen ("ps -e | tail -n +2", "r");
  if (cmd == NULL)
    {
      perror ("Couldn't kill a process! You got lucky!");
      return;
    }

  while (fgets (buf, 1000, cmd) != NULL)
    {
       buf[strcspn (buf, "\n")] = '\0';
       strcpy (output[count], buf);
       count++;
    }

  random = rand () % count;
  sscanf (output[random], "%d", &pid);
  kill_process_with_pid (pid);

  pclose (cmd);
}

int
main (int   argc,
      char *argv[])
{
  int number, guess, count = 0;

  srand (time (0));
  number = rand () % N_GUESS;

  printf ("Welcome to HitOrKill\n");
  printf ("I have picked up a totally random number between 0 and %d. Can you guess it correct?\n", N_GUESS - 1);
  printf ("For every wrong guess a random process will be removed from the memory\n");

  while (1)
    {
      printf ("(guess) ");
      if (scanf ("%d", &guess) != 1)
        {
	  printf ("Enter a valid guess or init will be killed\n");
	  while (getchar () != '\n');
	  continue;
	}

      if (guess == number)
        {
          printf ("Saved! You got it correct!\n");
	  if (count == 0)
            {
	      printf ("Luckily! No one has sacrificed\n");
	    }
	  else
	    {
	      printf ("%d brave processes were sacrificed for the greater good! RIP\n", count);
	    }
          break;
	}
      else
	{
          terminate();
	  count++;
	}
    }

  return 0;
}

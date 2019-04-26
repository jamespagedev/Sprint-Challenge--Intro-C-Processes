#include <stdio.h>
#include <dirent.h>
#include <errno.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  // pre-condition: all args AFTER argv[1] will be ignored
  // Note: argc is at least 1 for the current file name typed from user.
  // Parse command line
  char *dir;

  // Check Directory is Valid
  if (argc - 1 > 0) // dir was given
  {
    dir = argv[1];
    printf("Directory = %s\n", dir);
    DIR *check_dir = opendir(dir);
    if (ENOENT == errno)
    {
      printf("Directory \"%s\" does not exist\n", dir);
      return 1;
    }
    closedir(check_dir);
  }
  else // no dir given
  {
    dir = ".";
    printf("Directory = %s\n", dir);
    DIR *check_dir = opendir(dir);
    if (ENOENT == errno)
    {
      printf("Your environment is not setup correclty to run this file\n");
      return 1;
    }
    closedir(check_dir);
  }

  // Open directory

  // Repeatly read and print entries

  // Close directory

  return 0;
}
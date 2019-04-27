#include <stdio.h>
#include <dirent.h>   // `DIR`, `struct dirent`, `opendir()`, `readdir()`, and `closedir()`
#include <errno.h>    // ENOENT and errno
#include <string.h>   // `strcpy()`, `strcat()`, and `strcmp()`
#include <sys/stat.h> // `stat()`

void print_dir_details(struct stat item_stat, char *item_name, int dir_level)
{
  if (S_ISREG(item_stat.st_mode)) // item is file
  {
    if (dir_level == 1)
    {
      printf("\t%ld\t\t%s\n", item_stat.st_size, item_name);
    }
    else
    {
      printf("\t\t%ld\t\t%s\n", item_stat.st_size, item_name);
    }
  }
  else if (S_ISDIR(item_stat.st_mode)) // item is dir
  {
    // no need to re-print current dir twice
    if (strcmp(item_name, ".") != 0)
    {
      if (dir_level == 1)
      {
        printf("\t<directory>\t%s\n", item_name);
      }
      else
      {
        printf("\t\t<directory>\t%s\n", item_name);
      }
    }
  }
}

void print_dirs(char *orig_dir, char *curr_dir, int dir_level)
{
  printf("Directory = \"%s\"\n", curr_dir);
  // Open directory
  DIR *dir_details = opendir(curr_dir);
  struct dirent *dir_item;

  // Print items in directories
  while ((dir_item = readdir(dir_details)) != NULL)
  {
    // deconstruct item name for more readable code
    char *item_name = dir_item->d_name;

    // required dir\filename for stat()
    char dir_with_item[strlen(orig_dir) + strlen(item_name)];
    strcpy(dir_with_item, orig_dir);
    strcat(dir_with_item, "\\");
    strcat(dir_with_item, item_name);

    // setup item info
    struct stat item_stat;
    stat(dir_with_item, &item_stat);
    print_dir_details(item_stat, item_name, dir_level);
    // prints out weird, can't figure this "stretch" recursion out
    // if (dir_level == 1)
    // {
    //   printf("\n");
    //   if (S_ISREG(item_stat.st_mode))
    //   {
    //     print_dirs(orig_dir, item_name, 2); // 2 is for child directory
    //   }
    //   else if (S_ISDIR(item_stat.st_mode)) // item is dir
    //   {
    //     print_dirs(orig_dir, dir_with_item, 2); // 2 is for child directory
    //   }
    // }
  }

  // Close directory
  closedir(dir_details);
}

/**
 * Main
 */
int main(int argc, char **argv)
{
  // pre-condition: all args AFTER argv[1] will be ignored
  // Note: argc is at least 1 for the current file name typed from user.
  // Parse command line
  char *orig_dir;
  char *curr_dir;
  int dir_level = 1;

  // Check Directory is Valid
  if (argc - 1 > 0) // dir was given
  {
    orig_dir = argv[1];
    curr_dir = argv[1];
    DIR *check_dir = opendir(curr_dir);
    if (ENOENT == errno)
    {
      printf("Directory \"%s\" does not exist\n", curr_dir);
      return 1;
    }
    closedir(check_dir);
  }
  else // no dir given
  {
    orig_dir = ".";
    curr_dir = ".";
    DIR *check_dir = opendir(curr_dir);
    if (ENOENT == errno)
    {
      printf("Your environment is not setup correclty to run this file\n");
      return 1;
    }
    closedir(check_dir);
  }

  // Repeatly read and print entries
  print_dirs(orig_dir, curr_dir, dir_level);

  return 0;
}
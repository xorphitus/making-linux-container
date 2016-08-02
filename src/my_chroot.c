#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#define PATHNAME_SIZE 512

void show_dir(char *dirname) {
  struct dirent **namelist;
  int r = scandir(dirname, &namelist, NULL, NULL);
  if (r == -1) {
    exit(1);
  }

  printf("--- list files in directory '%s' ---\n", dirname);
  for (int i = 0; i < r; i++) {
    printf("%s\n", namelist[i]->d_name);
  }
}

int main(int argc, char *argv[]) {
  show_dir("/");

  char current_path[PATHNAME_SIZE];
  getcwd(current_path, sizeof current_path);

  printf("\nchange root to '%s'\n\n", current_path);

  int r = chroot(current_path);

  if (r == -1) {
    printf("chroot failed");
    exit(1);
  } else {
    show_dir("/");
    exit(0);
  }
}

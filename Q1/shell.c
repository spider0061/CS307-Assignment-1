/* 
  Header files import.
*/
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/* 
  Shell Variables and definations.
*/
#define BUFFER_SIZE 64
#define DELIMITER " \t\r\n\a"
extern char **environ;
char pwd_environ[2000];
char environment[2000];
char shell_hist_file[2000];

/*
  Declaration of shell functions.
*/
int shell_cd(char **args);
int shell_help(char **args);
int shell_dir(char **args);
int shell_quit(char **args);
int shell_clr(char **args);
int shell_pause(char **args);
int shell_echo(char **args);
int shell_environ(char **args);
int shell_history(char **args);

/*
  Commands which shell support.
*/
char *command_list[] = {
  "cd",
  "help",
  "dir",
  "quit",
  "clr",
  "pause",
  "echo",
  "environ",
  "history"
};

/* 
  Respective functions for commands array.
*/
int (*command_functions[]) (char **) = {
  &shell_cd,
  &shell_help,
  &shell_dir,
  &shell_quit,
  &shell_clr,
  &shell_pause,
  &shell_echo,
  &shell_environ,
  &shell_history,
};

/*
  Return total number of commands
*/
int total_commands() {
  return sizeof(command_list) / sizeof(char *);
}

/* 
  Function defination to execute cd command.
*/
int shell_cd(char **args)
{
  if (args[1] == NULL) {
    printf("%s\n",pwd_environ );
  } else {
    if (chdir(args[1]) != 0) {
      perror("C shell");
    }
  }
  FILE *f = popen("pwd", "r");
  while (fgets(pwd_environ, 2000, f) != NULL);
  pclose(f);
  pwd_environ[strcspn(pwd_environ, "\n")] = 0;
  return 1;
}

/* 
  Function defination to execute help command.
*/
int shell_help(char **args)
{
  printf("   Welcome to C Shell:\n\n");
  printf("   The shell supports following commands:\n");
  printf("   > clr: To clear the screen.\n");
  printf("   > pause: To pause operations of shell until ENTER is pressed.\n");
  printf("   > help: To show the help menu.\n");
  printf("   > quit / Ctrl+D: To quit the shell.\n");
  printf("   > history: To print all the  previous commands used in the shell.\n");
  printf("   > cd <directory>: To move to <directory>. If the directory is not present it will out current address.\n");
  printf("   > dir <directory>: To list the contents of <directory>.\n");
  printf("   > environ: To print environment variables of bash and current shell.\n");
  printf("   > echo <comment>: To print <comment> on screen.\n");
  return 1;
}

/* 
  Function defination to execute help command.
*/
int shell_dir(char **args)
{
  if(args[1]==NULL) {
    printf("No directory entered.\n");
  }
  else {
    char str[2000]="dir ";
    strcat(str,args[1]);
    system(str);
  }
  return 1;
}

/* 
  Function defination to execute quit command.
*/
int shell_quit(char **args)
{
  return 0;
}

/* 
  Function defination to execute clr command.
*/
int shell_clr(char **args)
{
  printf("\033[H\033[J");
  return 1;
}

/* 
  Function defination to execute pause command.
*/
int shell_pause(char **args)
{
  char ch;
  printf("System is paused. Press Enter: ");
  while(1)
  {
    ch=fgetc(stdin);
    
    if(ch==0x0A)
    {
      break;
    }
    else
    {
      printf("System is paused. Press Enter: ");
    }
    ch=getchar();
  }
  return 1;
}

/* 
  Function defination to execute echo command.
*/
int shell_echo(char **args)
{
  printf("%s\n",args[1]);
  return 1;
}

/* 
  Function defination to execute environ command.
*/
int shell_environ(char **args)
{
  int i = 1;
  char *s = *environ;
  printf("Bash environment variables:\n\n");
  for (; s; i++) {
    printf("%s\n", s);
    s = *(environ+i);
  }
  printf("\n");
  printf("C shell environment variables\n\n");
  printf("ENVIRONMENT: %s\n", environment);
  printf("PWD: %s\n", pwd_environ);
  return 1;
}

/* 
  Function defination to execute history command.
*/
int shell_history(char **args)
{
  FILE* filePointer;
  int bufferLength = 255;
  char buffer[bufferLength];
  filePointer = fopen(shell_hist_file, "r");
  while(fgets(buffer, bufferLength, filePointer)) {
      buffer[strcspn(buffer, "\n")] = 0;
      printf("%s\n", buffer);
  }
  return 1;
}

/* 
  Executes the command.
*/
int wrong_command(char **args)
{
  printf("Enter a valid command\n");
  return 1;
}

/* 
  Finds the appropriate function for entered command and executes it.
*/
int exe(char **args)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < total_commands(); i++) {
    if (strcmp(args[0], command_list[i]) == 0) {
      return (*command_functions[i])(args);
    }
  }

  return wrong_command(args);
}

/* 
  Function defination to take input.
*/
char *input(void)
{
  #ifdef LSH_USE_STD_GETLINE
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us
    if (getline(&line, &bufsize, stdin) == -1) {
      if (feof(stdin)) {
        exit(EXIT_SUCCESS);  // We received an EOF
      } else  {
        perror("error\n");
        exit(EXIT_FAILURE);
      }
    }
    return line;
  #else
  #define BUF_SIZE 1024
    int bufsize = BUF_SIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
      fprintf(stderr, "allocation error\n");
      exit(EXIT_FAILURE);
    }

    while (1) {
      c = getchar();

      if (c == EOF) {
        exit(EXIT_SUCCESS);
      } else if (c == '\n') {
        buffer[position] = '\0';
        return buffer;
      } else {
        buffer[position] = c;
      }
      position++;

      if (position >= bufsize) {
        bufsize += BUF_SIZE;
        buffer = realloc(buffer, bufsize);
        if (!buffer) {
          fprintf(stderr, "allocation error\n");
          exit(EXIT_FAILURE);
        }
      }
    }
  #endif
}

/* 
  Function defination to split the given input.
*/
char **tokenizer(char *line)
{
  int bufsize = BUFFER_SIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, DELIMITER);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += BUFFER_SIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, DELIMITER);
  }
  tokens[position] = NULL;
  return tokens;
}

/* 
  Main Function 
*/
int main(int argc, char **argv)
{

  /*
    To set C shell variables.
  */
  char str1[2000]="shell=";
  char str2[2000]="/shell.c=myshell";
  FILE *f = popen("pwd", "r");
  while (fgets(environment, 2000, f) != NULL);
  pclose(f); 
  environment[strcspn(environment, "\n")] = 0;
  strcpy(pwd_environ,environment);
  strcpy(shell_hist_file,environment);
  strcat(str1,environment);
  strcat(str1,str2); 
  strcpy(environment,str1);
  strcat(shell_hist_file,"/history.txt");

  /*
    Check if an input batch file is entered.
  */

  /*
    If batch file is entered then read commands from it and execute them.
  */
  if(argv[1]!=NULL) {
    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen(argv[1], "r");
    if(filePointer==NULL);
    else {
      char *line;
      char **args;
      int status;
      while (fgets(buffer, bufferLength, filePointer)) {
        buffer[strcspn(buffer, "\n")] = 0;
        line=buffer;
        args = tokenizer(line);
        status = exe(args);
        if(!status)
          break;
      }
      fclose(filePointer);
    }
  }

  /*
    Else let the user enter commands.
  */
  else {
    char *line;
    char **args;
    int status;
    do {
      char comd[50];
      printf("~%s$ ",pwd_environ);
      line = input();
      strcpy(comd,line);
      strcat(comd,"\n");
      FILE *fptr;
      fptr = fopen(shell_hist_file, "a");
      fprintf(fptr, "%s", comd);
      fclose(fptr);
      args = tokenizer(line);
      status = exe(args);
      free(line);
      free(args);
    } while (status);
  }

  /*
    Return 0 upon succesful termination.
  */
  return 0;
}

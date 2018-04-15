/**
 * @file    main.c
 * @author  Wojtek Węclewski <w.weclewski@protonmail.com>
 * @date    April, 2018
 * @brief   Simple example of Linux daemon
 *
 * Daemon checks periodically if there are any new saved changes in projects (list_of_projects.cfg file) and backup these changes in configured path.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

#define LOG_ERROR 1
#define CFG_ERROR 2

int main(void) {

  pid_t pid, sid;
  FILE *pLog, *pConf;
  time_t timestamp;

  pid = fork();
  if (pid < 0){
    exit(EXIT_FAILURE);
  }
  if (pid > 0){
    exit(EXIT_SUCCESS);
  }

  umask(0);

  pLog = fopen("simple_daemon.log", "w");
  if (pLog == NULL){
    exit(EXIT_FAILURE);
    return LOG_ERROR;
  }

  pConf = fopen("list_of_projects.cfg", "r");
  if (pConf == NULL){
    exit(EXIT_FAILURE);
    return CFG_ERROR;
  }

  sid = setsid();
  if (sid < 0){
    fprintf(pLog, "Can't set session ID\n");
    fflush(pLog);
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    fprintf(pLog, "Can't set working directory to /root \n");
    fflush(pLog);
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1){
    timestamp = time(0);
    /*printf("Heartbeat: %ld\n", timestamp);*/
    fprintf(pLog, "Heartbeat: %ld\n", timestamp);
    fflush(pLog);

    sleep(30);
  }
  fclose(pConf);
  fclose(pLog);
  exit(EXIT_SUCCESS);

  return 0;
}


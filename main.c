/**
 * @file    main.c
 * @author  Wojtek Węclewski <w.weclewski@protonmail.com>
 * @date    April, 2018
 * @brief   Simple example of Linux daemon
 *
 * Description
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

int main(void) {

  pid_t pid, sid;
  FILE *pLog;
  time_t timestamp;

  pid = fork();
  if (pid < 0){
    exit(EXIT_FAILURE);
  }
  if (pid > 0){
    exit(EXIT_SUCCESS);
  }

  umask(0);

  pLog = fopen("simple_daemon.log", "a");
  if (pLog == NULL){
    exit(EXIT_FAILURE);
  }

  sid = setsid();
  if (sid < 0){
    fprintf(pLog, "Can't set session ID\n");
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    [>fprintf(pLog, "Can't set working directory to /root \n");<]
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1){
    timestamp = time(0);
    /*printf("Heartbeat: %ld\n", timestamp);*/
    fprintf(pLog, "Heartbeat: %ld\n", timestamp);

    sleep(30);
  }
  fclose(pLog);
  exit(EXIT_SUCCESS);
}


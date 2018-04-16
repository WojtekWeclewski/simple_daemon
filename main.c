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

#define MAIN_LOG_FILE "simple_daemon.log"
#define CFG_ERROR 2

void write_log(char *file_name, char *message){
  FILE *pLog = fopen(file_name, "a");
  time_t timestamp = time(0);

  if (pLog == NULL){
    exit(EXIT_FAILURE);
    return;
  }
  fprintf(pLog, "TIME: %ld: %s\n", timestamp, message);
  /*fflush(pLog);*/
  fclose(pLog);
}

int main(void) {
  pid_t pid, sid;
  FILE *pConf;

  pid = fork();
  if (pid < 0){
    exit(EXIT_FAILURE);
  }
  if (pid > 0){
    exit(EXIT_SUCCESS);
  }

  umask(0);

  pConf = fopen("list_of_projects.cfg", "r");
  if (pConf == NULL){
    write_log(MAIN_LOG_FILE, "Can't find list_of_projects.cfg file");
    exit(EXIT_FAILURE);
    return CFG_ERROR;
  }

  sid = setsid();
  if (sid < 0){
    write_log(MAIN_LOG_FILE, "Can't set session ID");
    exit(EXIT_FAILURE);
  }

  /*if ((chdir("/")) < 0){*/
    /*write_log(MAIN_LOG_FILE, "Can't set working directory to /root");*/
    /*exit(EXIT_FAILURE);*/
  /*}*/

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1){
    //diff -qNr dir1/ dir2/ > project_name_diff.log
    write_log(MAIN_LOG_FILE, "HEARTBEAT");

    sleep(30);
  }
  fclose(pConf);
  exit(EXIT_SUCCESS);

  return 0;
}


#ifndef DEF_HANDLERS_SERV
#define DEF_HANDLERS_SERV
//#include "serv_cli_fifo.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


void hand_reveil (int sig);
void fin_serveur (int sig);

#endif
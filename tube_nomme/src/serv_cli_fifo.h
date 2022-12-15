#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define NMAX 10
#define f1 "fifo1"
#define f2 "fifo2"

struct Question {   
  int Num;
  int n;
};

struct Reponse {   
  int NumServeur;
  int tab[NMAX];
};
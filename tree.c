#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <string.h>

#define WHITE  "\e[0m"
#define BLUE  "\x1B[36m"

void sizinga(int i,char**p) {
  if(i){
    sizinga(i>>10,p+1);
    if(i&1023)printf("%d %s ",i&1023,*p);
  }
}

int dirinfo(char* name){
  DIR*root=opendir(name);
  struct dirent* cur;
  while(cur=readdir(root)){
    printf("%s%s\n", (cur->d_type&DT_DIR)?BLUE:WHITE, cur->d_name);
  }
  return 0;
}


int main(){

  dirinfo(".");
  /*printf("Looking at: %s\n", filename);
    char* suffixes[7] = {"bytes","kilobytes","megabytes","gigabytes","terabytes","petabytes","exabytes", "zettabytes", "yottabytes", "brontobytes", "gegobytes"};
    int logp = log(garbagefile->st_size)/log(1024);
    printf("\nSize of the file is:%.1f %s\n",garbagefile->st_size/pow(1024,logp),suffixes[logp]);
    printf("Exact file size (for larger files) is ");
    sizinga(garbagefile->st_size,suffixes);
    printf("\n\nFile permissions: ");
    char*perms="-xwrxwrxwr";
    printf("%c",garbagefile->st_mode&S_IFDIR?'d':'-');
    for(int i=10;--i;)printf("%c",perms[i*(garbagefile->st_mode*2>>i&1)]);
    printf("\n\nLast time of access: %s\n",ctime(&(garbagefile->st_atime))); */
    return 0;
}

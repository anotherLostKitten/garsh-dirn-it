#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <dirent.h>
#include <string.h>

#define WHITE "\e[0m"
#define BLUE "\e[96m"
#define GREEN "\e[92m"
#define PERMS "-xwrxwrxwr"
void sizinga(int i,char**p) {
  if(i){
    sizinga(i>>10,p+1);
    if(i&1023)printf("%d %s ",i&1023,*p);
  }
}
void dirinfo(char*name,int depth){
  DIR*root=opendir(name);
  struct stat*inf=malloc(sizeof(struct stat));
  int ep=strlen(name);
  name[ep++]='/';
  for(struct dirent*cur;cur=readdir(root);){
    if(*cur->d_name=='.')
      continue;
    strcpy(name+ep,cur->d_name);
    stat(name,inf);
    if(cur->d_type&DT_DIR){
      printf("d");
      for(int i=10;--i;)printf("%c",PERMS[i*(inf->st_mode*2>>i&1)]);
      printf(" +");
      for(int i=0;i<=depth;i++)printf("--");
      printf("%s%s/%s\n",BLUE,cur->d_name,WHITE);
      dirinfo(name, depth+1);
    } else {
      printf("-");
      for(int i=10;--i;)printf("%c",PERMS[i*(inf->st_mode*2>>i&1)]);
      printf(" +");
      for(int i=0;i<=depth;i++)printf("--");
      printf("%s%s%s\n",(inf->st_mode&64)?GREEN:WHITE,cur->d_name,WHITE);
    } 
  }
  free(inf);
}


int main(){
  char name[256]=".";
  dirinfo(name, 0);
  /*
  printf("Looking at: %s\n", filename);
  char* suffixes[7] = {"bytes","kilobytes","megabytes","gigabytes","terabytes","petabytes","exabytes", "zettabytes", "yottabytes", "brontobytes", "gegobytes"};
  int logp = log(garbagefile->st_size)/log(1024);
  printf("\nSize of the file is:%.1f %s\n",garbagefile->st_size/pow(1024,logp),suffixes[logp]);
  printf("Exact file size (for larger files) is ");
  sizinga(garbagefile->st_size,suffixes);
  printf("\n\nLast time of access: %s\n",ctime(&(garbagefile->st_atime)));
  */

  return 0;
}

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
#define PREFIXES "?KMGT"

void sizinga(int s){
  if (s>=1024) {
    char logp = log(s)/log(1024);
    printf("[%.1f%cB]\n",s/pow(1024,logp),PREFIXES[logp]);
  }else
    printf("[%dB]\n",s);
}
void perminga(int p){
    printf("%c",p&S_IFDIR?'d':'-');
    for(int i=10;--i;)printf("%c",PERMS[i*(p*2>>i&1)]);
}
void treeinga(char d,char e){
  for(int i=d;i--;)printf("\u2502  ");
  printf("%s\u2500\u2500 ",e?"\u251C":"\u2514");
}
int dirinfo(char*name,int depth){
  DIR*root=opendir(name);
  struct stat*inf=malloc(sizeof(struct stat));
  int ep=strlen(name),dirsize=0;
  name[ep++]='/';
  for(struct dirent*cur;cur=readdir(root);){
    if(*cur->d_name=='.')
      continue;
    strcpy(name+ep,cur->d_name);
    stat(name,inf);
    perminga(inf->st_mode);
    treeinga(depth,1);
    if(cur->d_type&DT_DIR){
      printf("%s%s%s/\n",BLUE,cur->d_name,WHITE);
      dirsize+=dirinfo(name,depth+1);
    }else{
      printf("%s%s%s%s ",inf->st_mode&64?GREEN:WHITE,cur->d_name,WHITE,inf->st_mode&64?"* ":" ");
      sizinga(inf->st_size);
      dirsize+=inf->st_size;
    }
    
  }
  free(inf);
  printf(" dir size:");
  treeinga(depth,0);
  sizinga(dirsize);
  return dirsize;
}


int main(){
  char name[256]=".";
  dirinfo(name, 0);
  /*
  printf("Looking at: %s\n", filename);
  int logp = log(garbagefile->st_size)/log(1024);
  printf("Exact file size (for larger files) is ");
  sizinga(garbagefile->st_size,suffixes);
  printf("\n\nLast time of access: %s\n",ctime(&(garbagefile->st_atime)));
  */

  return 0;
}

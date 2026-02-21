#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
   if(argc<3)
   {
      printf("insufficient value.\n");
      return 1;
   }
   FILE *fp1=fopen(argv[2],"r");
   if (fp1==NULL)
   {
      printf("error in opening file1.\n");
      return 1;
   }
   char line[1024];
   char *word=argv[1];
   while(fgets(line,sizeof(line),fp1))
   {
      if(strstr(line,word)!=NULL)
      {
         printf("%s",line);
      }
   }
   fclose(fp1);
   return 0;
}

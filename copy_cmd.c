#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
   if(argc!=3)
   {
      printf("Insufficent argument");
      return 1;
   }
   char ch;
   FILE *fp1,*fp2;
   fp1=fopen(argv[1],"r");
   if(fp1==NULL)
   {
      printf("Error in opening the file");
      return 1;
   }
   fp2=fopen(argv[2],"w");
   if(fp2==NULL)
   {
      printf("Error in opening the file");
      return 1;
   }
   while((ch=fgetc(fp1))!=EOF)
   {
      fputc(ch,fp2);
   }
   fclose(fp1);
   fclose(fp2);
   printf("Copied successfullyi\n");
   /*if(remove(argv[1])==0)
   {
      printf("destroyed successfully\n");
   }
   else
   {
      printf("not deleted");
   }*/
   return 0;
}

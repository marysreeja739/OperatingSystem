#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
   FILE *fp1,*fp2;
   char ch;
   if(argc==2)
   {
      fp1=fopen(argv[1],"r");
      if(fp1==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      while((ch=fgetc(fp1))!=EOF)
      {
         printf("%c",ch);
      }
      fclose(fp1);
   }
   else if(argc==3)
   {
      fp1=fopen(argv[1],"r");
      if(fp1==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      while((ch=fgetc(fp1))!=EOF)
      {
         printf("%c",ch);
      }
      printf("\n");
      fclose(fp1);
      fp1=fopen(argv[2],"r");
      if(fp1==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      while((ch=fgetc(fp1))!=EOF)
      {
         printf("%c",ch);
      }
      fclose(fp1);
   }
   else if(argc==4 && argv[2]==">")
   {
      //printf("Insufficent arguments");
      //return 1;
     //FILE *fp1,*fp2;
      fp1=fopen(argv[1],"r");
      if(fp1==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      fp2=fopen(argv[3],"w");
      if(fp2==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      char ch;
      while((ch=fgetc(fp1))!=EOF)
      {
         fputc(ch,fp2);
      }
      fclose(fp1);
      fclose(fp2);
   }
   else if(argc==4 && argv[2]==">>")
   {
      //printf("Insufficent arguments");
      //return 1;
      //FILE *fp1,*fp2;
      fp1=fopen(argv[1],"r");
      if(fp1==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      fp2=fopen(argv[3],"a");
      if(fp2==NULL)
      {
         printf("Error in opening the file");
         return 1;
      }
      char ch;
      while((ch=fgetc(fp1))!=EOF)
      {
         fputc(ch,fp2);
      }
      fclose(fp1);
      fclose(fp2);
   }
   else
   {
      printf("Insufficient value");
   }
   return 0;
}

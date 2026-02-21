#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
   pid_t a,b,c,d,e,f,g,h;
   a=fork();
   if(a>0)
   {
      printf("Process 1:%d\n",getpid());
   }
   else if(a==0)
   {
      printf("Praent:%d\n",getppid());
      printf("Process 2:%d\n",getpid());
      //pid_t b,c;
      b=fork();
      if(b==0)
         printf("Process 3:%d parent:%d\n",getpid(),getppid());
      c=fork();
      if(c==0&&a==0&&b>0)
      {
         printf("Process 4:%d\n",getpid());
      }
      /*else if(c>0&&b==0)
      {
         //printf("parent:%d\n",getpid());
         if(b==0&&c==0)
         {
            printf("parent:%d\n",getppid());
            pid_t x=getpid();
            printf("Process 5:%d\n",x);
         }
      }*/
      if(b==0&&c==0)
      {
         printf("Process 5:%d\n",getpid());
      }
      if(c>0&&b==0||c==0&&a==0&&b>0)
      {
         d=fork();
         if(c>0&&b==0&&d==0)
         {
            printf("Process 6:%d\n",getpid());
         }
         else if(c==0&&a==0&&b>0&&d==0)
         {
            printf("Process 7:%d\n",getpid());
            e=fork();
            if(e==0)
            {
               printf("Process 8:%d\n",getpid());
            }
            f=fork();
            if(d==0&&c==0&&a==0&&b>0&&e>0&&f==0)
            {
               printf("Process 9:%d\n",getpid());
               g=fork();
               if(g==0)
               {
                  printf("Process 11:%d\n",getpid());
               }
               h=fork();
               if(h==0&&d==0&&c==0&&a==0&&b>0&&e>0&&f==0&&g>0)
               {
                  printf("Process 12:%d\n",getpid());
               }
               if(g==0&&h>0)
               {
                  if(g==0&&h==0)
                  {
                     printf("Process 13:%d\n",getpid());
                  }
               }
            }
         }
      }
   }
   if(e==0&&f==0)
   {
      printf("Process 10:%d\n",getpid());
   }
   if(g==0&&h==0)
   {
      printf("Process 13:%d\n",getpid());
   }
}

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc,char* argv[])
{
  if(argc!=2)
    {
      fprintf(stderr,"Too few or many arguments..");
      return EXIT_FAILURE;
    }
  FILE* f=fopen(argv[1],"r");
  if(f==NULL)
    {
      fprintf(stderr,"\nFile %s does not exist...",argv[1]);
      return EXIT_FAILURE;
    }
  int c;
  long arr[26]={0};
  while((c=fgetc(f))!=EOF)
    {
      if(!isalpha(c))
	continue;
      c=tolower(c);
      arr[c-97]++;
    }
  long max=0;
  for(int i=0;i<26;i++)
    if(arr[max]<arr[i])
      max=i;
  max=(max+22)%26;
  printf("%ld\n",max);
  if(fclose(f) != 0)
    {
      fprintf(stderr,"Failed to close the input file!\n");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

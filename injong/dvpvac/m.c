#include "m.h"

int main(int argc,char *argv[])
{
  unsigned char buffer[16];
  int i=0,j=0;
  int size;
  int length=0;

  printf("%s\n",argv[1]);
  printf("%s\n", argv[2]);

  FILE *fp = fopen(argv[1], "rb");
  FILE *fp_s = fopen(argv[2], "wb");
  FILE *fp_d = fopen(argv[3], "wb");

  fseek(fp,0,SEEK_END);
  size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  printf("file name : %s \nfile size : %d \n\r", argv[1] ,size);

  rwbuf_f(fp ,fp_s, fp_d, size, buffer);
  
  fclose(fp);    
  fclose(fp_s);
  fclose(fp_d);

  return 0;
}  
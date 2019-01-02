/*
 unix2dos.c

 convert unix file format to dos text file format

 */

#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[])
{
  FILE *fin, *fout;
  char buf[256+1];
  int line;

  fprintf(stderr, "Unix to Dos file format Convertor Ver 1.00    Copyleft(C) 1993 Rock\n");
  if(argc != 3) {
    fprintf(stderr, "Usage : unix2dos source_file_name destination_file_name\n");
    return;
  }
  if(!strcmp(argv[1], argv[2])) {
    fprintf(stderr, "Duplicated source and destination file name...\n");
    return;
  }
  fin = fopen(argv[1], "r");
  if(fin == NULL) {
    fprintf(stderr, "File open Error : %s\n", strupr(argv[1]));
    return;
  }
  fout = fopen(argv[2], "w");
  if(fout == NULL) {
    fprintf(stderr, "File open Error : %s\n", strupr(argv[2]));
    return;
  }

  line = 0;
  while ( 1) {
    fgets(buf, 256, fin);
    if(feof(fin))
      break;
    fputs(buf, fout);
    line++;
    fprintf(stderr, "Line No : %d\r", line);
  }
  fclose(fin);
  fclose(fout);
  fprintf(stderr, "\nSuccessfully Done.......");
}



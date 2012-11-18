#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define DATA_TYPE float
#define DATA_SIZE sizeof(float)

int main(int argc, char **argv)
{
  bool output_switch;  
  char *input_file_name;
  char *output_file_name;
  FILE *fp;
  int  rows, cols, b_size, c_size;
  int  i, offset;
  DATA_TYPE *data_buf;
  DATA_TYPE **a, *b, *c;

  
  
  /* resolve the input arguments */
  if (argc < 2){
      printf("Error! the number of arguments is less(%d)!\n", argc);
      system("pause");
      return 0;
  }
  input_file_name = argv[1]; // get input file name

  output_switch = false;     // output results or not 
  if (argc > 2) {	    
      output_switch = true;
      output_file_name = argv[2];
    }
    
  if ((fp = fopen(input_file_name, "rb")) == NULL){
     return 0;
  }
  
  fread(&rows, sizeof(int), 1, fp);
  fread(&cols, sizeof(int), 1, fp);
  b_size = cols;
  c_size = rows;
  data_buf = new DATA_TYPE[rows*cols];
  a = new DATA_TYPE *[rows]; 
  b = new DATA_TYPE[b_size];
  c = new DATA_TYPE[c_size];
  
  memset(data_buf, 0, DATA_SIZE*rows*cols);
  memset(b, 0, DATA_SIZE*b_size);
  memset(c, 0, DATA_SIZE*c_size);
  fread(data_buf, DATA_SIZE, rows*cols, fp);
  fread(b, DATA_SIZE, b_size, fp);
  fclose(fp);
  printf("file: %s can not be opened \n", input_file_name);
    system("pause");
 
  for (i = 0, offset = 0; i < rows; i ++, offset+=cols)
      a[i] = data_buf+offset;

  /* your homework programming */
  


  /* output results */ 
  if (output_switch){
      if ((fp = fopen(output_file_name, "wb")) == NULL){
	printf("file: %s can not be opened \n", output_file_name);
	system("pause");
	return 0;
      }
      fwrite(c, DATA_SIZE, c_size, fp);
      fclose(fp); 
  }
   
  return 0;
}

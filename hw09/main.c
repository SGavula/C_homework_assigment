#include <stdio.h>

int main()
{
  // data array to store one million numbers
  int data[10];

  // write one million numbers to the data array
  for (int i = 0; i < 10; i++)
    data[i] = i + 1;

  // file pointer for binary file
  FILE *file;

  // open the binary file file.bin in write mode using "wb"
  file = fopen("file.bin", "wb");

  // check if the file failed to open, exit if so
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }


  fwrite(data, sizeof(int), 1, file);

  // close our access to the file
  fclose(file);
  
  return 0;
}
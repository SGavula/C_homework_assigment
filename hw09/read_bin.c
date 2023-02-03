#include <stdio.h>

int main()
{
  // data array to store one million numbers
  int data[10];

  // file pointer for binary file
  FILE *file;

  // open the binary file file.bin in read mode using "rb"
  file = fopen("file.bin", "rb");

  // check if the file failed to open, exit if so
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }

  // ready the entire contents of the file to the data array
  fread(data, sizeof(data), 1, file);

  for(int i = 0; i < 10; i++) {
    printf("%i\n", data[i]);
  }

  // close our access to the file
  fclose(file);

  return 0;
}
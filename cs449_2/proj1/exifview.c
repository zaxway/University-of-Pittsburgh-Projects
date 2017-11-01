#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned short tagIdentifier;
  unsigned short dataType;
  unsigned int numberOfDataItems;
  unsigned int offsetOfDataItems;
} TiffTag;

typedef struct {
  unsigned short startOfFile;
  unsigned short marker;
  unsigned short lengthOfBlock;
  char exifString[4];
  unsigned short zeroTerminator;
  char startOfTiff[2];
  unsigned short version;
  unsigned int offsetForExif;
} Exif;


int main(int argc, char* argv[]) {
  /* Major variables*/
  FILE* f;
  Exif header;
  /*opens the file and reads the header*/
  f = fopen(argv[1], "rb");
  fread(&header, sizeof(header), 1, f);

  /*checker*/
  if(header.startOfFile != 0xD8FF) {
    printf("Error: invalid start of file!\n");
    exit(1);
  }
  if (header.marker != 0xE1FF) {
    printf("Error!\n");
    exit(1);
  }
  else if (strcmp(header.exifString, "Exif") == 1) {
    printf("Error! tag was not found!!\n");
    exit(1);
  }
  else if (header.zeroTerminator != 0x0000) {
    printf("Error!\n");
    exit(1);
  }
  else if (header.startOfTiff[0] != 'I') {
    printf("Error! We do not support this endianess!!\n");
    exit(1);
  }

  /* make a count (2 bytes) */
  unsigned short count;

  /* read the count. This tells us how many tags there are in total!!!! */
  fread(&count, sizeof(count), 1, f);
  /* initialize Tag*/
  TiffTag tiff;
  /* Variables associated with for loop */
  int i;
  int save;
  char buffer[100];
  int save2;
  unsigned short block;


  /*for loop for traversing through tags!!*/

  for (i = 0; i < count; i++) {
    /* every iteration, read new tag*/
    fread(&tiff, sizeof(tiff), 1, f);
    save = ftell(f);
    /* If you read a manufacturer string...*/
    if(tiff.tagIdentifier == 0x010F) {
      fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
      fread(&buffer, sizeof(buffer[0]), tiff.numberOfDataItems, f);
      printf("Manufacturer:\t%s\n", buffer);
    }
    /* Model string  */
    else if (tiff.tagIdentifier == 0x0110) {
      fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
      fread(&buffer, sizeof(buffer[0]), tiff.numberOfDataItems, f);
      printf("Model:\t%s\n", buffer);
    }

    /* Loop #2 */
    else if (tiff.tagIdentifier == 0x8769) {
      fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
      fread(&block, sizeof(block), 1, f);

      unsigned int one;
      unsigned int two;
      int n;
      for (n = 0; n < block; n++) {
        fread(&tiff, sizeof(tiff), 1, f);
        save2 = ftell(f);
        /* width */
        if (tiff.tagIdentifier == 0xA002) {
          printf("Width:\t%d\n", tiff.offsetOfDataItems);
        }
        /* Height */
        else if (tiff.tagIdentifier == 0xA003) {
          printf("Height:\t%d\n", tiff.offsetOfDataItems);
        }
        /* ISO speed */
        else if (tiff.tagIdentifier == 0x8827) {
          printf("ISO Speed:\t%d\n", tiff.offsetOfDataItems);
        }
        /* Exposure Speed */
        else if (tiff.tagIdentifier == 0x829a) {
          fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
          fread(&one, sizeof(one), 1, f);
          fread(&two, sizeof(two), 1, f);
          printf("Exposure Time:\t%d/%d second \n", one, two);
        }
        /* F stop (must make it a double) */
        else if (tiff.tagIdentifier == 0x829d) {
          fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
          fread(&one, sizeof(one), 1, f);
          fread(&two, sizeof(two), 1, f);
          printf("F-Stop:\t%d/%d\n", (double) one, (double) two);
        }
        /*Lens Length */
        else if (tiff.tagIdentifier == 0x920A) {
          fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
          fread(&one, sizeof(one), 1, f);
          fread(&two, sizeof(two), 1, f);
          unsigned int d = one/two;
          printf("Lens Length:\t%d\n", d);
        }
        /*Date Taken */
        else if (tiff.tagIdentifier == 0x9003) {
          fseek(f, tiff.offsetOfDataItems + 12, SEEK_SET);
          fread(&buffer, sizeof(buffer[0]), tiff.numberOfDataItems, f);
          printf("Date Taken:\t%s\n", buffer);
        }

        fseek(f, save2, SEEK_SET);
        /* end of for loop*/

      }
      /* back in 8769 */

    }
    fseek(f, save, SEEK_SET);
  }
  return 0;
}

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  // The size, in bytes, of the image
  uint32_t         bV5Size;
  // The width of the bitmap, in pixels.
  uint64_t         bV5Width;
  // The height of the bitmap, in pixels. If the value of bV5Height is positive, 
  // the bitmap is a bottom-up DIB and its origin is the lower-left corner. 
  // If bV5Height value is negative, the bitmap is a top-down DIB and its 
  // origin is the upper-left corner.
  uint64_t         bV5Height;
  uint16_t         bV5Planes;
  // The number of bits that define each pixel and the maximum number of colors 
  // in the bitmap.  
  uint16_t         bV5BitCount;
  uint32_t         bV5SizeImage;
} BITMAPV5HEADER;

// prevent padding this struct to 16 bytes which breaks things
typedef struct __attribute__((packed)) { 
    // 0x4D42 for BMP
    uint16_t headerField;
    // The size of the BMP file in bytes
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    // The offset, i.e. starting address, of the byte where 
    // the bitmap image data (pixel array) can be found.
    uint32_t startAddress;
} FILEHEADER;


// Helper function to read in the provided
// number of bytes, and then return an integer read in big endian
int reverseToBigEndian(FILE * fp, int numBytes) {
    int chars[numBytes];
    int c;
    int value = 0;
    for (int ii=0; ii < numBytes; ii++) {
        c = getc(fp);   
        chars[ii] = c;
    }
    for (int ii=numBytes - 1; ii >= 0; ii--) {
        value ^= chars[ii];
        if (ii > 0) {
            value <<= 8;
        }
    }    
    return value;
}

typedef struct {
  char bytes[3];
} pixel;

FILEHEADER* getFileHeader(FILE *fp) {
    FILEHEADER* fileHeader = malloc(sizeof(FILEHEADER));
    fileHeader->headerField = reverseToBigEndian(fp, 2);
    assert(fileHeader->headerField == 0x4D42);

    // The size of the file is the next 4 bytes
    int chars[4];
    int ii;
    fileHeader->size = reverseToBigEndian(fp, 4);
    printf("The file_size is %d\n", fileHeader->size);

    
    fseek(fp, 4, SEEK_CUR); // Skip over reserved fields
    fileHeader->startAddress = reverseToBigEndian(fp, 4);;
    printf("The bitmap start offset is at %d\n", fileHeader->startAddress);
    assert(fileHeader->startAddress == 0x8a);    
    return fileHeader;
}

BITMAPV5HEADER* getDIBHeader(FILE* fp) {
    BITMAPV5HEADER* dibHeader = malloc(sizeof(BITMAPV5HEADER));
    dibHeader->bV5Size = reverseToBigEndian(fp, 4);
    printf("The header_size is %d\n", dibHeader->bV5Size);
    
    dibHeader->bV5Width = reverseToBigEndian(fp, 4);
    printf("The width is %llu\n", dibHeader->bV5Width);
    dibHeader->bV5Height = reverseToBigEndian(fp, 4);
    printf("The height is %llu\n", dibHeader->bV5Height);    
    dibHeader->bV5Planes = reverseToBigEndian(fp, 2);
    
    printf("The planes is %d\n", dibHeader->bV5Planes);
    assert(dibHeader->bV5Planes == 1);
    dibHeader->bV5BitCount = reverseToBigEndian(fp, 2);
    printf("The bytes per pixel is %d bytes\n", dibHeader->bV5BitCount / 8);  
    
    fseek(fp, 4, SEEK_CUR); // skip bV5Compression
    dibHeader->bV5SizeImage = reverseToBigEndian(fp, 4);
    printf("The bV5SizeImage is %d bytes\n", dibHeader->bV5SizeImage);  
    int rowSize = ((dibHeader->bV5BitCount * dibHeader->bV5Width + 31) / 32) * 4;    
    int bitMapImageSize = rowSize * dibHeader->bV5Height;
    assert(bitMapImageSize == dibHeader->bV5SizeImage);
    return dibHeader;
}

void rotateMatrix (pixel** matrix, int n) 
{
    int left = 0, right = n - 1;
    int top, bottom, i;
    pixel tmp;

    while (left < right) {
        top = left;
        bottom = right;
        for (i = 0; i < right - left; i++) {
            tmp = matrix[top][left + i];
            matrix[top][left + i] = matrix[top + i][right];
            matrix[top + i][right] = matrix[bottom][right - i];
            matrix[bottom][right - i] = matrix[bottom - i][left];
            matrix[bottom - i][left] = tmp;
        }
        left++;
        right--;
    }
}

int main () {
    FILE* fp = fopen("./sample_bmp_file.bmp", "rb");
    FILE* fpOut = fopen("test.bmp", "wb");
    FILEHEADER* fileHeader = getFileHeader(fp);
    BITMAPV5HEADER* dibHeader = getDIBHeader(fp); 
    // Specifically, in the order: blue, green and red (8 bits per each sample)
    // Create an image height x image width matrix
    pixel** matrix = malloc(dibHeader->bV5Height * sizeof(pixel*));
    pixel* p;
    for (int i=0; i < dibHeader->bV5Height; i++) {
        matrix[i] = (pixel*)malloc(dibHeader->bV5Width * sizeof(pixel));
    }
    int rowSize = ((dibHeader->bV5BitCount * dibHeader->bV5Width + 31) / 32) * 4;
    int numBytesPerPixel = rowSize / dibHeader->bV5Width;
    
    // Move to the start of the bitmap of the image
    fseek(fp, fileHeader->startAddress, SEEK_SET);

    // Create a width x height matrix of pixels
    for (int i = 0; i < dibHeader->bV5Height; i++) {
        for (int j = 0; j < dibHeader->bV5Width; j++) {
            p = malloc(sizeof(pixel));
            for (int k = 0; k < numBytesPerPixel; k++) {
                p->bytes[k] = getc(fp);
            }
            matrix[i][j] = *p;
        }
    }
    rotateMatrix(matrix, dibHeader->bV5Height);    
    
    // Write each byte of the bitmap image to a buffer in a rotated order
    char* imageBuf = malloc(dibHeader->bV5SizeImage);
    int index = 0;
    pixel pix;
    for (int row = 0; row < dibHeader->bV5Height; row++) {
        for (int col = 0; col < dibHeader->bV5Width; col++) {
            for (int k = 0; k < numBytesPerPixel; k++) {
                imageBuf[index++] = matrix[row][col].bytes[k];
            };
        }
    }

    char *headerBuf = (char *)malloc(dibHeader->bV5Size + sizeof(FILEHEADER));
    if (headerBuf == NULL) {
        printf("Memory allocation error.\n");
        fclose(fp);
        fclose(fpOut);
        return 1;
    }
    // Read the entire content of the source file into the header
    fseek(fp, 0, SEEK_SET);
    size_t bytesRead = fread(headerBuf, 1, fileHeader->startAddress, fp);
    // Write the header buffer
    int headerFlag = fwrite(headerBuf, 1, bytesRead, fpOut);    
    fseek(fp, fileHeader->startAddress, SEEK_SET);
    int imageFlag = fwrite(imageBuf, 1, dibHeader->bV5SizeImage, fpOut);
    if (headerFlag && imageFlag) {
        printf("Sucessfully printed to fpOut\n");
    }

    // Close both files and free the allocated memory
    fclose(fp);
    fclose(fpOut);
    free(imageBuf);
    free(p);
    free(headerBuf);
}
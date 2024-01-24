#define RED0 0x00
#define RED1 0x20
#define RED2 0x40
#define RED3 0x60
#define RED4 0x80
#define RED5 0xa0
#define RED6 0xc0
#define RED7 0xe0
#define GREEN0 0x00
#define GREEN1 0x04
#define GREEN2 0x08
#define GREEN3 0x0c
#define GREEN4 0x10
#define GREEN5 0x14
#define GREEN6 0x18
#define GREEN7 0x1c
#define BLUE0 0x00
#define BLUE1 0x01
#define BLUE2 0x02
#define BLUE3 0x03
/*
 * To run:
 * 1. make convert OR make to run benchmark
 * 2. ./convert teapots.bmp teapots_out.bmp 
 */
const int red_table[8] = {
  RED0, RED1, RED2, RED3, RED4, RED5, RED6, RED7
};
const int green_table[8] = {
  GREEN0, GREEN1, GREEN2, GREEN3, GREEN4, GREEN5, GREEN6, GREEN7
};
const int blue_table[4] = { BLUE0, BLUE1, BLUE2, BLUE3 };

unsigned char quantize_optimized(unsigned char red, unsigned char green,
                       unsigned char blue) {
  unsigned char out = 0;
  // shift by 4 to zero out the lower order byte and then shift by 1 
  // more in order to divide by 2 
  out += red_table[red >> 5]; 
  out += green_table[green >> 5];
  // shift by 4 to zero out the lower order bit
  // shift by 2 more in order to divide by 4  
  out += blue_table[blue >> 6]; 
  return out;
}


// use bitmasking to mask according to the protocol
// https://en.wikipedia.org/wiki/List_of_8-bit_computer_hardware_graphics#8-bit_RGB_palettes
unsigned char quantize(unsigned char red, unsigned char green,
                       unsigned char blue) {
  return (red & 0xe0) | ((green & 0xe0) >> 3) | (blue >> 6);
}



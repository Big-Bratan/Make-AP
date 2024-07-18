#include <pgmspace.h>
#include <Arduino.h>

// pixil-frame-0 (9).jpg
// https://lang-ship.com/tools/image2data/

const uint16_t routerImgWidth = 64;
const uint16_t routerImgHeight = 64;

// RGB565 Dump(little endian)
const unsigned short routerImg[4096] PROGMEM = {
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x2008,0x0000,0x2000,0x0000,0x0000,0x2008,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 0, 64 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6108,0x0000,0x4200,0x2100,0x0100,0x0000,0x0000,0x0000,0x0100,0x0000,0x2000,0x0000,0x2100,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 1, 128 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x2200,0x0200,0x0200,0x0300,0x8408,0x0200,0x0200,0x0100,0x4100,0x0000,0x0000,0x4100,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 2, 192 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4308,0x5384,0xD694,0xB68C,0xD78C,0xD26B,0xC610,0x0200,0x2300,0x0100,0x0100,0x6200,0x0000,0x4100,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 3, 256 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2200,0x5384,0xB58C,0xD68C,0xD68C,0xD68C,0x7584,0x958C,0x958C,0x6300,0x2200,0x0100,0x0100,0x2100,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 4, 320 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0xA408,0x0200,0x0200,0x0200,0x0611,0xF273,0xF594,0x537C,0x379D,0x547C,0x6400,0x8400,0x0200,0x6200,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 5, 384 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x0100,0x0100,0x4300,0x0200,0x0100,0x8308,0x2200,0x6400,0x537C,0x9584,0xD68C,0x347C,0x6500,0x0200,0x6200,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 6, 448 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x6300,0x0200,0x6300,0x2200,0x0100,0x0100,0x0200,0x0200,0x6400,0x9584,0xB68C,0x9584,0x4300,0x0100,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 7, 512 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x948C,0x9484,0xF694,0x9584,0x6400,0x0200,0x0300,0x0200,0x0200,0x0200,0x6400,0xF373,0x3895,0x7584,0x0200,0x0100,0x0000,0x0000,0x2000,0x0000,0x4208,0x0000,0x0000,// row 8, 576 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2200,0xD594,0x9484,0xB68C,0x9584,0xF794,0x7484,0x2400,0x2300,0x0200,0x2100,0x0100,0x4719,0xD26B,0xF794,0x2400,0x0200,0x2100,0x0000,0x0000,0x0000,0x0100,0x2000,0x0000,// row 9, 640 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x2300,0x0300,0x0300,0xA508,0xF373,0xF794,0x5484,0x3484,0x8508,0x0100,0x4200,0x0100,0x8400,0x1895,0x557C,0x0200,0x6200,0x2000,0x0000,0x2100,0x0000,0x2000,0x0000,// row 10, 704 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2200,0x0100,0x6300,0x0200,0x2300,0x0200,0x2300,0xB594,0x179D,0x916B,0xA408,0x0100,0x0100,0x0200,0xF373,0x399D,0x6500,0x0200,0x0000,0x0000,0x4108,0x0000,0x2000,0x0000,// row 11, 768 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2200,0x0200,0x6300,0x0200,0x4300,0x0200,0x0200,0x0300,0x99AD,0x3384,0x0100,0x4200,0x0100,0xE610,0x347C,0x5484,0x4300,0x2100,0x0000,0x0000,0x0000,0x0000,0x0000,// row 12, 832 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x5284,0x369D,0x748C,0x0200,0x2300,0x0200,0x0200,0x6400,0x137C,0x958C,0x8508,0x0200,0x0100,0x0200,0x1795,0x179D,0x0200,0x0100,0x4100,0x0000,0x2000,0x0000,0x2000,// row 13, 896 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6108,0x0421,0x0421,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x5384,0xB58C,0x9584,0xF794,0x337C,0x8500,0x2300,0x0200,0x8400,0xB694,0xD373,0x6400,0x2200,0x6300,0x537C,0x337C,0xE610,0x0100,0x2100,0x0000,0x0000,0x0000,0x0000,// row 14, 960 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0xE318,0xE739,0xC739,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x4300,0x0200,0x4400,0x9584,0xF78C,0x7584,0x2300,0x2200,0x0200,0xB68C,0xD794,0x0300,0x0200,0x0200,0x4300,0x1695,0x337C,0x6300,0x0100,0x0000,0x2000,0x0000,0x0000,// row 15, 1024 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x0100,0x0200,0x8508,0x5584,0xD68C,0x0300,0x0200,0x0200,0x2400,0x968C,0xB58C,0x2300,0x0200,0x0200,0xD68C,0xD68C,0x0200,0x2100,0x0000,0x0000,0x2000,0x0000,// row 16, 1088 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4100,0x4200,0x0100,0x0200,0x6508,0x5584,0xD694,0x0200,0x0200,0x0300,0x958C,0xB58C,0x0200,0x0300,0x0200,0x9584,0xD58C,0x2200,0x2200,0x0000,0x0000,0x0000,0x0000,// row 17, 1152 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0x728C,0x938C,0x4300,0x0200,0x0200,0x958C,0x958C,0x0200,0x0100,0x0200,0xD594,0xD594,0x0200,0x0200,0x2200,0xF694,0xD58C,0x2200,0x0100,0x0000,0x0000,0x0000,0x2100,// row 18, 1216 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0100,0x9394,0xB494,0x2200,0x0200,0x6300,0xB48C,0xB494,0x0100,0x0000,0x6308,0x5284,0x5284,0x6308,0x0100,0x0100,0x9384,0x327C,0x8308,0x0100,0x0000,0x0000,0x0000,0x0000,// row 19, 1280 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x0000,0x0100,0x6308,0x0100,0x2100,0x0100,0x2100,0x0000,0x0100,0x4200,0x4200,0x0000,0x0000,0x2100,0x2100,0xA408,0x0100,0x0000,0x0000,0x0000,0x0000,0x0100,// row 20, 1344 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x0000,0x0000,0x0000,0x2100,0x0000,0x0000,0x2100,0x0000,0x0000,0x2100,0x0000,0x0000,0x0000,0x0100,0x0000,0x4108,0x0000,0x0000,0x0000,0x0000,// row 21, 1408 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6108,0x0421,0x0421,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x0000,0x0000,0x6108,0x2000,0x0000,0x0000,0x0000,0x2100,0x0000,0x0000,0x2000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 22, 1472 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0xE318,0xE739,0xC739,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x4000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 23, 1536 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0x4529,0x0842,0x2842,0x0000,0x2000,0x0000,0x4108,0x0000,0x0742,0x0742,0x2742,0x2742,0x284A,0x0000,0x4108,0x0000,0x6108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 24, 1600 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0xE841,0x4108,0x0000,0x4108,0xA631,0x0742,0xDADE,0xFADE,0xFADE,0xDADE,0xB9DE,0x6952,0xC639,0x0000,0x2000,0x0000,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 25, 1664 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4008,0x0000,0x0000,0xA631,0x484A,0xE739,0x0000,0x0842,0xC739,0x1CE7,0x3CEF,0x99D6,0xDADE,0xDADE,0xFADE,0xFAE6,0x1AE7,0x17C6,0x4C6B,0xC639,0x0000,0x0000,0x0000,0x4108,0x0000,0x0000,0x2100,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 26, 1728 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x8531,0x6529,0xAA52,0xE741,0x1BE7,0xBADE,0xFBE6,0x17C6,0x274A,0x1AE7,0x98D6,0x3BEF,0x98D6,0xFADE,0x5BEF,0x78D6,0xF6BD,0x6C6B,0xE641,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 27, 1792 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2108,0x0000,0x2000,0x0000,0x8110,0x0000,0xA631,0x484A,0x99D6,0x1BE7,0x99D6,0xDADE,0x8431,0x3BEF,0x98D6,0x78D6,0x8431,0xFAE6,0x3AEF,0xB8D6,0xF9E6,0xD9DE,0x9CF7,0x98D6,0xD5BD,0x4B6B,0xE641,0x0000,0x4008,0x0000,0x4008,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 28, 1856 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x4008,0x0000,0x0000,0x0000,0x2842,0x284A,0x58CE,0x3BEF,0xB9DE,0xDADE,0xA531,0xD9DE,0xB9DE,0xB9DE,0x6431,0x5BEF,0xB9DE,0xB8D6,0x4329,0x1AE7,0x19E7,0x77D6,0x19E7,0xB8D6,0x5BEF,0xB9DE,0xDADE,0x684A,0x484A,0x0000,0x0000,0x0000,0x4008,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 29, 1920 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6108,0x0000,0x2842,0x8952,0x58CE,0x5CEF,0xFAE6,0x58CE,0xE641,0x98D6,0xD9DE,0xFAE6,0xA539,0x99DE,0x3BEF,0x57CE,0xC639,0xB9DE,0x1AE7,0x78D6,0xFAE6,0x1AE7,0x7BF7,0x98D6,0xFAE6,0x78D6,0x1AE7,0xFADE,0x37C6,0xA952,0x2742,0x0000,0x6108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 30, 1984 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x0842,0x0842,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0xA631,0x694A,0xBADE,0x99D6,0x7CEF,0x98D6,0x8531,0xFAE6,0xB9D6,0x3BEF,0x6431,0xD9DE,0xB9DE,0xFAE6,0x4329,0x3BEF,0x99D6,0xFAE6,0xD9DE,0x1AE7,0xF9E6,0x77D6,0xF9E6,0x98D6,0x7CF7,0xB9DE,0xFAE6,0xDADE,0x5CEF,0x98D6,0xDADE,0x484A,0xC639,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 31, 2048 pixels
0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x2100,0x2521,0x2942,0x494A,0x0000,0x2000,0x0000,0x0000,0x0000,0x284A,0x684A,0xB9D6,0x1BE7,0xDADE,0xFADE,0x6429,0xB9DE,0xFAE6,0xFADE,0x8431,0x98D6,0x1AE7,0xD9DE,0xE541,0x36C6,0x5BEF,0xD9DE,0xD9DE,0xD9DE,0x1AE7,0xF9E6,0x98D6,0x1AE7,0xFAE6,0xD9E6,0x74B5,0x95BD,0xDAE6,0xFAE6,0xD9DE,0xB9DE,0xFAE6,0xFADE,0x99D6,0x2842,0x0742,0x0000,0x0000,0x0000,0x4108,0x0000,0x0000,0x0000,0x2000,// row 32, 2112 pixels
0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0xC739,0xC739,0xC739,0x6110,0x0000,0x0000,0x0742,0x484A,0xB9DE,0xB9DE,0x58CE,0x1AE7,0x6429,0xD9DE,0x1AE7,0xD9DE,0xE218,0x3BE7,0xD9DE,0x5BEF,0x2329,0xB8DE,0xB8D6,0x9CF7,0xD9DE,0xB8DE,0x3AE7,0x3BEF,0x78D6,0xFAE6,0xF9E6,0xFAE6,0x53AD,0x94B5,0xA539,0x4429,0x74B5,0x33AD,0x5CEF,0xD9DE,0xD9DE,0xB9DE,0x7CEF,0xB9D6,0xFADE,0x484A,0x494A,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 33, 2176 pixels
0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x8631,0x494A,0x0742,0x0000,0xC739,0xC639,0x1BE7,0xFBE6,0xDADE,0xBADE,0x274A,0x78D6,0xFAE6,0xDADE,0x6431,0x3AE7,0x5BEF,0xD9DE,0x4329,0xD9DE,0xFAE6,0x3AE7,0xD9DE,0x78CE,0xB9DE,0xFAE6,0xB9DE,0x98D6,0x5BEF,0xB9DE,0x93AD,0xB5B5,0xC539,0xE218,0xA952,0xA639,0x6531,0xC639,0xF2A4,0x74B5,0xFADE,0xD9DE,0xB9D6,0xD9DE,0xFAE6,0xBADE,0x79D6,0x284A,0x0000,0x4008,0x0000,0x0000,0x0000,// row 34, 2240 pixels
0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0x4429,0xA639,0x8952,0xE741,0xFBE6,0xDADE,0xDADE,0x78D6,0x0642,0x99DE,0x98DE,0xFAE6,0x4329,0xD9DE,0xD9DE,0xD9DE,0x0221,0xD9DE,0x3BE7,0xB9D6,0x1AE7,0xD9D6,0x1ADF,0x5BEF,0xFAE6,0x99DE,0xFAEE,0x3BEF,0x33AD,0xB4B5,0xA531,0x4321,0x2E7C,0x063A,0x6429,0x4429,0x55B5,0x13AD,0xD29C,0x0E84,0x57CE,0x5BEF,0xFADE,0xFADE,0xDADE,0x7CEF,0x99D6,0x484A,0x0000,0x0000,0x0000,0x0000,0x2000,// row 35, 2304 pixels
0x0000,0x0000,0x0000,0x2000,0x0000,0x4108,0x0000,0x2000,0x0000,0x0000,0x0000,0x4429,0x8952,0x37C6,0x3CEF,0xB9D6,0xDADE,0x6431,0x3BEF,0x98D6,0xDADE,0x0642,0x57CE,0x3BEF,0xFAE6,0xA531,0x98D6,0xBCF7,0xB9D6,0x98D6,0x5BEF,0xB9D6,0xFADE,0xFADE,0x99D6,0xDAE6,0xFBEE,0x13B5,0x33B5,0xA541,0x6431,0x908C,0x8429,0xC531,0x8531,0x33A5,0x95BD,0xCE83,0x7094,0x37CE,0xD9DE,0x5BEF,0xB8D6,0x98D6,0x7CF7,0xD9DE,0x37C6,0xD29C,0xE741,0x0000,0x0000,0x0000,0x0000,0x0000,// row 36, 2368 pixels
0x0000,0x0000,0x0000,0x2000,0x0000,0x4008,0x0000,0x0000,0x0000,0x694A,0xAA5A,0xF7C5,0x7CF7,0xDADE,0xDADE,0x8531,0xFAE6,0xB9D6,0xFAE6,0x6431,0xFAE6,0x98D6,0x5BEF,0x2321,0x1AE7,0x98D6,0x3BE7,0x78CE,0xFADE,0x5BEF,0x78D6,0x1AE7,0x1AE7,0xFADE,0xDAE6,0x75BD,0xF3B4,0xA649,0x6541,0x0752,0x6431,0xA531,0xA531,0x73A5,0xB5B5,0xEE7B,0x508C,0xDAE6,0x78D6,0x5CEF,0xB9DE,0xFAE6,0x3BEF,0xFAE6,0x99D6,0xEE83,0x508C,0x6D73,0xE741,0x0000,0x0000,0x2000,0x0000,0x0000,// row 37, 2432 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x6108,0x0000,0x2842,0x284A,0x58CE,0xBADE,0xBDFF,0x16C6,0x274A,0x98D6,0x1AE7,0xB9DE,0xE641,0x78D6,0x1AE7,0xB9DE,0x8431,0xD9DE,0x1AE7,0xD9DE,0x1AE7,0xF9DE,0xD9DE,0xB9DE,0xB9DE,0x1AE7,0xD9DE,0x98D6,0xB5B5,0x54B5,0x6539,0x6541,0x085A,0xE430,0xC749,0x8539,0xF29C,0xB5B5,0x0E7C,0x2F84,0xD9DE,0xB9DE,0xDAE6,0xFAE6,0xDADE,0xFAE6,0xFADE,0x57CE,0x508C,0xCE7B,0x3084,0x0F84,0xEF7B,0x694A,0x2108,0x0000,0x0000,0x0000,0x0000,// row 38, 2496 pixels
0x0000,0x0000,0x0000,0x0000,0x2000,0xA631,0x694A,0xBADE,0xDADE,0x3BE7,0xB9DE,0x98D6,0x5BEF,0x78D6,0x1BE7,0x6431,0x1AE7,0xB9DE,0x1AE7,0x8431,0xB9DE,0xFAE6,0xFAE6,0xD9DE,0xD9DE,0x1ADF,0xF9DE,0xD9DE,0xFAE6,0xB9DE,0xFAE6,0x53B5,0xB4B5,0x6429,0xA539,0x2852,0x6541,0x0431,0x8641,0x14B5,0x75B5,0x7194,0xAD73,0x3BE7,0x98CE,0x3BE7,0xD9DE,0xD9E6,0xFAE6,0xDADE,0xDADE,0x0F84,0x0F84,0x0F84,0x0842,0xC739,0xEF7B,0x1084,0xC739,0x0000,0x2100,0x0000,0x0000,0x0000,// row 39, 2560 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x284A,0x1BE7,0xB9D6,0xDADE,0xDADE,0xFAE6,0xFAE6,0xFAE6,0x98D6,0x1AE7,0xF9DE,0xB8DE,0xA539,0x98DE,0x1AE7,0xD9E6,0xFAE6,0xB9DE,0xFADE,0x3AE7,0x98D6,0xFADE,0xD9E6,0xFAE6,0x54BD,0x95C5,0x4431,0x6429,0x908C,0x8531,0x0329,0xA641,0x34B5,0x54B5,0xEF8B,0x308C,0xB9DE,0xFADE,0xB9D6,0x5BE7,0xB9D6,0x1BE7,0xFAE6,0xDADE,0x2F84,0x0F84,0xEE7B,0xEF7B,0x2942,0x4529,0x4629,0x0942,0xCF7B,0x0842,0x0000,0x0100,0x0000,0x0000,0x0000,// row 40, 2624 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0742,0xF7C5,0x9DF7,0xB9D6,0xFAE6,0x1BE7,0x98D6,0xB9DE,0x3BEF,0xD9DE,0xD9DE,0x5BEF,0x57D6,0x5BF7,0x98D6,0xB9DE,0xD9DE,0x1AE7,0xD9DE,0x78CE,0x1ADF,0x3BE7,0x53AD,0x74B5,0x2331,0x2339,0x8962,0xA539,0x6429,0x6429,0xB5BD,0x13AD,0x0F84,0x0F8C,0xBADE,0x99D6,0xFAE6,0xFADE,0xB9D6,0xFADE,0x3BE7,0xDADE,0xCE7B,0x3084,0xCE7B,0xCF7B,0x0842,0x2942,0x2521,0x8731,0x9394,0x2A4A,0xF07B,0x0942,0x0000,0x0000,0x0000,0x2000,0x0000,// row 41, 2688 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0xC639,0x6D6B,0xD6BD,0xFBE6,0xDADE,0xB9DE,0x5BEF,0xB9DE,0xFAE6,0xB8D6,0x3AEF,0xD9DE,0xB9DE,0xF9E6,0xD9DE,0xFAE6,0xFAE6,0xD9DE,0xF9DE,0x3AE7,0x94AD,0x53A5,0xE641,0x2331,0x685A,0x8541,0x4431,0x2429,0x95B5,0x74AD,0x2F84,0x0F84,0xDADE,0xFAE6,0xB9DE,0xFAE6,0xFAE6,0xFADE,0x1BE7,0x79D6,0x0F84,0x8D73,0x1084,0x8E73,0x2942,0xE839,0xC831,0x0942,0x4729,0x2621,0x9494,0xE941,0xB07B,0x0942,0x0100,0x0000,0x2000,0x0000,0x0000,// row 42, 2752 pixels
0x0000,0x0000,0x0000,0x0000,0x2000,0xE739,0xA631,0xCA5A,0x6952,0x79D6,0xB9DE,0x3BEF,0xB9DE,0x3BEF,0xB9DE,0xB9DE,0x1AE7,0xFAE6,0xF9DE,0xD9DE,0x5BEF,0xFADE,0x98CE,0xD5B5,0x53A5,0xC531,0x6429,0x2F84,0xC639,0x8539,0x0329,0x54B5,0x95BD,0x2F84,0x0F84,0x99D6,0xDADE,0xFAE6,0x1BE7,0xFAE6,0xB9DE,0xFAE6,0x78D6,0x9194,0xCE7B,0x0F84,0x518C,0x8E73,0x8B52,0x4621,0x8729,0xF17B,0x6B4A,0x4729,0x4729,0xD59C,0x2A42,0xD07B,0x2942,0x0000,0x0000,0x0000,0x0000,0x2000,// row 43, 2816 pixels
0x0000,0x2000,0x0000,0x0000,0x0000,0x294A,0xE741,0xC739,0xC739,0x494A,0x8952,0x58CE,0xDADE,0xFAE6,0xB9DE,0x3BE7,0xB8D6,0xF9DE,0x3AE7,0x1AE7,0x98D6,0x74AD,0xD5BD,0x6429,0xE631,0x4F84,0x8529,0xA531,0x2321,0x74B5,0xB5BD,0xEF8B,0xEE83,0x99D6,0xFAE6,0xFAE6,0x1BE7,0xB9DE,0xDADE,0xB9DE,0xFAE6,0x5094,0x8D73,0xAE7B,0x1084,0x8E7B,0xAF7B,0x518C,0xA731,0x8731,0x6729,0xF59C,0xE939,0x4721,0x8729,0x538C,0xE939,0xF07B,0x294A,0x0000,0x0000,0x2000,0x0000,0x2000,// row 44, 2880 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0842,0x6A52,0x0842,0x0842,0x0842,0xC739,0x284A,0x8952,0x78D6,0x1BEF,0xB9D6,0x1AE7,0x1ADF,0x98D6,0xD9DE,0x7CF7,0xCD7B,0x0E84,0x54AD,0x33A5,0x063A,0x6421,0x74A5,0x95B5,0xEE7B,0x0F84,0xD9DE,0xD9DE,0xDADE,0xFAE6,0xFAE6,0xFAE6,0xBADE,0xFBE6,0x2F84,0xAE7B,0xEF83,0xEF83,0x0742,0x6952,0x1084,0xF083,0xAF73,0x2942,0x6729,0x0519,0x159D,0xE939,0x6729,0x6729,0x8731,0x4A4A,0xCF7B,0x2942,0x0000,0x0000,0x2000,0x0000,0x0000,// row 45, 2944 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0xC739,0x294A,0x0842,0x0842,0x294A,0xE841,0x0842,0xE741,0xE741,0x6952,0xDADE,0xFADE,0x98D6,0x3BEF,0xB9DE,0x78D6,0xFAE6,0xDAE6,0x0F84,0x308C,0x33A5,0xF6BD,0xEE7B,0x3084,0xDADE,0xBADE,0xB9DE,0xD9DE,0xD9DE,0x1AE7,0xD9DE,0xBADE,0xEF83,0xCF7B,0xF083,0xEF7B,0xE739,0x494A,0xC739,0x0842,0x8E73,0x1084,0x3084,0x2942,0x4621,0xC831,0x5284,0x093A,0x6629,0x4A4A,0xE839,0xCF7B,0xAF73,0xE841,0x4108,0x0000,0x0000,0x0000,0x0000,// row 46, 3008 pixels
0x0000,0x0000,0x2000,0x0000,0x4108,0xE841,0x0842,0x0942,0x0942,0x0842,0xE841,0x294A,0x0842,0x484A,0xC739,0x284A,0x284A,0xDADE,0xB9DE,0xFAE6,0x1BEF,0x99DE,0xDAE6,0xB9DE,0xBADE,0x0F84,0xEE7B,0xFADE,0xB9D6,0xFAE6,0xDADE,0x1BE7,0xFAE6,0xFADE,0xB9DE,0x0F84,0x0F84,0xEF83,0xF083,0x0842,0x2942,0x0842,0x0842,0xA210,0x2942,0x1084,0xAE73,0x1084,0x2942,0x8629,0x2521,0x6629,0x2942,0x2942,0xD07B,0x1084,0xEF7B,0xAA52,0xC739,0x8631,0x0421,0x4108,0x0000,0x0000,// row 47, 3072 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0842,0x0842,0x0842,0x2942,0x0842,0x2942,0x294A,0x0842,0xA318,0x8631,0xC739,0x0742,0xC739,0x484A,0xDAE6,0x79D6,0x5CF7,0xBADE,0xFAE6,0xDADE,0xDADE,0xB9DE,0xDADE,0x1AE7,0xDADE,0x3BEF,0x58CE,0x9AD6,0x518C,0xCF7B,0xCF7B,0xCF7B,0x294A,0x0942,0x0842,0x6A4A,0x4529,0x6629,0x8210,0x294A,0xF083,0xAF7B,0x1084,0x0842,0x8631,0x4521,0x694A,0xEF7B,0xF07B,0xEF7B,0x0842,0xE739,0xA631,0x6529,0xE318,0x4108,0x0000,0x0000,0x0000,// row 48, 3136 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0842,0x0842,0x2842,0x2842,0x0842,0x0842,0x0842,0xE841,0x8310,0x6629,0xA731,0x4529,0x8A52,0xC739,0x0842,0x8A52,0x38CE,0x99D6,0x3BEF,0xDADE,0xFAE6,0xFAE6,0x1AE7,0x3BEF,0x78D6,0x37CE,0xD2A4,0x318C,0x8F7B,0x8F7B,0x4A52,0x294A,0xC839,0xE841,0x8631,0x2529,0x6631,0x6631,0xC318,0xA739,0xF083,0x518C,0xAF73,0xCF7B,0x694A,0x494A,0x6D6B,0xCF7B,0x694A,0xE739,0xA631,0x6529,0xE318,0x8210,0x2000,0x0000,0x0000,0x0000,0x0000,// row 49, 3200 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0842,0x0842,0x0842,0x2942,0x0842,0x0842,0x0842,0x0842,0xA310,0x4529,0x6631,0x6629,0xE841,0x294A,0xE841,0xA739,0x6952,0xCA5A,0x79D6,0xB9D6,0x1BE7,0xDADE,0x99D6,0x38CE,0xF3A4,0x508C,0xEB62,0x8E73,0x8A52,0x494A,0x8631,0x294A,0x294A,0x8731,0x4529,0x6631,0x6631,0x8210,0x0421,0x0842,0xAF7B,0xF083,0x3184,0x318C,0x8E73,0xAE73,0xAA52,0xE739,0xA631,0x2421,0x4529,0x6108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 50, 3264 pixels
0x0000,0x0000,0x0000,0x0000,0x2108,0x0842,0x494A,0xE839,0x2942,0x0842,0x0842,0x2942,0x2942,0xC318,0x4529,0x6629,0xA739,0xA739,0xE841,0x0421,0xA739,0x0842,0x4529,0x8A52,0x6952,0xAE7B,0x0F84,0x1084,0x308C,0x6D73,0x6E73,0xEB62,0x294A,0xE841,0xE841,0xE420,0xA739,0xE841,0x4529,0x4631,0x2529,0x2529,0xC318,0x8739,0x094A,0x118C,0xD083,0xAF7B,0x8E73,0x694A,0x2842,0x6529,0x4529,0x6529,0x6108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 51, 3328 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x8631,0x494A,0xE841,0x2942,0x0842,0x0842,0x0842,0x0842,0xC318,0x6629,0x6629,0xE420,0x2942,0x4A4A,0x6208,0xE420,0x8631,0xA739,0xC739,0x0842,0xCF7B,0x1084,0xEF83,0xAF7B,0x294A,0x084A,0x8639,0xC741,0x8631,0x0421,0x8210,0xE841,0x8A52,0x8631,0x4529,0x4529,0x0421,0xA210,0x494A,0x294A,0xAF73,0xAF7B,0x494A,0x2842,0xA631,0x6529,0x2421,0x6108,0x0000,0x0000,0x2000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x2000,// row 52, 3392 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0xA210,0xC739,0x0842,0x294A,0x0842,0x0842,0x0842,0x0842,0xC318,0x6631,0x8631,0x8731,0x0942,0xA739,0xC418,0xC839,0x4529,0x4529,0x294A,0xE841,0xCF7B,0xF083,0xF083,0xF083,0x294A,0xE841,0xA739,0x6631,0x8631,0x4529,0x0421,0xE841,0x0842,0xA739,0x2842,0xA318,0x294A,0x0842,0xCF7B,0x8E73,0x8A52,0x2942,0x2421,0x8631,0x2421,0x0000,0x0000,0x0000,0x2000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 53, 3456 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0421,0xC739,0xE839,0xE841,0x0842,0x0842,0x0842,0xC318,0x4529,0x2529,0x2529,0x4A4A,0x0842,0x8210,0x4529,0x6631,0x8631,0x0842,0x494A,0x1084,0xCF83,0xCF7B,0xD07B,0xE841,0x6631,0x4529,0x4529,0x8631,0xA310,0xA310,0xC739,0x494A,0x0842,0x0842,0x2842,0xF07B,0xAE73,0x8A52,0x0842,0x6631,0x4529,0xA731,0x0000,0x2000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,// row 54, 3520 pixels
0x0000,0x2000,0x0000,0x0000,0x2000,0x0000,0x4108,0x4529,0x6629,0xA631,0xE841,0x2842,0x0842,0x8210,0xE418,0xA318,0x8631,0xE841,0xE841,0x0421,0x4529,0x6629,0x4529,0x0842,0xE841,0xF083,0xCF83,0xF083,0x1084,0xE841,0x6631,0x4529,0x8631,0x4529,0xC318,0xE839,0x6A4A,0x8631,0x494A,0xF07B,0x1084,0xE739,0x494A,0x4529,0x4529,0x8631,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 55, 3584 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2108,0x0421,0x4529,0x8631,0x0842,0x494A,0xE739,0xC318,0x8310,0x2942,0xE841,0x8210,0x8631,0x8631,0x2529,0x0842,0x294A,0x1084,0xAF7B,0xCF7B,0x1084,0xE841,0x8631,0x6631,0x6529,0x8210,0xE318,0xE841,0x494A,0xAF73,0x518C,0xC739,0xE839,0xC739,0x6631,0xE318,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 56, 3648 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0x6210,0xC318,0x4529,0xC739,0x0842,0xA739,0x0842,0x294A,0x0842,0xA318,0x2421,0x6629,0x8631,0x494A,0xE841,0xF083,0x318C,0xF083,0xD083,0x294A,0xC839,0xE841,0xC318,0xE841,0x294A,0xAF73,0xCF7B,0x294A,0xE841,0x8631,0x6529,0xE420,0x6210,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 57, 3712 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x6208,0xC318,0x6631,0xE739,0x494A,0x0842,0xE841,0xE420,0xC318,0xC318,0xE420,0x0842,0x494A,0xAF73,0xF07B,0xF083,0xF083,0x294A,0xC839,0x4A52,0x2942,0x1084,0x6E73,0x8A52,0x494A,0x4529,0x2529,0x6631,0x4108,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 58, 3776 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x6210,0xE420,0x2521,0xC739,0x0842,0xC739,0xA731,0xE420,0xE420,0xE841,0x0942,0xCF7B,0x1184,0x1084,0x8F7B,0xE841,0x8A52,0x6E73,0xAF73,0x8A52,0x0842,0x4529,0x4529,0x6529,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 59, 3840 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2100,0x2100,0x0421,0x4529,0x0842,0x294A,0xA739,0xE839,0x294A,0x0942,0xF07B,0xAF7B,0xF07B,0x9294,0xAE73,0x8E73,0x494A,0x494A,0x0421,0x8631,0x4529,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 60, 3904 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0421,0x4529,0xA731,0x294A,0xE841,0x0842,0xF07B,0x1084,0xCF7B,0x8E73,0x494A,0x494A,0x6529,0x4529,0x2421,0x4108,0x0000,0x0000,0x2000,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 61, 3968 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4108,0x0000,0x0000,0x2000,0x4108,0x0421,0x2529,0x8631,0x0842,0x0842,0x0842,0xE739,0x0842,0x8531,0x6531,0x6529,0x0000,0x6108,0x0000,0x0000,0x4108,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 62, 4032 pixels
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x6108,0x0000,0x6529,0x8631,0x0421,0xA631,0x4429,0x8631,0x4429,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,// row 63, 4096 pixels
};
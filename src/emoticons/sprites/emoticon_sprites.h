#ifndef EMOTICON_SPRITES_H_
#define EMOTICON_SPRITES_H_

//EYE SPRITES:
//----------------------------------------------

// 'mouth_smile', 8x9px
const unsigned char epd_bitmap_mouth_smile [] PROGMEM = {
	0x60, 0x30, 0x18, 0x18, 0x18, 0x18, 0x18, 0x30, 0x60
};
// 'mouth_3', 8x9px
const unsigned char epd_bitmap_mouth_3 [] PROGMEM = {
	0x78, 0xcc, 0x0c, 0x0c, 0x38, 0x0c, 0x0c, 0xcc, 0x78
};
// 'mouth_D', 8x9px
const unsigned char epd_bitmap_mouth_D [] PROGMEM = {
	0xf8, 0x6c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6c, 0xf8
};
// 'mouth_I', 8x9px
const unsigned char epd_bitmap_mouth_I [] PROGMEM = {
	0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c
};
// 'mouth_O_big', 8x9px
const unsigned char epd_bitmap_mouth_O_big [] PROGMEM = {
	0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x6c, 0x38
};
// 'mouth_P', 8x9px
const unsigned char epd_bitmap_mouth_P [] PROGMEM = {
	0xfc, 0x66, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0xf0
};
// 'mouth_T', 8x9px
const unsigned char epd_bitmap_mouth_T [] PROGMEM = {
	0x7e, 0x5a, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c
};
// 'mouth_o', 8x9px
const unsigned char epd_bitmap_mouth_o [] PROGMEM = {
	0x00, 0x00, 0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 256)
const int epd_bitmap_mouth_allArray_LEN = 8;
const unsigned char* epd_bitmap_mouth_allArray[8] = {
	epd_bitmap_mouth_smile,
	epd_bitmap_mouth_D,
	epd_bitmap_mouth_I,
	epd_bitmap_mouth_O_big,
	epd_bitmap_mouth_P,
	epd_bitmap_mouth_T,
	epd_bitmap_mouth_3,
	epd_bitmap_mouth_o
};



//EYE SPRITES:
//----------------------------------------------

// 'eyes_bar', 8x9px
const unsigned char epd_bitmap_eyes_bar [] PROGMEM = {
	0x00, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18
};
// 'eyes_colon', 8x9px
const unsigned char epd_bitmap_eyes_colon [] PROGMEM = {
	0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18
};
// 'eyes_semicolon', 8x9px
const unsigned char epd_bitmap_eyes_semicolon [] PROGMEM = {
	0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 96)
const int epd_bitmap_eyes_allArray_LEN = 3;
const unsigned char* epd_bitmap_eyes_allArray[3] = {
	epd_bitmap_eyes_colon,
	epd_bitmap_eyes_bar,
	epd_bitmap_eyes_semicolon
};

#endif
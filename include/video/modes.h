#pragma once
#include "types.h"
#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

extern unsigned char g_40x25_text[61];
extern unsigned char g_40x50_text[61];
extern unsigned char g_80x25_text[61];
extern unsigned char g_80x50_text[61];
extern unsigned char g_90x30_text[61];
extern unsigned char g_90x60_text[61];
extern unsigned char g_640x480x2[61];
extern unsigned char g_320x200x4[61];
extern unsigned char g_640x480x16[61];
extern unsigned char g_720x480x16[61];
extern unsigned char g_320x200x256[61];
extern unsigned char g_320x200x256_modex[61];

extern unsigned char g_8x8_font[2048];
extern unsigned char g_8x16_font[4096];
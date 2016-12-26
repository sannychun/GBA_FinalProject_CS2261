
//{{BLOCK(level1)

//======================================================================
//
//	level1, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 453 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 28992 + 8192 = 37696
//
//	Time-stamp: 2016-11-08, 19:35:43
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVEL1_H
#define GRIT_LEVEL1_H

#define level1TilesLen 28992
extern const unsigned short level1Tiles[14496];

#define level1MapLen 8192
extern const unsigned short level1Map[4096];

#define level1PalLen 512
extern const unsigned short level1Pal[256];

#endif // GRIT_LEVEL1_H

//}}BLOCK(level1)

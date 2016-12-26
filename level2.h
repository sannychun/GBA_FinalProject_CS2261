
//{{BLOCK(level2)

//======================================================================
//
//	level2, 512x512@8, 
//	+ palette 256 entries, not compressed
//	+ 477 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 30528 + 8192 = 39232
//
//	Time-stamp: 2016-11-10, 20:34:29
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVEL2_H
#define GRIT_LEVEL2_H

#define level2TilesLen 30528
extern const unsigned short level2Tiles[15264];

#define level2MapLen 8192
extern const unsigned short level2Map[4096];

#define level2PalLen 512
extern const unsigned short level2Pal[256];

#endif // GRIT_LEVEL2_H

//}}BLOCK(level2)

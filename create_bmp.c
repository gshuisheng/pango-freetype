#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "create_bmp.h"

struct palette_t
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char reserved;
}palette;

int create_bmp_file(FT_Bitmap *bitmap, char *filename)
{
	int palette_size = sizeof(palette);
	bmp_file_t bmp_file_header = {
	0x4d42,
	0, 
	0,
	0,
	54 
    };
	bmp_info_t bmp_info_header = {
	40,
	0, 
	0, 
	1,
	8,
	0,
	0,
	0,
	0,
	0,
	0
    };
    
    FILE *fp;
    
    fp = fopen(filename, "wb");
    if(NULL == fp)
    {
		fprintf(stderr, "%s:%d:fopen\n", __FILE__, __LINE__);
    }
    
    bmp_info_header.bmp_width = bitmap->width;
    bmp_info_header.bmp_height = bitmap->rows;
    bmp_info_header.bmp_size = (abs(bitmap->pitch))*(bitmap->rows);

    bmp_file_header.file_size = bmp_info_header.bmp_size + 54;
//    bmp_file_header.data_offset = 

    fprintf(stdout, "file_header size: %d   info_header size: %d\n", sizeof(bmp_file_t), sizeof(bmp_info_t));
    fprintf(stdout, "file_size %d\n", bmp_file_header.file_size);
    switch( bitmap->pixel_mode )
    {
	case FT_PIXEL_MODE_MONO :
	    bmp_info_header.bpp = 1;
	    fprintf(stdout, "pixel_mode:mono\n");
	    break;
	case FT_PIXEL_MODE_GRAY :
	    bmp_file_header.file_size += palette_size;
	    bmp_file_header.data_offset = 54 + palette_size;
	    bmp_info_header.bpp = 8;
	    fprintf(stdout, "pixel_mode:gray\n");
	    break;
	case FT_PIXEL_MODE_GRAY2 :
	    bmp_info_header.bpp = 2;
	    fprintf(stdout, "pixel_mode:gray2\n");
	    break;
	case FT_PIXEL_MODE_GRAY4 :
	    bmp_info_header.bpp = 4;
	    fprintf(stdout, "pixel_mode:gray4\n");
	    break;
	case FT_PIXEL_MODE_LCD :
	    bmp_info_header.bpp = 24;
	    fprintf(stdout, "pixel_mode:LCD\n");
	    break;
	case FT_PIXEL_MODE_BGRA :
	    bmp_info_header.bpp = 32;
	    fprintf(stdout, "pixel_mode:LCD\n");
	    break;
	default:
	    break;
    }

    fwrite(&bmp_file_header, 1, sizeof(bmp_file_t), fp);
    fwrite(&bmp_info_header, 1, sizeof(bmp_info_t), fp);
    if( FT_PIXEL_MODE_GRAY == bitmap->pixel_mode )
    {
	int i;
	for(i=0; i<256; i++)
	{
		palette.red = i;
		palette.green = i;
		palette.blue = i;
		fwrite(&palette, 1, palette_size, fp);
	}
    	        
    }
    
    
//    fwrite(bitmap->buffer, 1, bmp_info_header.bmp_size, fp);

    int i;
    int cnt = 0;
    
    for(i=(bmp_info_header.bmp_size-bitmap->pitch); i>=0; i=i-bitmap->pitch)
    {
	fwrite(bitmap->buffer+i, 1, bitmap->pitch, fp);
//	printf("**i**=%d\n", i);
//	cnt++;
    }
//    printf("cnt=%d, height=%d\n", cnt, bmp_info_header.bmp_height);
    fclose(fp);
    
}


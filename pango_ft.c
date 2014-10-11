/*
  Text layouting and rendering with Pango
  ---------------------------------------
  reference :http://www.roxlu.com/2014/046/rendering-text-with-pango--cairo-and-freetype
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <freetype/ftbitmap.h>
#include <pango/pangoft2.h>

#include "create_bmp.h"
 
#define USE_FREETYPE 1
#define USE_RGBA  1
 
int main() {

	PangoContext* context = NULL;
	PangoLayout* layout = NULL;
	PangoFontDescription* font_desc = NULL;
	PangoFontMap* font_map = NULL;
	FT_Bitmap bmp = {0};

	int stride = 0;
	int width = 320;
	int height = 80;

	/* ------------------------------------------------------------ */
	/*                   I N I T I A L I Z E                        */
	/* ------------------------------------------------------------ */

	/* FT buffer */
	FT_Bitmap_New(&bmp);
	bmp.rows = height;
	bmp.width = width;

	bmp.buffer = (unsigned char*)malloc(bmp.rows * bmp.width*4);
	if (NULL == bmp.buffer) {
		printf("+ error: cannot allocate the buffer for the output bitmap.\n");
		exit(EXIT_FAILURE);
	}

	bmp.pitch = ((width + 3) & -4);
	bmp.pixel_mode = FT_PIXEL_MODE_GRAY; 

	printf("**pitch**: %d\n", bmp.pitch);


	/* ------------------------------------------------------------ */
	/*               D R A W   I N T O  C A N V A S                 */
	/* ------------------------------------------------------------ */
	/*1.fontmap*/ 
	font_map = pango_ft2_font_map_new();
	if (NULL == font_map) {
	printf("+ error: cannot create the pango font map.\n");
	exit(EXIT_FAILURE);
	}
	/*2.context */
	context = pango_font_map_create_context(font_map);
	if (NULL == context) {
		printf("+ error: cannot create pango font context.\n");
		exit(EXIT_FAILURE);
	}

	/* 3.create layout object. */
	layout = pango_layout_new(context);
	if (NULL == layout) {
		printf("+ error: cannot create the pango layout.\n");
		exit(EXIT_FAILURE);
	}

	/*4.create the font description @todo the reference does not tell how/when to free this */
	font_desc = pango_font_description_from_string("Station 35");
	pango_layout_set_font_description(layout, font_desc);
	pango_font_map_load_font(font_map, context, font_desc);
	pango_font_description_free(font_desc);

	/* set the width around which pango will wrap */
	printf("PANGO_SCALE = %d\n", PANGO_SCALE);
	pango_layout_set_width(layout, 10240 * PANGO_SCALE);
	pango_layout_set_height(layout,10240 * PANGO_SCALE);
	printf("PANGO_SCALE = %d\n", PANGO_SCALE);

	char khmer_text[128] = "";
	FILE *fp;
	fp = fopen("Khmer.txt", "rb");
	if(NULL == fp)
	{
		perror("fopen");
		exit(-1);
	}
	fread(khmer_text, 1, 3, fp);
	fread(khmer_text, 1, sizeof(khmer_text), fp);
	fclose(fp);


	char text[2048] = "";
	/* write using the markup feature */
	sprintf(text, ""
			"<span foreground=\"black\" font_family=\"Station\""
			"font=\"30\" >"
			"<tt>%s</tt>"
			"</span>"
			"<span foreground=\"#00FF00\" letter_spacing=\"2048\">"
			"ab c</span>", khmer_text);

	printf("text:\n %s\n", text);
	/* write using the markup feature */
//	const gchar* test_text = ""
//		"<span foreground=\"black\" font_family=\"Station\" \
//		font=\"30\" letter_spacing=\"1024\">"
//		"<tt>ជ្រើសរើសជា </tt>"
//		"</span>"
//		"<span font_family=\"sans\"  letter_spacing=\"500\" \
//		font_weight=\"light\"> SANS</span>"
//		"<span foreground=\"#00FF00\" letter_spacing=\"2048\"> ab c</span>""";
//	printf("test_text:\n %s\n", test_text);

	pango_layout_set_markup(layout, text, -1);

	/* render */
	pango_ft2_render_layout(&bmp, layout, 0, 0);

	/* ------------------------------------------------------------ */
	/*               O U T P U T  A N D  C L E A N U P              */
	/* ------------------------------------------------------------ */

	/* show bitmap info */
	printf("rows: %d\n", bmp.rows);
	printf("width: %d\n", bmp.width);
	printf("pitch: %d\n", bmp.pitch);
	printf("pixel_mode: %d\n", bmp.pixel_mode);
	printf("num_grays: %d\n", bmp.num_grays);
	printf("palette_mode: %d\n", bmp.palette_mode);

	create_bmp_file(&bmp, "test_pango_ft.bmp");
	return 0;
}

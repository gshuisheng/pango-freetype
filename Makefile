  FONTCONFIG_CFLAGS = -I/usr/local/include -I/usr/local/include/freetype2  
  FONTCONFIG_LIBS = -L/usr/local/lib -lfontconfig -lfreetype  
  FREETYPE_CFLAGS = -I/usr/local/include/freetype2 -I/usr/local/include   -I/usr/local/include -I/usr/local/include/freetype2  
  FREETYPE_LIBS = -L/usr/local/lib -lfreetype   -L/usr/local/lib -lfontconfig -lfreetype  
  GLIB_CFLAGS = -pthread -I/usr/local/include/glib-2.0 -I/usr/local/lib/glib-2.0/include   
  GLIB_LIBS = -pthread -L/usr/local/lib -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  
  HARFBUZZ_CFLAGS = -I/usr/local/include/harfbuzz  
  HARFBUZZ_LIBS = -L/usr/local/lib -lharfbuzz  
  
  PANGO_CFALGS = -I/usr/include/pango-1.0/ 
  PANGO_LIBS = -L/usr/local/lib -lpango-1.0 -lpangoft2-1.0 -lpangoxft-1.0 -lpangocairo-1.0
  CAIRO_CFALGS = -I/usr/include/cairo/
  CAIRO_LIBS = -L/usr/lib/i386-linux-gnu/ -lcairo
  CFLAGS = -I /usr/include -I ./
  
  SRC = pango_ft.c
  BIN = pango_ft 
  OBJ1 = pango_ft.o
  OBJ2 = create_bmp.o

$(BIN): $(OBJ1) $(OBJ2) 
	gcc -W -o $@ $^ $(FONTCONFIG_CFLAGS) $(FREETYPE_CFLAGS) \
		$(GLIB_CFLAGS) $(HARFBUZZ_CFLAGS) \
		$(PANGO_CFALGS) $(CAIRO_CFALGS)   \
		$(CFLAGS)  \
		$(FONTCONFIG_LIBS) $(FREETYPE_LIBS) \
		$(GLIB_LIBS) $(HARFBUZZ_LIBS) \
		$(PANGO_LIBS) \
		$(CAIRO_LIBS)
	rm $(OBJ1) $(OBJ2)

$(OBJ1):  $(SRC) create_bmp.h
	gcc -W $(FONTCONFIG_CFLAGS) $(FREETYPE_CFLAGS) \
		$(GLIB_CFLAGS) $(HARFBUZZ_CFLAGS) \
		$(PANGO_CFALGS) $(CAIRO_CFALGS)   \
		$(CFLAGS)  \
		$(FONTCONFIG_LIBS) $(FREETYPE_LIBS) \
		$(GLIB_LIBS) $(HARFBUZZ_LIBS) \
		$(PANGO_LIBS) $(CAIRO_LIBS)  -c $(SRC)

$(OBJ2): create_bmp.c create_bmp.h
	gcc  -W $(FREETYPE_CFLAGS) \
		$(GLIB_CFLAGS) \
		$(CFLAGS)  \
		$(FONTCONFIG_LIBS) $(FREETYPE_LIBS) -c create_bmp.c
	


clean:
	rm -rf $(OBJ) $(BIN) *.out *.o

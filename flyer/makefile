CC = gcc
CFLAGS = -g -Wall 

INCDIRS = -I/usr/X11R6/include `sdl-config --cflags` \
-Isrc -Isrc/graphics -Isrc/general -Isrc/math -Isrc/game \
-Isrc/physics -Isrc/splash_screen -Isrc/menu -Isrc/score_screen

LIBDIRS = -L/usr/X11R6/	`sdl-config --libs`
 
LIBS = -lX11 -lXi -lXmu -lGL -lGLU -lm -lglut -lGLEW -lGLU

OBJDIR = bin
SRCDIR = src

OBJS = $(OBJDIR)/main.o	\
	$(OBJDIR)/general/list_t.o	\
	$(OBJDIR)/general/fifo_t.o	\
	$(OBJDIR)/graphics/model_t.o	\
	$(OBJDIR)/graphics/renderer_t.o \
	$(OBJDIR)/graphics/fire_t.o \
	$(OBJDIR)/graphics/load_texture.o \
	$(OBJDIR)/general/game_system_t.o \
	$(OBJDIR)/splash_screen/splash_screen_t.o \
	$(OBJDIR)/score_screen/score_screen_t.o \
	$(OBJDIR)/general/utilties.o \
	$(OBJDIR)/general/printw.o \
	$(OBJDIR)/game/game_t.o \
	$(OBJDIR)/game/control_handler_t.o \
	$(OBJDIR)/game/aircraft_t.o \
	$(OBJDIR)/game/camera_t.o \
	$(OBJDIR)/game/segment_t.o \
	$(OBJDIR)/game/pipe_t.o \
	$(OBJDIR)/menu/menu_t.o \
	$(OBJDIR)/menu/main_menu_create.o \
	$(OBJDIR)/math/vector3_t.o \
	$(OBJDIR)/math/matrix44_t.o \
	$(OBJDIR)/graphics/light_t.o \
	$(OBJDIR)/graphics/default_game_renderer_settings.o\
	$(OBJDIR)/physics/body_t.o \

all:	flyer

$(OBJDIR)/%.o:	$(SRCDIR)/%.c  $(SRCDIR)/%.h 
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@ 

flyer:	$(OBJS)
	$(CC) $(CFLAGS) $(INCDIRS) $(LIBDIRS) $(LIBS) $(OBJS) -o flyer 

clean:
	rm bin/*.o
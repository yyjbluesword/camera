#!makefile

TARGET := libcamera
DEFS :=
INC := -I$(mcserver_dir)/include -I$(mcserver_dir)
LIBS := 
CFLAGS = '-Wall'
all: version.h $(TARGET)

version.h: FORCE
	@echo "generate version.h"
	@./gen_version_h.sh > $@

FORCE:

$(TARGET): camera.c
	$(CC) -fPIC $(CFLAGS) -shared $(DEFS) $(INC) $^ $(LIBS) -o $@.so

clean:
	rm -rf $(TARGET).so
install:
	cp $(TARGET).so $(mcserver_dir)/src/mcserver_plugin


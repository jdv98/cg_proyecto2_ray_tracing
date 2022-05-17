#Directorios
OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src

#Archivos
FILES = main keys\
	read_file\
	cargar_figuras\
	estructuras\
	ray_tracer\
	vector_normal_figura

OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(FILES))
OUTPUT=$(BIN_DIR)/main

######
CFLAGS=-I/usr/local/Mesa-3.4/include `pkg-config --cflags MagickWand`
LDLIBS=-lX11 -lglut -lGLU -lGL -lm -lXext -lXmu -lpthread `pkg-config --libs MagickWand`
LDFLAGS=-L/usr/local/Mesa-3.4/lib -L/usr/X11R6/lib

######
$(OUTPUT): $(OBJECTS)
	mkdir -p bin
	gcc $(OBJECTS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p obj
	gcc -g -c -MMD $(CFLAGS) $< -o $@


-include $(OBJ_DIR)/*.d

run: $(OUTPUT)
	./$(OUTPUT) $(w) $(h)

valgrind: $(OUTPUT)
	valgrind -s ./$(OUTPUT) $(w) $(h)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

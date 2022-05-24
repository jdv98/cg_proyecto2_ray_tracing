#Directorios
OBJ_DIR=obj
BIN_DIR=bin
SRC_DIR=src

#Archivos
FILES = main\
	read_file\
	cargar_figuras\
	estructuras\
	ray_tracer\
	escritura\
	vector_normal_figura

OBJECTS=$(patsubst %, $(OBJ_DIR)/%.o, $(FILES))
OUTPUT=$(BIN_DIR)/main

######
CFLAGS=`pkg-config --cflags MagickWand`
LDLIBS=-lm `pkg-config --libs MagickWand`
LDFLAGS=

######
$(OUTPUT): $(OBJECTS)
	mkdir -p bin
	gcc $(OBJECTS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p obj
	gcc -g -c -MMD $(CFLAGS) $< -o $@


-include $(OBJ_DIR)/*.d

run: $(OUTPUT)
	./$(OUTPUT) $(i) $(t) $(w) $(h)

valgrind: $(OUTPUT)
	valgrind -s ./$(OUTPUT) $(i) $(t) $(w) $(h)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

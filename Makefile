# Files
SRC = src/main.c src/ui.c src/calculate.c src/global.c
OBJ = $(SRC:.c=.o)

# Target
TARGET = GTK_CALCULATOR

# Compiler flags
CFLAGS = -I include `pkg-config --cflags gtk4`
LDFLAGS = `pkg-config --libs gtk4`

# Rules
$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(TARGET) $(LDFLAGS)


%.o: %.c
	gcc -c $< -o $@ $(CFLAGS) 

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)




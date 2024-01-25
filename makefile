CC = g++ 
CFLAGS = -Wall 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJFILES = Board.o Shnake.o game.o main.o
TARGET = shnake 

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

run:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) && ./$(TARGET)
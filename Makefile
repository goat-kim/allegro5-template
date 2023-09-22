CC := gcc
OBJS := main.o

TARGET = allegro5_template
LIBS := allegro-5 allegro_font-5
CFLAGS := -Wall `pkg-config --cflags --libs $(LIBS)`

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET) $(CFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -f *.o

CC = g++
CFLAGS = -Wall -std=c++11

TARGET = matrix

all: $(TARGET)

$(TARGET): matrix.cpp
	$(CC) $(CFLAGS) matrix.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
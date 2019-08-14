CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -shared

SRCS = ./Source
HEADRS = ./Source/API
TARGET_LIB = galapagos.so

all: $(TARGET_LIB)

$(TARGET_LIB): genetic_factory.o galapagos.o
	$(CC) $(LDFLAGS) -o $(TARGET_LIB) galapagos.o genetic_factory.o

galapagos.o: $(SRCS)/galapagos.cpp genetic_factory.h
	$(CC) $(CFLAGS) $(SRCS)/galapagos.cpp

genetic_factory.o: $(SRCS)/Factory/genetic_factory.cpp
	$(CC) $(CFLAGS) $(SRCS)/Factory/genetic_factory.cpp

clean:
	-rm -f $(TARGET_LIB) galapagos.o genetic_factory.o

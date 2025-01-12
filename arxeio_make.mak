# Metaglwttistis
CC = gcc
# Flags metaglwttisth
CFLAGS = -Wall -Wextra -std=c99
# To programma mas
SRC = e_shop_askisi.c
# Vivliothikes
TARGET = e_shop
# Tropos pou tha trexei to make
$(TARGET): $(SRC) e_shop.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Kalesma entolis clean
clean:
	rm -f $(TARGET)

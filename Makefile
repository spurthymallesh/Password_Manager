	CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/main.c \
      src/register.c \
      src/login.c \
      src/file.c \
      src/utils.c \
      src/sha256.c \
      src/encryption.c \
      src/vault.c

TARGET = password_manager

LDFLAGS = -lcrypto

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
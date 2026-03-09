CC = gcc
CFLAGS = `sdl2-config --cflags --libs` -lm

# Default target
raytracing:  main.c raytracing.c
	$(CC) main.c raytracing.c -o raytracing $(CFLAGS)

# Strict target
strict: main.c raytracing.c
	$(CC) -Wall -Wextra -Werror main.c raytracing.c -o raytracing $(CFLAGS)
# Debug target
debug: main.c raytracing.c
	$(CC) -g -Wall -Wextra main.c raytracing.c -o raytracing $(CFLAGS)
# Clean target
clean:
	rm -f ./raytracing
.PHONY: clean strict
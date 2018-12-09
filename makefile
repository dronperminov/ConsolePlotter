COMPILER=gcc

all:
	$(COMPILER) -Wall console_plotter.c -o console_plotter

clean:
	rm console_plotter
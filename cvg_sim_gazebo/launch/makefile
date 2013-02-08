all:	grid_cells 

grid_cells:	grid_cells.cpp
	g++ -o grid_cells grid_cells.cpp `pkg-config opencv --cflags --libs`

clean: 
	rm -f grid_cells


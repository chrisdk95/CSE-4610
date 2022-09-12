project4:Sdisk.o Filesys.o main.o block.o shell.o table.o


	c++ -o project4 Sdisk.o Filesys.o main.o block.o shell.o table.o -o proj4
Sdisk.o:Sdisk.cpp
	c++ -c Sdisk.cpp

Filesys.o:Filesys.cpp
	c++ -c Filesys.cpp

block.o:block.cpp
	c++ -c block.cpp

shell.o:shell.cpp
	c++ -c shell.cpp

table.o:table.cpp
	c++ -c table.cpp
	
main.o:main.cpp
	c++ -c main.cpp

clean:
	rm *.o
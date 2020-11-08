OPTIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Set_Species.o Species.o Set_Cluster.o Cluster.o
	@g++ -o program.exe program.o Set_Species.o Species.o Set_Cluster.o Cluster.o
	@rm *.o

program.o: program.cc Species.hh Cluster.hh Set_Cluster.hh Set_Species.hh
	@g++ -c program.cc $(OPTIONS)

Species.o: Species.cc Species.hh
	@g++ -c Species.cc $(OPTIONS)

Set_Species.o: Set_Species.cc Set_Species.hh
	@g++ -c Set_Species.cc $(OPTIONS)

Cluster.o: Cluster.cc Cluster.hh
	@g++ -c Cluster.cc $(OPTIONS)

Set_Cluster.o: Set_Cluster.cc Set_Cluster.hh
	@g++ -c Set_Cluster.cc $(OPTIONS)

practica.tar: program.cc Set_Species.hh Set_Species.cc Species.hh Species.cc Cluster.hh Set_Cluster.hh Makefile BinTree.hh program.exe celeste.sabater.html.zip
	@tar -cvf practica.tar program.exe program.cc Set_Species.hh Set_Species.cc Species.hh Species.cc Cluster.hh Cluster.cc Set_Cluster.hh Set_Cluster.cc Makefile BinTree.hh celeste.sabater.html.zip

clean:
	@rm *.o
	@rm *.exe

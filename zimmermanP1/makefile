P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean :
	rm *.o P1.out *.gch

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf zimmermanP1
	mkdir zimmermanP1
	cp Project1.cpp zimmermanP1
	cp LexicalAnalyzer.h zimmermanP1
	cp LexicalAnalyzer.cpp zimmermanP1
	#cp aidsTest.ss zimmermanP1
	cp SyntacticalAnalyzer.h zimmermanP1
	cp SyntacticalAnalyzer.cpp zimmermanP1
	#cp SetLimits.cpp zimmermanP1
	#	cp SetLimits.h zimmermanP1
	cp makefile zimmermanP1
	cp README.txt zimmermanP1
	tar cfvz zimmermanP1.tgz zimmermanP1
	#cp zimmermanP1.tgz ~tiawatts/cs460drop

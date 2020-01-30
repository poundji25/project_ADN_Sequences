partie1 : A
	./A sequences_ADN

partie2 : B
	./B sequences_ADN
			
A : main1.o sequence.o distance.o
	gcc -o  A main1.o sequence.o distance.o -Wall

B : main2.o sequence.o distance.o famille.o
	gcc -o  B main2.o sequence.o distance.o famille.o -Wall

main2.o : main2.c sequence.h distance.h famille.h
	gcc main2.c  -c -o main2.o -Wall
		
main1.o : main1.c sequence.h distance.h 
	gcc main1.c -c -o main1.o -Wall

sequence.o : sequence.c sequence.h 
	gcc sequence.c  -c -o sequence.o -Wall

distance.o : distance.c distance.h
	gcc distance.c -c -o distance.o -Wall

famille.o : famille.h famille.c sequence.h distance.h
	gcc famille.c -c -o famille.o -Wall
	
clean : 
	rm *.o
	rm -f partie1
	rm -f partie2
	rm -f A
	rm -f B	

CXX ?= g++
CFLAGS =  -lpq 
LIB=-I/usr/include/postgresql
OBJS= db_svm.o db_connection.o svm.o config.o

svm.o: src/svm.cpp src/svm.h
	$(CXX) $(CFLAGS) -c src/svm.cpp
teste: src/teste.c svm.o
	$(CXX) $(CFLAGS) src/teste.c svm.o -o teste -lm

db_connection.o: src/db_connection.c src/db_connection.h
	$(CXX) -c src/db_connection.c $(LIB) $(CFLAGS)

db_svm.o: src/db_svm.c src/db_svm.h
	$(CXX) -c src/db_svm.c $(LIB) $(CFLAGS)	

config.o: src/config.h	src/config.c
	$(CXX) -c src/config.c

gen_classifier_model: src/gen_classifier_model.c db_svm.o db_connection.o svm.o config.o
	$(CXX) -o gen_classifier_model src/gen_classifier_model.c db_svm.o db_connection.o svm.o config.o -lconfuse $(LIB) $(CFLAGS)

run_test: src/run_test.c db_svm.o db_connection.o svm.o config.o
	$(CXX) -o run_test src/run_test.c db_svm.o db_connection.o svm.o config.o -lconfuse $(LIB) $(CFLAGS)
 
classifier: src/classifier.c  $(OBJS)
	$(CXX) -o classifier src/classifier.c $(OBJS) -lconfuse $(LIB) $(CFLAGS) 

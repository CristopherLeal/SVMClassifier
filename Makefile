CXX ?= g++
CFLAGS =  -lpq 
LIB=-I/usr/include/postgresql
OBJS= db_svm.o db_connection.o svm.o config.o utils.o

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

utils.o: src/utils.h src/utils.c
	$(CXX) -c src/utils.c

gen_classifier_model: src/gen_classifier_model.c $(OBJS)
	$(CXX) -o gen_classifier_model src/gen_classifier_model.c $(OBJS) -lconfuse $(LIB) $(CFLAGS)

run_test: src/run_test.c $(OBJS)
	$(CXX) -o run_test src/run_test.c $(OBJS) -lconfuse $(LIB) $(CFLAGS)
 
classifier: src/classifier.c  $(OBJS)
	$(CXX) -o classifier src/classifier.c $(OBJS) -lconfuse $(LIB) $(CFLAGS) 

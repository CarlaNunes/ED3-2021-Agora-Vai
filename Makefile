all : 
	gcc main.c ./IO/IO.c ./auxiliar/functions.c ./Ferramentas/Ferramentas.c -o exe  

run : all
	./exe

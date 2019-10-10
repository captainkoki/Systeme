#Makefile de lecturefichierOFF
#R. RAFFIN, A2SE M3101

compilateur = g++
preproc_options = -g -c -Wall -O3
link_options = -O3 -Wall -lm
main = lecturefichierOFF

all: $(main)
	@echo "\ncompilation terminee"

$(main): objetsOFF.o iFaceTri.o point3.o vector3.o
	@echo "--- compilation de $@ ..."
	$(compilateur) $(main).cpp $^ $(link_options) -o $@

objetsOFF.o: objetsOFF.cpp objetsOFF.h
	$(compilateur) $(preproc_options) $<

point3.o: point3.cpp point3.h
	$(compilateur) $(preproc_options) $<

vector3.o: vector3.cpp vector3.h
	$(compilateur) $(preproc_options) $<

iFaceTri.o: iFaceTri.cpp iFaceTri.h
	$(compilateur) $(preproc_options) $<

clean:
	rm -f *.o $(main) *~

archive:
	tar czvf $(main).tgz *.cpp *.h Makefile

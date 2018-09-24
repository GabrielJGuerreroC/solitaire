# Adapta la siguiente variable a la ruta de tu instalación de DeSIGNAR
DSG = ~/DeSIGNAR

# Ajusta esto con tu compilador
CXX = clang++ -std=c++14

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings \
       -Wno-parentheses 

FLAGS = -DDEBUG -D_GLIBCXX__PTHREADS -g -O0 $(WARN) -Wno-invalid-source-encoding

INCLUDE = -I. -I $(DSG)/include 

LIBS = -L $(DSG)/lib -lDesignar

all: test

test: solitaire.H test.C
	$(CXX) $(FLAGS) $(INCLUDE) $@.C -o $@ $(LIBS)

clean:
	$(RM) *~ test

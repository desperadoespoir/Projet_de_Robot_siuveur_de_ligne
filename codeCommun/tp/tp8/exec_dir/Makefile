
#Executable makefile

# Name of our project
# (use a single word, e.g. 'myproject')
PROJECTNAME=execute

# Source files
# List C/C++/Assembly source files:
# (list all files to compile, e.g. 'a.c b.cpp as.S'):
# Use .cc, .cpp or .C suffix for C++ files, use .S
# (NOT .s !!!) for assembly source code files.
PRJSRC= main.cpp
#Chemin des fichiers de la librairies
LIBDIR =../lib_dir

# additional includes (e.g. -I/path/to/mydir)
INC=-I$(LIBDIR)

# libraries to link in (e.g. -lmylib)
LIBS= -L$(LIBDIR)  -lstatique


LDFLAGSTRG =
CCTRG = avr-gcc

##### automatic target names ####
TRG=$(PROJECTNAME).out
DUMPTRG=$(PROJECTNAME).s



include ../Makefile_common


$(TRG): $(OBJDEPS)
	$(CCTRG) $(LDFLAGSTRG) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)


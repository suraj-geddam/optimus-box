.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
RM 	= rm
ECHO	= /bin/echo

# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/myobjs
BINDIR = $(PROJECT_ROOT)/mybins
DOCDIR = $(PROJECT_ROOT)/doc
PRODIR = $(PROJECT_ROOT)/profile

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

# Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-pg -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
CPPFLAGSO= -O3 -Wall -fno-strict-aliasing
CPPFLAGSO+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%_opt.o)
RCLEAN := $(wildcard $(DOCDIR)/report.*[!tex][!bib] texput.log)
PCLEAN := $(wildcard $(DOCDIR)/presentation.*[!tex] texput.log)

.PHONY: all exe exe_opt codeDoc report profile clean distclean

all: debugsetup exe exe_opt

debugsetup: dirs b2ddebug

finalsetup: dirs b2dfinal

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CPPFLAGS) -c $< -o $@

$(OOBJS): $(OBJDIR)/%_opt.o : $(SRCDIR)/%.cpp
	@$(CC) $(CPPFLAGSO) -c $< -o $@

exe: debugsetup $(OBJS)
	@$(CC) -pg -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	@mv exe $(BINDIR)/;

exe_opt: finalsetup $(OOBJS)
	@$(CC) -o $@ $(LDFLAGS) $(OOBJS) $(LIBS)
	@mv exe_opt $(BINDIR)/;

dirs:
	@mkdir -p mybins
	@mkdir -p myobjs
	
b2ddebug:
	@cd $(EXTERNAL_ROOT); \
	cd src; \
	rm -rf Box2D; \
	tar -xf Box2D.tgz; \
	cd Box2D; \
	mkdir -p build251; \
	cd build251; \
	cmake -DCMAKE_BUILD_TYPE=Debug ../; \
	make; \
	make install;
	
b2dfinal:
	@cd $(EXTERNAL_ROOT); \
	cd src; \
	rm -rf Box2D; \
	tar -xf Box2D.tgz; \
	cd Box2D; \
	mkdir -p build251; \
	cd build251; \
	cmake -DCMAKE_BUILD_TYPE=Release ../; \
	make; \
	make install;

profile:
	@gprof $(BINDIR)/exe $(PROJECT_ROOT)/gmon.out > $(PRODIR)/profile.txt
	@python3 $(PRODIR)/gprof2dot.py $(PRODIR)/profile.txt > $(PRODIR)/out.dot
	@dot -Tpng $(PRODIR)/out.dot -o $(PRODIR)/callgraph.png
	@rm $(PRODIR)/out.dot $(PROJECT_ROOT)/gmon.out 

report:
	@cd $(DOCDIR); \
	pdflatex report.tex; \
	bibtex report; \
	pdflatex report.tex; \
	pdflatex report.tex; \
	pdflatex presentation.tex; \
	rm presentation.aux; \
	rm presentation.out; \

release: exe_opt codeDoc report
	
codeDoc:
	@$(ECHO) -n "Generating Doxygen Documentation of Group-26 ...  "
	@$(RM) -rf doc/html
	@doxygen $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"
	
clean:
	@$(RM) -rf $(OBJDIR)/*.o $(BINDIR)/* $(DOCDIR)/html
	@$(RM) -rf $(RCLEAN) $(PCLEAN)

distclean: clean
	@$(RM) -rf $(OBJDIR) $(BINDIR) $(EXTERNAL_ROOT)/src/Box2D/

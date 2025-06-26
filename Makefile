PROGRAM = petert13
CC = g++
CFLAGS = -std=c++14 -Wall -Wpedantic -Wextra -g
# -fsanitize=address

SRCDIR = src
OBJDIR = tmp

SRC = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
HDR = $(shell find $(SRCDIR)/ -type f -name '*.h')

all: compile run

doc: $(SRC) $(HDR)
	doxygen

compile: $(PROGRAM)

$(OBJDIR)/main.o:  src/main.cpp src/CManager.h src/CMenu.h src/CDifficulty.h src/CScoreBoard.h src/CGame.h \
 src/CDumbGhost.h src/CSmartGhost.h src/CPatternGhost.h src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h src/CWall.h \
 src/CTeleport.h src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CManager.o: src/CManager.cpp src/CManager.h src/CMenu.h src/CDifficulty.h src/CScoreBoard.h src/CGame.h \
 src/CDumbGhost.h src/CSmartGhost.h src/CPatternGhost.h src/CGhost.h src/CMap.h src/CCoin.h \
 src/CCherry.h src/CWall.h src/CTeleport.h src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h \
 src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CMenu.o: src/CMenu.cpp src/CMenu.h src/CDifficulty.h src/CScoreBoard.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CGame.o: src/CGame.cpp src/CGame.h src/CDifficulty.h src/CDumbGhost.h \
 src/CSmartGhost.h src/CPatternGhost.h src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h src/CWall.h src/CTeleport.h \
 src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CMap.o: src/CMap.cpp src/CMap.h src/CCoin.h src/CCherry.h src/CWall.h src/CTeleport.h src/CEmpty.h \
 src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CDifficulty.o: src/CDifficulty.cpp src/CDifficulty.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CScoreBoard.o: src/CScoreBoard.cpp src/CScoreBoard.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CGhost.o: src/CGhost.cpp src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h src/CWall.h src/CTeleport.h \
 src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CDumbGhost.o: src/CDumbGhost.cpp src/CDumbGhost.h src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h \
 src/CWall.h src/CTeleport.h src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CSmartGhost.o: src/CSmartGhost.cpp src/CSmartGhost.h src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h \
 src/CWall.h src/CTeleport.h src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CPatternGhost.o: src/CPatternGhost.cpp src/CPatternGhost.h src/CGhost.h src/CMap.h src/CCoin.h src/CCherry.h \
 src/CWall.h src/CTeleport.h src/CEmpty.h src/CGhostSpawn.h src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CTile.o: src/CTile.cpp src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CCoin.o: src/CCoin.cpp src/CCoin.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CEmpty.o: src/CEmpty.cpp src/CEmpty.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CGhostSpawn.o: src/CGhostSpawn.cpp src/CGhostSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CPacmanSpawn.o: src/CPacmanSpawn.cpp src/CPacmanSpawn.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CTeleport.o: src/CTeleport.cpp src/CTeleport.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CWall.o: src/CWall.cpp src/CWall.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CCherry.o: src/CCherry.cpp src/CCherry.h src/CTile.h src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CPacMan.o: src/CPacMan.cpp src/CPacMan.h src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<
$(OBJDIR)/CPosition.o:: src/CPosition.cpp src/CPosition.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run:
	./$(PROGRAM)
#	valgrind --leak-check=full --show-leak-kinds=all

clean:
	rm -f $(PROGRAM)
	rm -rf $(OBJDIR)
	rm -rf doc
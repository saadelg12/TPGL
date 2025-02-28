# Nom de l'exécutable
EXEC = calculatrice

# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Fichiers sources et objets
SRC = main.cpp Lexer.cpp Etat.cpp Automate.cpp
OBJ = $(SRC:.cpp=.o)

# Règle de compilation principale
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compilation des fichiers sources
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Nettoyage complet
mrproper: clean
	rm -f calculatrice

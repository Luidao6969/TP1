# Diretórios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin

# Arquivos fonte
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Ordenador.cpp \
       $(SRC_DIR)/Sort.cpp \
       $(SRC_DIR)/Estatisticas.cpp

# Nome do executável
EXEC = $(BIN_DIR)/tp1.out

# Flags do compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I$(INC_DIR)

# Regra padrão
all: $(EXEC)

# Como compilar o executável
$(EXEC): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Limpeza dos binários
clean:
	rm -rf $(BIN_DIR)

# Rodar o programa
run: all
	./$(EXEC)

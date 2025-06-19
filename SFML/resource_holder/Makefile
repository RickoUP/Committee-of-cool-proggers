TARGET = main
SRC = main.cpp game.cpp  

CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include

# Путь к библиотекам
LIB_DIR = /usr/local/lib

# Статические библиотеки SFML (в правильном порядке!)
SFML_LIBS = \
	$(LIB_DIR)/libsfml-graphics-s.a \
	$(LIB_DIR)/libsfml-window-s.a \
	$(LIB_DIR)/libsfml-system-s.a \
	$(LIB_DIR)/libsfml-audio-s.a

# Сторонние зависимости SFML
EXT_LIBS = -lGL -lpthread -ldl -lfreetype -lX11 -lXrandr -lXi -lXcursor -ludev -lasound -lFLAC -lvorbis -logg

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS) $(EXT_LIBS)

clean:
	rm -f $(TARGET)

go: clean all
	./$(TARGET)

./PHONY: clean go



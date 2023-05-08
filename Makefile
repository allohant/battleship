GXX = g++
CXXFLAGS = -g -Wall 
OBJMODULES = coords.o utility.o deck.o boat.o field.o char.o aichar.o playerchar.o engine.o textengine.o
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
main: main.cpp $(OBJMODULES)
	$(CXX) $(CXXFLAGS) $^ -o $@

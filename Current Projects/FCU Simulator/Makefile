CXXFLAGS += --std=c++17

start: Projectile.o Launcher.o ballisticCalc.o Profile.o Display.o main.o *.h
	$(CXX) $(CXXFLAGS) Projectile.o Launcher.o ballisticCalc.o Profile.o Display.o main.o -o start

Projectile.o: Projectile.cpp *.h
	$(CXX) $(CXXFLAGS) -c Projectile.cpp -o Projectile.o

Launcher.o: Launcher.cpp *.h
	$(CXX) $(CXXFLAGS) -c Launcher.cpp  -o Launcher.o

ballisticCalc.o: ballisticCalc.cpp *.h
	$(CXX) $(CXXFLAGS) -c ballisticCalc.cpp  -o ballisticCalc.o

Profile.o: Profile.cpp *.h
	$(CXX) $(CXXFLAGS) -c Profile.cpp  -o Profile.o

Display.o: Display.cpp *.h
	$(CXX) $(CXXFLAGS) -c Display.cpp  -o Display.o

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp  -o main.o

clean:
	rm -f *.o *.gch *~ a.out start

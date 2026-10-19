MainFiles = main.cpp AuthService.cpp AuthService.h release.h
SOURCEFiles = main.cpp 

LDLIBS = -lssl -lcrypto

main: $(MainFiles)
	g++ -Wall -g $(SOURCEFiles) -o main  $(LDLIBS)
	



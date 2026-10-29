# Cross-platform Makefile for ReleaseGuard
# Works on Linux and macOS. On macOS it finds Homebrew's OpenSSL automatically.

CXX      = g++
CXXFLAGS = -Wall -g -std=c++17
LDLIBS   = -lssl -lcrypto
LDFLAGS  =

# OpenSSL lives outside the default compiler path on macOS (Homebrew),
# so add its include/lib directories only when building on a Mac.
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  OPENSSL_PREFIX := $(shell brew --prefix openssl 2>/dev/null)
  ifneq ($(OPENSSL_PREFIX),)
    CXXFLAGS += -I$(OPENSSL_PREFIX)/include
    LDFLAGS  += -L$(OPENSSL_PREFIX)/lib
  endif
endif

all: main

# release.h #includes AuthService.cpp, so the app builds from main.cpp alone.
main: main.cpp REPL.h release.h AuthService.cpp AuthService.h
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LDFLAGS) $(LDLIBS)

# Standalone demos
releasedemo: releaseDemo.cpp release.h
	$(CXX) $(CXXFLAGS) releaseDemo.cpp -o releasedemo $(LDFLAGS) $(LDLIBS)

requestdemo: requestDemo.cpp release.h
	$(CXX) $(CXXFLAGS) requestDemo.cpp -o requestdemo $(LDFLAGS) $(LDLIBS)

demos: releasedemo requestdemo

clean:
	rm -f main releasedemo requestdemo

.PHONY: all demos clean

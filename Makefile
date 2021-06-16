# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs
#
# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it
#

# make uses the modification dates to determine
# is the programs need to be re-built

# all: blokus blokus_v0 --- example of how to do all

#This is the main build

blokus: blokus.cpp
	g++ -g -std=c++20 blokus.cpp -o blokus

blokus_v0: blokus_v0.cpp
	g++ -g -std=c++20 blokus_v0.cpp -o blokus_v0
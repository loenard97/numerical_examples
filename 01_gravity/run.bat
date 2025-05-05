@echo off

g++ -ID:\Projects\Cpp\numerical -o main main.cpp
main.exe | python plot.py
# aspect-sort
C++ application to quickly sort many images by their aspect ratios
Written on linux using VSCode

# require
DevIL (image library)

cpp17 (for filesystem commands)

# compile-command
'g++ -std=c++17 $fullFileName sorter.cpp -lIL -lstdc++fs && ./a.out '

# notes
Some of the code is non portable, check or remove them (noteably system("clear"))

This readme will change!
COMPILE="g++ -g -std=c++17 src/*.cpp -I include -o bin/a.out -lSDL2 -lSDL2_image -ldl"
echo ${COMPILE}
eval $COMPILE


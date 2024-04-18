COMPILE="g++ -g -std=c++17 src/*.cpp -I include -o bin/a.out -lSDL2 -lSDL2_image -lSDL2_ttf -ldl"
echo ${COMPILE}
eval $COMPILE


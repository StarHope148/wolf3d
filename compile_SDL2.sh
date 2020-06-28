if [ ! -f SDL2-2.0.12/Makefile ]
then
    echo "Compiling SDL2..."
	cd SDL2-2.0.12 && ./configure && make && sudo make install
else
    echo "SDL2 already ready"
fi
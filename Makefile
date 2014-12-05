all:
	#Arm cross compile
	arm-none-linux-gnueabi-gcc -O3 -static edge_filter.c -lm -o edge_filter
	
gcc:
	#native compile
	gcc -O3 -static edge_filter.c -lm -o edge_filter
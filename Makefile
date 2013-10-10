objects=main.o jpegsize.o

ifilter : main.o jpegsize.o
	cc -g -o ifiter main.o jpegsize.o

main.o : main.c jpegsize.h
	cc -g -c main.c

jpegsize.o : jpegsize.c
	cc -g  -c jpegsize.c

clean:
	rm ifilter main.o jpegsize.o
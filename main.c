#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "jpegsize.h"

/* Less than */
int lt(x, y) {
	printf("%d < %d\n", x, y);
	return x < y;
}

/* Greater than */
int gt(x, y) {
	printf("%d > %d\n", x, y);
	return x > y;
}
/* Alwazy return true */
int ignore(x, y) {
	return -1;
}

typedef int (*fptr)();

fptr generate_comparator(int val) {
	return val > 0 ? &gt : &lt;
}

int main (int argc, char const *argv[])
{
	int c, w, h, fw, fh;
	fptr w_comp = &ignore;
	fptr h_comp = &ignore;
	while((c = getopt(argc, argv, "w:h:")) != -1) {
		switch(c) {
			case 'w':
			w = atoi(optarg);
			w_comp = generate_comparator(w);
			w = abs(w);
			printf("Width: %d\n", w);
			break;
			case 'h':
			h = atoi(optarg);
			h_comp = generate_comparator(h);
			h = abs(h);
			printf("Height: %d\n", h);
			break;
			default:
			printf("other options %c\n", c);
		}
	}
	printf("gt:\t%p\n", (void *)gt);
	printf("lt:\t%p\n", (void *)lt);
	printf("ignore:\t%p\n", (void *)ignore);
	printf("w_comp:\t%p\n", (void *)w_comp);
	printf("h_comp:\t%p\n", (void *)h_comp);
	char buf[BUFSIZ];
	fgets(buf, BUFSIZ, stdin);
	size_t len = strlen(buf)-1;
	if (buf[len] == '\n') {
		buf[len] = '\0';
		printf("%s\n", buf);
		FILE *f = fopen(buf, "r");
		scanhead(f, &fw, &fh);
		fclose(f);
		if (w_comp(fw, w) && h_comp(fh, h)) {
			printf("%s\n", buf);
		}
	} else {
		printf("Line was truncated\n");
	}
	return 0;
}
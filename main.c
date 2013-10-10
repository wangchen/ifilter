#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "jpegsize.h"

//#define DEBUG

/* Less than */
int eq(x, y) { return x == y; }

/* Less than */
int lt(x, y) { return x < y; }

/* Greater than */
int gt(x, y) { return x > y; }

/* Alwazy return true */
int ignore(x, y) { return -1; }

typedef int (*fptr)();

void generate_comparator(char *val, fptr * comp, int *size) {
	*size = abs(atoi(val));
	printf("%d\n", val[0]=='-');
	switch(val[0]){
		case '+':
		*comp = &gt;
		break;
		case '-':
		*comp = &lt;
		break;
		default:
		*comp = &eq;
	}
}

int main (int argc, char * const argv[])
{
	int c, w, h, fw, fh;
	fptr w_comp = &ignore;
	fptr h_comp = &ignore;
	while((c = getopt(argc, argv, "w:h:")) != -1) {
		switch(c) {
			case 'w':
			generate_comparator(optarg, &w_comp, &w);
			break;
			case 'h':
			generate_comparator(optarg, &h_comp, &h);
			break;
			default:
			printf("other options %c\n", c);
		}
	}
#ifdef DEBUG
	printf("eq: %p gt: %p lt: %p ig: %p\n", eq, gt, lt, ignore);
	printf("w_comp:\t%p\n", (void *)w_comp);
	printf("h_comp:\t%p\n", (void *)h_comp);
#endif
	char buf[BUFSIZ];
	fgets(buf, BUFSIZ, stdin);
	size_t len = strlen(buf)-1;
	if (buf[len] == '\n') {
		buf[len] = '\0';
		FILE *f = fopen(buf, "r");
		scanhead(f, &fw, &fh);
		fclose(f);
		if (w_comp(fw, w) && h_comp(fh, h)) {
			printf("%dx%d\t%s\n", fw, fh, buf);
		}
	} else {
		printf("Line was truncated\n");
	}
	return 0;
}
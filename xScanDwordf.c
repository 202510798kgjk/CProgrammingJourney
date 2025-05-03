#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef unsigned int DWORD;

bool xScanDwordf(DWORD* p);

int main() {
	int someInteger1;
	bool result = xScanDwordf(&someInteger1);
	if (result == NULL) {
		printf("Error.");
		return -1;
	}
	else {
		printf("%d", someInteger1);
	}

	return 0;
}


bool xScanDwordf(DWORD* p) {
	size_t capacity = 4;
	unsigned char* buf = malloc(capacity);
	if (buf == NULL) {
		return false;
	}
		DWORD count = 0;
		while (1) {
			if (count == capacity - 1) {
				capacity += capacity;
				buf = realloc(buf, capacity);
				if (buf == NULL) {
					return false;
				}
			}
			char ch = getchar();
			if (0x30<=ch&&ch<=0x39) {
				ch = (ch - 0x30);
				*(buf + count) = ch;
			}
			else if (ch == '\n') {
				break;
			}
			else {
				return false;
			}
			count++;
		}
		DWORD* result = malloc(capacity*count);
		for (auto i = 0;i < count;i++) {
			*(result + i) = (*(buf + i))&0xFF;
			for (auto j = i;j <count-1;j++)
				*(result + i) = (*(result + i)) * 10;
		}
		for (auto i = 0;i < count;i++) {
			*p += *(result + i);
		}

	return true;
}

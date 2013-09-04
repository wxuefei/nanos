#include "user_vga.h"
#include "syscall.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "user.h"

int atoi(const char *a);

int main(int argc, char **argv) {

	int color = atoi(argv[1]) << 8;
	int row = atoi(argv[2]);

	sys_add_pages(1);
	*(uint64_t*)USER_HEAP = 50;

	for (int i = 0; i < 80; i++) {

		if (i == 20 && row == 12) {
			print(row, i, color, "*");
			sys_exit();
		}

		print(row, i, color, "\07");
		usleep(100000);
	}

	sys_exit();
}

int atoi(const char *a) {
	int num = 0;
	int mult = 1;
	int len = strlen(a);

	for (int i = len - 1; i >= 0; i--) {
		char c = a[i];
		num += (c - '0') * mult;
		mult *= 10;
	}
	return num;
}

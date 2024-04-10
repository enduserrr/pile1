#include <stdio.h>
#include <unistd.h> // for pid_t
#include <limits.h> // for INT_MAX, INT_MIN

/**
 * @brief	cd /Users/name/ ; cc <file.c> -o <program_name>
 * */

int main() 
{
	printf("_______________________");
	printf("\n- INT_MAX\t: %d\n", INT_MAX);
	printf("- INT_MIN\t: %d\n", INT_MIN);
	printf("- INT\t\t: %zu bytes\n", sizeof(int));
	printf("- PID_T\t\t: %zu bytes\n", sizeof(pid_t));
	printf("- SIZE_T\t: %zu bytes\n", sizeof(size_t));
	printf("- LONG INT\t: %zu bytes\n", sizeof(long int));
	printf("- LONG LONG INT\t: %zu bytes\n", sizeof(long long int));
	printf("- DOUBLE\t: %zu bytes\n", sizeof(double));
	printf("- LONG DOUBLE\t: %zu bytes\n", sizeof(long double));
	printf("- INT\t\t: %zu bytes\n", sizeof(int));
	printf("- CHAR\t\t: %zu bytes\n", sizeof(char));
	printf("- UNSIGNED CHAR\t: %zu bytes\n", sizeof(unsigned char));
	printf("_____________________________________________");
	printf("\nA byte = 8 bits & byte max value: 255 (11111111)\n");
	printf("0b00>0b01>0b10>0b11>0b100>0b101>0b111>0b1000>0b1001...\n\n");
	return (0);
}
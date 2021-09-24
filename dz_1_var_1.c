#include <stdio.h>

int main(void) {
	int num, a;
	int n = 0, k = 0;	//n and k - counters
	int rez[11] = {0};	//rez [11] - array to fill 1 and 0

	printf("Please enter your number less than 1023: ");

	scanf("%d", &num);	//user input

	if (num >= 1024){
		printf("Error: The entered number is too large!\n");
		return 0;
	}

	if (num < 0){
		printf("Error: The entered number less than zero!\n");
		return 0;
	}

	a = num;

	while (a != 1){		//count the number of bits
		if (a % 2 == 1){
			a = (a - 1) / 2;
			n++;
		}
		else {
			a /= 2;
			n++;
		}
	}

	k = n;

	while(num != 1){	//fill the array in reverse order
		if (num % 2 == 1){
			rez[k--] = 1;
			num = (num - 1) / 2;
		}
		else{
			rez[k--] = 0;
			num /= 2;
		}
	}

	rez[k] = 1;
	rez[n + 1] = '\0';

	printf("Answer: ");

	for (int i = 0; i < n + 1; i++){	//result output
		printf("%d", rez[i]);
	}
	printf("\n");
	return 0;
}

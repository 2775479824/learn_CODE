#include "Stack.h"


int main()
{
	ST stack;
	STInit(&stack);

	STPush(&stack, 1);
	STPush(&stack, 2);
	STPush(&stack, 3);
	STPush(&stack, 4);
	STPush(&stack, 5);

	while (!STEmpty(&stack))
	{
		int top = STTop(&stack);
		printf("%d ", top);
		STPop(&stack);

	}


	STDestroy(&stack);

	return 0;
}
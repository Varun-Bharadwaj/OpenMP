#include "LinkedListTask.h"

void append(int value, Node** h)
{
	Node* temp = new Node();
	temp->info = value;
	temp->next = NULL;

	Node* aux = *h;
	if (aux == NULL)
	{
		*h = temp;
	}
	else {
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = temp;
	}
}

void Process(Node* p)
{
#pragma omp critical
	cout << p->info << " by thread " << omp_get_thread_num() << endl;
}
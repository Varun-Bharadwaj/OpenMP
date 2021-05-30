#include "LinkedListTask.h"
int tasks_created = 0;
int main()
{
	//Build a linked List
	Node* head = NULL;

	for (int i = 1; i < 9; i++)
	{
		append(i, &head);
	}

	//Sequential Access
	cout << "Sequential Access" << endl;
	Node* tmp = head;
	while (tmp != NULL)
	{
		Process(tmp);
		tmp = tmp->next;
	}

	cout << "Parallel Access" << endl;
#pragma omp parallel
	{
		cout << "Inside Parallel Region: Thread: " << omp_get_thread_num() << endl;
#pragma omp single
		{
			cout << "Inside Single Region: Thread: " << omp_get_thread_num() << endl;
			Node* tmp = head;
			while (tmp != NULL)
			{
#pragma omp task
				{
					cout << "Inside Task: Thread: " << omp_get_thread_num() << endl;
					Process(tmp);
				}
				tmp = tmp->next;
			}
		}
	}

//Fibonacci Sequence

	int N = 20;
	chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	cout << "Sequential: " << fibSeq(N) << endl;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elasped_seconds = end - start;
	cout << "Sequential Time: " << (elasped_seconds.count() * 1000000) << " usecs" << endl;

	//Parallel Execution
	tasks_created = 0;
	start = std::chrono::system_clock::now();
#pragma omp parallel
	{
#pragma omp single
		{
			cout << "Parallel: " << fibPar(N) << endl;
		}
	}
	end = std::chrono::system_clock::now();
	elasped_seconds = end - start;
	cout << "Parallel Time: " << (elasped_seconds.count() * 1000000) << " usecs" << endl;
	cout << "Number of tasks created: " << tasks_created << endl;
	return 0;
}
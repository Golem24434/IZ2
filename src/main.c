#include "../include/testy/find_letters.h"


int main() {
	srand(time(NULL));

	void *handle = dlopen("./find_let.so", RTLD_LAZY);

	int (*funcpt)();

    *(void **)(&funcpt) = dlsym(handle, "multiprocess_find_topic");

	letter*		letters[MAX_NUMBER_LETTERS];
	date_frame 	start_letters,end_letters;
	str_topics* topics1;

	fill_in_elements(letters);
	 int sc=1;
	// printf("Выберите с какого года искать письма?[2010-2020]\n");
	// if (scanf("%d", &sc) == -1) return -1;
	// start_letters.year 	= sc-2011;
	// printf("Выберите с какого месяца искать письма?[1-12]\n");
	// if (scanf("%d", &sc) == -1) return -1;
	// start_letters.month = sc;
	// printf("Выберите с какого дня искать письма?[1-30]\n");
	// if (scanf("%d", &sc) == -1) return -1;
	// start_letters.day 	= sc;

	printf("Выберите до какого года искать письма?[2010-2020]\n");
	if (scanf("%d", &sc) == -1) return -1;
	end_letters.year 	= sc-2011;
	printf("Выберите до какого месяца искать письма?[1-12]\n");
	if (scanf("%d", &sc) == -1) return -1;
	end_letters.month = sc;
	printf("Выберите до какого дня искать письма?[1-30]\n");
	if (scanf("%d", &sc) == -1) return -1;
	end_letters.day 	= sc;
	// end_letters.year 	=start_letters.year;
	// end_letters.month = start_letters.month;
	// end_letters.day = start_letters.day + 15;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	// end_letters.year 	= 9;
	// end_letters.month 	= 4;
	// end_letters.day 	= 25;
	int id;
	printf("Выберите id пользователя?[1-30]\n");
	if (scanf("%d", &id) == -1) return -1;

	int numb_start = binary_search(letters, date_in_key(start_letters),MAX_NUMBER_LETTERS);
	int numb_end = binary_search(letters, date_in_key(end_letters),MAX_NUMBER_LETTERS);
	topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 15);
	printf("Многопроцессорная реализация?[0/1]\n");
	if (scanf("%d", &sc) == -1) return -1;
	while (sc != 0 && sc != 1) {
		if (sc == 1) {
			topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 15);
		} else {
			if (sc == 0) {
				topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 15);
			} else {
				printf("Введите 0 или 1.\n");
				if (scanf("%d", &sc) == -1) return -1;
			}
		}
	}

    for (int i=0;i<topics1->number;++i) {
       printf("%d-ая тема пользователя %s\n",i,topics1->topics[i]);
    }
	if (sc == 1) {	
		free(topics1);
	} else {
		if (sc == 0 ) {
			munmap(topics1, getpagesize());
		}
	}
	return 0;
}
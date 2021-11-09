#include "../include/testy/find_letters.h"


int main() {
	srand(time(NULL));

	void *handle = dlopen("./find_let.so", RTLD_LAZY);

	int (*funcpt)();

    *(void **)(&funcpt) = dlsym(handle, "multiprocess_find_topic");

	letter*		letters[MAX_NUMBER_LETTERS];
	date_frame 	start_letters,end_letters;

	fill_in_elements(letters);

	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;

	end_letters.year = 9;
	end_letters.month = 4;
	end_letters.day = 25;

	int numb_start = binary_search(letters, date_in_key(start_letters),MAX_NUMBER_LETTERS);
	int numb_end = binary_search(letters, date_in_key(end_letters),MAX_NUMBER_LETTERS);

	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int* topics2 = multiprocess_find_topic(letters, numb_start, numb_end, 10);

	printf("%d\n",equality_test(topics1,topics2));
	free(topics1);

	// for (int i=0;i<1000;++i) {
	// 	if (topics1[i] == 1) {
	// 		printf("%d\n",i);
	// 	} 
	// }
	// for (int i = 0;i<1000;++i) {
    // 	free(letters[i]);
  	// }

	munmap(topics1, getpagesize());
	munmap(topics2, getpagesize());
	
	return 0;
}
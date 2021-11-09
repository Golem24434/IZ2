#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <dlfcn.h>

#define MAX_NUMBER_LETTERS 1000000
#define MAX_NUMBER_TOPICS 1000


typedef struct letter letter;
typedef struct date_frame date_frame; 
typedef struct str_topics str_topics; 

struct str_topics {
	int number;
	char topics[100][10];
};


struct date_frame {
	int year;
	int month;
	int day;
};

struct letter {
	int		sender_id;
	int		ecipient_id[10];
	char	topic[10];
	int		number_ecipient;
	date_frame	date;	
};

int testing_letters_el(letter** letters, int N);

int date_in_key(date_frame date);

int binary_search(letter** k, int key, int N);

int get_number_process();

int fill_in_elements(letter** letters);

str_topics* singleprocces_find_topic(letter** letters, int start,int  end, int number_user);

str_topics* multiprocess_find_topic(letter** letters, int start,int  end, int number_user);

int equality_test(str_topics* topics1,str_topics* topics2);
#endif
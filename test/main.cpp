#include "gtest/gtest.h"

extern "C" {
#include "../include/testy/find_letters.h"
}

TEST(date_in_key, ok) {
	date_frame date;
	date.year = 10;
	date.month = 5;
	date.day = 3;  
	EXPECT_EQ(date_in_key(date), 3753);
}

TEST(binary_search, ok) {
	letter*		let[200];
	testing_letters_el(let,200);
	EXPECT_EQ(binary_search(let,753,200), 46);
  	for (int i = 0;i<200;++i) {
    	free(let[i]);
  	}
}

TEST(binary_search_null, not_ok) {
	letter**	let=NULL;
	EXPECT_EQ(binary_search(let,753,200), -1);
}

TEST(fill_in_elements, ok) {
	letter** letters = NULL;
	EXPECT_EQ(fill_in_elements(letters), -1);
}


TEST(multi_and_singleproc, not_ok) {
	letter* letters[MAX_NUMBER_LETTERS];
	fill_in_elements(letters);
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	int	numb_start = binary_search(letters, date_in_key(start_letters),MAX_NUMBER_LETTERS);
	int numb_end = binary_search(letters, date_in_key(end_letters),MAX_NUMBER_LETTERS);
	str_topics* topics1 = singleprocces_find_topic(letters, numb_start, numb_end,7);
	str_topics* topics2 = multiprocess_find_topic(letters, numb_start, numb_end,6);
	EXPECT_EQ(equality_test(topics1,topics2),0);

	for (int i = 0;i<MAX_NUMBER_LETTERS;++i) {
    	free(letters[i]);
  	}
	free(topics1);
	munmap(topics2,getpagesize());
}

TEST(singleproc_200el, ok) {
	letter*		letters[200];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,200);
	int	numb_start = binary_search(letters, date_in_key(start_letters),200);
	int numb_end = binary_search(letters, date_in_key(end_letters),200);
	str_topics* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=4;
	topics2->topics[0][0]='D';
	topics2->topics[1][0]='E';
	topics2->topics[2][0]='F';
	topics2->topics[3][0]='G';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<200;++i) {
    	free(letters[i]);
  	}
	free(topics1);
	free(topics2);
}



TEST(singleproc_1000el, ok) {
	letter*		letters[1000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 0;
	start_letters.day 	= 0;
	end_letters.year = 8;
	end_letters.month = 12;
	end_letters.day = 0;
	testing_letters_el(letters,1000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),1000);
	int numb_end = binary_search(letters, date_in_key(end_letters),1000);
	str_topics* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=2;
	topics2->topics[0][0]='D';
	topics2->topics[1][0]='E';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<1000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
	free(topics2);
}


TEST(singleproc_10000el, ok) {
	letter*		letters[10000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 11;
	start_letters.day 	= 0;
	end_letters.year = 8;
	end_letters.month = 12;
	end_letters.day = 0;
	testing_letters_el(letters,10000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),10000);
	int numb_end = binary_search(letters, date_in_key(end_letters),10000);
	str_topics* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=1;
	topics2->topics[0][0]='F';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<10000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
	free(topics2);
}

TEST(singleproc_100000el, ok) {
	letter*		letters[100000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 11;
	start_letters.day 	= 0;
	end_letters.year 	= 8;
	end_letters.month 	= 12;
	end_letters.day 	= 0;
	testing_letters_el(letters,100000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),100000);
	int numb_end = binary_search(letters, date_in_key(end_letters),100000);
	str_topics* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=3;
	topics2->topics[0][0]='G';
	topics2->topics[1][0]='A';
	topics2->topics[2][0]='B';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<100000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
	free(topics2);
}





TEST(multi_1000el, ok) {
	letter*		letters[1000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 0;
	start_letters.day 	= 0;
	end_letters.year = 8;
	end_letters.month = 12;
	end_letters.day = 0;
	testing_letters_el(letters,1000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),1000);
	int numb_end = binary_search(letters, date_in_key(end_letters),1000);
	str_topics* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=2;
	topics2->topics[0][0]='D';
	topics2->topics[1][0]='E';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<1000;++i) {
    	free(letters[i]);
  	}
	munmap(topics1,getpagesize());
	free(topics2);
}


TEST(multi_10000el, ok) {
	letter*		letters[10000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 11;
	start_letters.day 	= 0;
	end_letters.year = 8;
	end_letters.month = 12;
	end_letters.day = 0;
	testing_letters_el(letters,10000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),10000);
	int numb_end = binary_search(letters, date_in_key(end_letters),10000);
	str_topics* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=1;
	topics2->topics[0][0]='F';
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<10000;++i) {
    	free(letters[i]);
  	}
	munmap(topics1,getpagesize());
	free(topics2);
}

TEST(multi_100000el, ok) {
	letter*		letters[100000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 8;
	start_letters.month = 11;
	start_letters.day 	= 0;
	end_letters.year 	= 8;
	end_letters.month 	= 12;
	end_letters.day 	= 0;
	testing_letters_el(letters,100000);
	int	numb_start = binary_search(letters, date_in_key(start_letters),100000);
	int numb_end = binary_search(letters, date_in_key(end_letters),100000);
	str_topics* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 15);
	str_topics* topics2 = (str_topics*) malloc(sizeof(str_topics));
	topics2->number=3;
	topics2->topics[0][0]='G';
	topics2->topics[1][0]='G';
	topics2->topics[2][0]='B';
	EXPECT_EQ(equality_test(topics1,topics2),0);
	for (int i = 0;i<100000;++i) {
    	free(letters[i]);
  	}
	munmap(topics1,getpagesize());
	free(topics2);
}


TEST(singleprocces_find_topic_null, not_ok) {
	letter** letters = NULL;
	int condition = (singleprocces_find_topic(letters,1,1000,17) == NULL);
	ASSERT_TRUE(condition);
}

TEST(multi_find_topic_null, not_ok) {
	letter** letters = NULL;
	int condition = (multiprocess_find_topic(letters,1,1000,17) == NULL);
	ASSERT_TRUE(condition);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



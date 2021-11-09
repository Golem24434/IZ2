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
	testing_letters_el(let,200,17);
	EXPECT_EQ(binary_search(let,753,200), 49);
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

TEST(multi_and_singleproc, ok) {
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
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end,7);
	int* topics2 = multiprocess_find_topic(letters, numb_start, numb_end,7);
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<MAX_NUMBER_LETTERS;++i) {
    	free(letters[i]);
  	}
	free(topics1);
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
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end,7);
	int* topics2 = multiprocess_find_topic(letters, numb_start, numb_end,6);
	EXPECT_EQ(equality_test(topics1,topics2),-1);
	for (int i = 0;i<MAX_NUMBER_LETTERS;++i) {
    	free(letters[i]);
  	}
	free(topics1);
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
	testing_letters_el(letters,200,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),200);
	int numb_end = binary_search(letters, date_in_key(end_letters),200);
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<200;++i) {
    	free(letters[i]);
  	}
	free(topics1);
}



TEST(singleproc_1000el, ok) {
	letter*		letters[1000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,1000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),1000);
	int numb_end = binary_search(letters, date_in_key(end_letters),1000);
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<1000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
}

TEST(singleproc_10000el, ok) {
	letter*		letters[10000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,10000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),10000);
	int numb_end = binary_search(letters, date_in_key(end_letters),10000);
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<10000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
}

TEST(singleproc_100000el, ok) {
	letter*		letters[100000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,100000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),100000);
	int numb_end = binary_search(letters, date_in_key(end_letters),100000);
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<100000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
}

TEST(singleproc_1000000el, ok) {
	letter*		letters[1000000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,1000000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),1000000);
	int numb_end = binary_search(letters, date_in_key(end_letters),1000000);
	int* topics1 = singleprocces_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<1000000;++i) {
    	free(letters[i]);
  	}
	free(topics1);
}

TEST(multiproc_1000el, ok) {
	letter*		letters[1000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,1000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),1000);
	int numb_end = binary_search(letters, date_in_key(end_letters),1000);
	int* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<1000;++i) {
    	free(letters[i]);
  	}
}

TEST(multiproc_10000el, ok) {
	letter*		letters[10000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,10000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),10000);
	int numb_end = binary_search(letters, date_in_key(end_letters),10000);
	int* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<10000;++i) {
    	free(letters[i]);
  	}
}

TEST(multiproc_100000el, ok) {
	letter*		letters[100000];
	date_frame 	start_letters,end_letters;
	start_letters.year 	= 0;
	start_letters.month = 0;
	start_letters.day 	= 1;
	end_letters.year 	= 9;
	end_letters.month 	= 4;
	end_letters.day 	= 25;
	testing_letters_el(letters,100000,17);
	int	numb_start = binary_search(letters, date_in_key(start_letters),100000);
	int numb_end = binary_search(letters, date_in_key(end_letters),100000);
	int* topics1 = multiprocess_find_topic(letters, numb_start, numb_end, 10);
	int topics2[1000];
	for (int i = 0;i<1000;++i) {
		topics2[i]=0;
 	}
	topics2[17] = 1;
	EXPECT_EQ(equality_test(topics1,topics2),1);
	for (int i = 0;i<100000;++i) {
    	free(letters[i]);
  	}
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



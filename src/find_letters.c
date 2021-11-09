#include "../include/testy/find_letters.h"


int get_number_process() {
 
 unsigned int  eax=11,ebx=0,ecx=1,edx=0;
 
 asm volatile("cpuid"
         : "=a" (eax),
           "=b" (ebx),
           "=c" (ecx),
           "=d" (edx)
         : "0" (eax), "2" (ecx)
         : );

 return eax;
}

int date_in_key(date_frame date) {
 
 int value = (((date.year)*12 + date.month)*30 + date.day);

 return value;
}

int binary_search(letter** k, int key, int N) {
 if (k == NULL) {
  printf("Ошибка! На вход функции binary_search подается нулевой указатель.");
  return -1;
 }
 int left = 0;
 int right = N-1;
 int search = -1;
 while (left <= right) 
   {
     int mid = (left + right) / 2;
  if (k[mid] == NULL) {
   printf("Ошибка! Элемент в массиве является нулевым указателем.");
  }
     if (key == date_in_key(k[mid]->date)) {  
        search = mid;     
        break;            
     }  
     if (key < date_in_key(k[mid]->date)) {    
        right = mid - 1;  
  }
  else {                 
        left = mid + 1;   
  }   
 }
 
   if (search == -1) {    
    if (left == N) {
     left=left-1;
    }
    search = left;
     }
 return search;
}

int fill_in_elements(letter** letters) {
 if (letters == NULL) {
  printf("Ошибка! На вход функции fill_in_elements подается нулевой указатель.");
  return -1;
 }
 for (int i=0;i<MAX_NUMBER_LETTERS;++i) {
  letters[i] = (letter*) malloc(sizeof(letter));
  if (letters[i] == NULL) {
   printf("Ошибка! В функции fill_in_elements %d-ому элементу не выделена память.",i);
   return -1;
  }
 }
 for (int i=0;i<MAX_NUMBER_LETTERS;++i) {
  letters[i]->sender_id = i; 
  letters[i]->number_ecipient = rand() % 7 + 1;
  for (int j = 0; j<letters[i]->number_ecipient; ++j) {
   letters[i]->ecipient_id[j] = rand() % MAX_NUMBER_LETTERS;
  }
  int Y = MAX_NUMBER_LETTERS / 10;
  int M = Y / 12;
  letters[i]->date.year  = i / Y;
  letters[i]->date.month  = (i % Y) / M;
  letters[i]->date.day  = ((i % Y) % M) % 30;
  for (int j=0;j<9;++j) {
    letters[i]->topic[j]  = 65 + rand() % 25 ;
  }
  letters[i]->topic[9] = '\0';
 }
 return 0;
}

str_topics* singleprocces_find_topic(letter** letters, int start,int  end, int number_user) {
 if (letters == NULL) {
  printf("Ошибка! На вход функции singleprocces_find_topic подается нулевой указатель.");
  return NULL;
 }
 str_topics* find_topics = (str_topics*) calloc(MAX_NUMBER_TOPICS,sizeof(str_topics));
 find_topics->number = 0;
 if (find_topics == NULL) {
  printf("Ошибка! В функции singleprocces_find_topic не выделена память.");
  return NULL;
 }
 for (int i=start;i<=end;++i) {
  for (int j=0;j<letters[i]->number_ecipient;++j){
   if (letters[i]->ecipient_id[j] == number_user) {
        for (int o=0;o<9;++o) {
            find_topics->topics[find_topics->number][o] = letters[i]->topic[o];
        }
        find_topics->number = find_topics->number + 1;
   }
  }
 }
 return find_topics;
}

str_topics* multiprocess_find_topic(letter** letters, int start,int  end, int number_user) {
    if (letters == NULL) {
        printf("Ошибка! На вход функции multiprocess_find_topic подается нулевой указатель.");
        return 0;
    }
    long page_size = getpagesize();
    str_topics* shared_memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory == MAP_FAILED) {
        return NULL;
    } 


    int numberOfChildren = get_number_process();
    pid_t *childPids = NULL;
    pid_t p;

    /* Allocate array of child PIDs: error handling omitted for brevity */
    childPids = malloc(numberOfChildren * sizeof(pid_t));

    if (childPids == NULL) {
        return NULL;
    }

    int step=(end-start)/numberOfChildren;
    int begin = start;

    /* Start up children */
    for (int ii = 0; ii < numberOfChildren; ++ii) {
        start = begin + ii*step;
        end = begin + (ii+1)*step;
        if ((p = fork()) == 0) {
            str_topics* topics_singl = singleprocces_find_topic(letters, start, end, number_user);
            for (int i=0;i<topics_singl->number;++i) {
                for (int j=0;j<10;++j) {
                    shared_memory->topics[shared_memory->number][j] = topics_singl->topics[i][j];
                }
                shared_memory->number = shared_memory->number + 1;
            }
            exit(0);
        }
    else {
        childPids[ii] = p;
    }
    }

    /* Wait for children to exit */
    int stillWaiting;
    do {
    stillWaiting = 0;
        for (int ii = 0; ii < numberOfChildren; ++ii) {
        if (childPids[ii] > 0) {
            if (waitpid(childPids[ii], NULL, WNOHANG) != 0) {
                /* Child is done */
                childPids[ii] = 0;
            }
            else {
                /* Still waiting on this child */
                stillWaiting = 1;
            }
        }
        /* Give up timeslice and prevent hard loop: this may not work on all flavors of Unix */
        sleep(0);
        }
    } while (stillWaiting);

    /* Cleanup */
    free(childPids);
    return shared_memory;

}

int testing_letters_el(letter** letters, int N) {

 for (int i=0;i<N;++i) {
  letters[i] = (letter*) malloc(sizeof(letter));
 }

 for (int i=0;i<N;++i) {
  letters[i]->sender_id = i; 
  letters[i]->number_ecipient = 1;
  letters[i]->ecipient_id[0] = i % 50;
  int Y = (N / 10)+1;
  int M = (Y / 12)+1;
  letters[i]->date.year = (int)(i / Y);
  letters[i]->date.month = (int)((i % Y ) / M );
  letters[i]->date.day = (int)(((i % Y) % M ) % 30);
  for (int j=0;j<9;++j) {
    letters[i]->topic[j]  = 65 + i % 7;
  }
  letters[i]->topic[9] = '\0';
 }

 return 0;
}

int equality_test(str_topics* topics1,str_topics* topics2) {
   if (topics1->number == topics2->number) {
      for (int i=0;i<topics1->number;++i) {
         if (topics1->topics[i][0] != topics2->topics[i][0]) {
            return 0;
         }
      }
      return 1;
   } else {
      return 0;
   }
}



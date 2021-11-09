#include "../include/testy/find_letters.h"

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
      printf("Элемент не найден! Искать будем до %d при ключе %d\n", k[search]->sender_id,date_in_key(k[search]->date));
     }
   else {          
      printf("Элемент найден! Искать будем до %d при ключе %d\n", k[search]->sender_id,date_in_key(k[search]->date));
 }
 return search;
}

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
  letters[i]->topic  = rand() % 1000;
 }
 return 0;
}

int* singleprocces_find_topic(letter** letters, int start,int  end, int number_user) {
 if (letters == NULL) {
  printf("Ошибка! На вход функции singleprocces_find_topic подается нулевой указатель.");
  return NULL;
 }
 int* topics = (int*) calloc(MAX_NUMBER_TOPICS,sizeof(int));
 if (topics == NULL) {
  printf("Ошибка! В функции singleprocces_find_topic не выделена память.");
  return NULL;
 }
 for (int i=start;i<=end;++i) {
  for (int j=0;j<letters[i]->number_ecipient;++j){
   if (letters[i]->ecipient_id[j] == number_user) {
    topics[letters[i]->topic] = 1; 
   }
  }
 }
 return topics;
}

int* multiprocess_find_topic(letter** letters, int start,int  end, int number_user) {
 if (letters == NULL) {
  printf("Ошибка! На вход функции multiprocess_find_topic подается нулевой указатель.");
  return 0;
 }
 long page_size = getpagesize();
    printf("%ld\n",page_size); 
    int* shared_memory = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                              MAP_SHARED | MAP_ANONYMOUS, -1, 0);
 if (shared_memory == MAP_FAILED) {
  return NULL;
 }
    int numberOfChildren = get_number_process();
    pid_t *childPids = NULL;
    pid_t p;
 for (int i = 0;i<1000;++i) {
  shared_memory[i]=0;
 }
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
  int* topics = singleprocces_find_topic(letters, start, end, number_user);
  for (int i = 0;i<1000;++i) {
   if (topics[i]==1) {
    shared_memory[i]=1;
   }
  }
  free(topics);
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
    if (childPids[ii] == -1) {return NULL;}
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

int equality_test(int* a, int *b) {
 int ans = 1;
 for (int i=0;i<MAX_NUMBER_TOPICS;++i) {
  if (a[i] != b[i]) {
   ans = -1;
  }
 }
 return ans;
}

int testing_letters_el(letter** letters, int N, int K) {

 for (int i=0;i<N;++i) {
  letters[i] = (letter*) malloc(sizeof(letter));
 }

 for (int i=0;i<N;++i) {
  letters[i]->sender_id = i; 
  letters[i]->number_ecipient = 1;
  letters[i]->ecipient_id[0] = 10;
  int Y = 20;
  int M = 6;
  letters[i]->date.year = (int)(i / Y);
  letters[i]->date.month = (int)((i % Y ) / M );
  letters[i]->date.day = (int)(((i % Y) % M ) % 30);
  letters[i]->topic = K;
 }
 return 0;
}

int testing_letters_1000el(letter** letters) {

 for (int i=0;i<1000;++i) {
  letters[i] = (letter*) malloc(sizeof(letter));
 }

 for (int i=0;i<1000;++i) {
  letters[i]->sender_id = i; 
  letters[i]->number_ecipient = 1;
  letters[i]->ecipient_id[0] = 10;
  int Y = 1000 / 10;
  int M = Y / 12;
  letters[i]->date.year = (int)(i / Y);
  letters[i]->date.month = (int)((i % Y ) / M );
  letters[i]->date.day = (int)(((i % Y) % M ) % 30);
  letters[i]->topic = 17;
 }
 return 0;
}
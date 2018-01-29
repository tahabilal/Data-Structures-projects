
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*
	You can use your text file in readInput method

	fopen("Your text file directory","r")


*/





//define all methods
char* removePunctuation(char *word);
void compare(struct s_word *cmp1,struct s_word *cmp2,struct s_word **result);
void compare(struct s_word *cmp1,struct s_word *cmp2,struct s_word **result,int *counter);
int search(char *word,struct s_word *header);
int search(char *word1,char *word2,struct s_word *header);
int sortedInsert(char *word,struct s_word **header,int *counter);
int insert(char *word,struct s_word **header);
void printList(struct s_word *header,int counter);
char letterReduction(char word);
void readInput(struct s_word **header);

//data field
struct s_word{
	char word[50];
	struct s_word *nextNode;
};

//global variable for linked list header and counter
int countOf2grams,countOfCommonWords = 0;
int inputOrder = 1;
struct s_word *firstHeader,*secondHeader,*resultOf2grams,*resultOfCommonWord;


//print LL
void printList(struct s_word *header,int counter)
{
	struct s_word *iterate;
	iterate = header;
	
	if(header==NULL) printf("Linked list is empty.");
	
	else 
	{
		while(iterate != NULL)
		{
			printf("%s\n",iterate->word);
			iterate = iterate->nextNode;
		}
	}
}

//delete all LL's element
void deleteAll(struct s_word **header)
{
	struct s_word *iterate,*previous;
	
	//if LL empty
	if(*header==NULL) return;
	
	previous = *header;
	iterate = previous->nextNode;
	
	//if LL have one element
	if (iterate == NULL){free(*header); return;} 
	
	//if LL have more than one element
	else 
	{	
		while(iterate != NULL)
		{
			if(iterate->nextNode == NULL) free(iterate);//if remain one element
			free(previous);
			previous = iterate;
			iterate = iterate->nextNode;
		}
	}
	*header == NULL;
	
	
}

//insert element in LL 
int insert(char *word,struct s_word **header)
{
	struct s_word *iterate,*newNode;
	
	// create node to insert and assign values to its fields
	newNode = (struct s_word *) malloc(sizeof(struct s_word));
	word = removePunctuation(word);//remove sign at the end of word
	strcpy(newNode->word,word);//for assign char squence to char array
	newNode->word[0] = letterReduction(newNode->word[0]);//reduction first letter
	newNode->nextNode = NULL;
	
	//if LL empty
	if(*header == NULL) 
	{
		*header = newNode;
		return 1;
	} 
	
	
	//if LL not empty
	else
	{
		iterate = *header;
		while(iterate != NULL)
		{
			if(iterate->nextNode == NULL) {iterate->nextNode = newNode; return 1;}
			iterate = iterate->nextNode ;
		}
		return 1;
	}
	
	return 0;
		
}

//read input from text
void readInput(struct s_word **header)
{
	
	FILE *filePtr;
	char temp[50];//temp string for assign for LL data
	
	if (inputOrder)
	{
		filePtr = fopen("file1.txt","r");//this part can be changed "your text file directory"
		inputOrder -= 1;//for 2. input text
	}
	else  filePtr = fopen("file2.txt","r");//this part can be changed "your text file directory"
		
	
	if(filePtr==NULL) printf("Your input file does not exist! "); //if file pointer is NULL
	
	else //if file pointer is not NULL
		while(!feof(filePtr)){
			fscanf(filePtr,"%s",temp);
			insert(temp,header);//call insert for creat struct and insert LL	
		}
	
	fclose(filePtr);
	
}

//compare two LL for to find same element and create result LL
void compare(struct s_word *cmp1,struct s_word *cmp2,struct s_word **result)
{
	
	struct s_word *iterate;
	iterate = cmp1;

	
	if(iterate == NULL || cmp2 == NULL) printf("LL is empty"); 
	
	else
	{
		while(iterate != NULL)
		{
			if(search(iterate->word,cmp2)) {
				sortedInsert(iterate->word,result,&countOfCommonWords);//result sorted
			}
			iterate = iterate->nextNode;
		}
	}
}

//compare two LL for to find same element and create result LL (overload for 2-grams)
void compare(struct s_word *cmp1,struct s_word *cmp2,struct s_word **result,int *counter)
{
	
	struct s_word *iterate,*previous;
	char *temp;//temp char sequence for using string method as proper
	char a_temp[150];//temp char array for using string method as proper
	previous = cmp1;
	iterate = cmp1->nextNode;

	
	if(previous == NULL || cmp2 == NULL ) printf("LL is empty"); 
	
	else if(iterate == NULL) printf("LL have only one element");
	
	else
	{
		while(iterate != NULL)
		{
			if(search(previous->word,iterate->word,cmp2)) {
				strcpy(a_temp,(temp = strcat(previous->word," ")));// firstly assign a temp array ' ' value
				strcat(a_temp,(temp = iterate->word));//and concatenation second element
				sortedInsert(a_temp,result,counter);//result LL shorted fashion
			}
			previous = iterate;
			iterate = iterate->nextNode;
		}
	}
}

//remove punctuation from all elements
char* removePunctuation(char *word)
{
	int i,length;
	char a_word[50];
	
	length = strlen(word);
	strcpy(a_word,word);
	
	for (i=0; i < length; i++){
		if(a_word[i] < 48 || (a_word[i]<64)&&(a_word[i]>57)) a_word[i] = '\0';//all punctuation ascii value
	}
	
	word = a_word;
	return word;
	
}

//reduction elemts's first letter
char letterReduction(char word)
{
	if(word < 97) word = word + 32;//reduction expression (ascii value)
	return word;

}

//search match element with data
int search(char *word,struct s_word *header)
{
	
	struct s_word *iterate;
	iterate = header;
	
	if(iterate == NULL) return 0;
	
	else{
		while(iterate != NULL)
		{			
			if(!strcmp(iterate->word,word)) return 1;// search successful
			iterate = iterate->nextNode;
		}
	}
	// key non-existent
	return 0;
		 
}

//insert elemt in LL (sorted fashion for result LL)
int sortedInsert(char *word,struct s_word **header,int *counter)
{
	struct s_word *iterate,*newNode,*previous;
	
	// create node to insert and assign values to its fields
	newNode = (struct s_word *) malloc(sizeof(struct s_word));
	strcpy(newNode->word,word);//for assign char squence to char array
	newNode->nextNode = NULL;
	
	//if LL empty
	if(*header == NULL)  *header = newNode;

	
	//if LL not empty
	else
	{
		iterate = *header;
		while(iterate != NULL && strcmp(newNode->word,iterate->word)>0)
		{
			previous = iterate;
			iterate = iterate->nextNode ;
		}

		if(iterate != NULL && strcmp(newNode->word,iterate->word)==0) return 0;//existent key
		
		// insert node in a sorted fashion
		if(iterate != NULL) newNode->nextNode = iterate;
		
		// if value to insert is the least in LL then have header point to node
		if(*header==iterate) *header = newNode;
		
		// otherwise insert node in correct position
		else previous->nextNode = newNode;

	}
	*counter += 1;//count of match
	return 1;
}

//search match element with data(overload for 2-grams)
int search(char *word1,char *word2,struct s_word *header)
{
	struct s_word *iterate,*previous;
	previous = header;
	iterate = header->nextNode;
	
	if(iterate == NULL || previous == NULL) return 0;
	
	else{
		while(iterate != NULL)
		{	
			if(!strcmp(previous->word,word1) && !strcmp(iterate->word,word2)) return 1;//succesful search
			previous = iterate;
			iterate = iterate->nextNode;				
		}
	}
	// key non-existent
	return 0;
}

main(void)
{
	char operations;
	
	// read file and construct LL
	readInput(&firstHeader); 
	readInput(&secondHeader);
	compare(firstHeader,secondHeader,&resultOfCommonWord); 
	compare(firstHeader,secondHeader,&resultOf2grams,&countOf2grams);
	printf("\n>>");
  	printf("1: Print common words; 2: Print common 2-grams; 3: Exit; \n>>");
	
	do
	{	
		scanf("%c",&operations);
		switch(operations)
		{
			case '1': printf("the number of common words: %d\n\n",countOfCommonWords);
				      printf("the common words are:\n\n");
					  printList(resultOfCommonWord,countOfCommonWords); 
					  printf("\n>>");
					break;
			case '2': printf("the number of common 2-grams: %d\n\n",countOf2grams);
					  printf("the common 2-grams are:\n\n");
					  printList(resultOf2grams,countOf2grams); 
					  printf("\n>>");
					break;
			case '3': deleteAll(&firstHeader);
					  deleteAll(&secondHeader);
					  deleteAll(&resultOf2grams);
					  deleteAll(&resultOfCommonWord);
					break;	
			
			//default : ;
		}
	}while(operations!= '3');


}

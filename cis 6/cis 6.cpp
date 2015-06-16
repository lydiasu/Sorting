//
//  main.cpp
//  cis 6
//
//  Created by Su Yuqing on 4/19/14.
//  Copyright (c) 2014 Su Yuqing. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <sys/resource.h>
#include <iomanip>

const int PR(10);

using namespace std;


struct entryType
{
    
	string	ssn;
	string fname;
	string lname;
    int dob;
    string state;
    int phoneNum1;
    int phoneNum2;
    int phoneNum3;
    
};

struct nodeType
{
	entryType info;
	nodeType *next;
	nodeType *back;
};

struct listType
{
	nodeType *first;
	nodeType *last;
	int count;
};


// Extra credits.

void searchDLLname (listType *lst)
{
    nodeType *current;
    
    string name;
    
    cout << "Enter a name exactly correct: ";
    
    cin >> name;
    
    cout << endl;
    
    
    current = lst->first;
    while (current != NULL)
    {
        if( current->info.fname == name || current->info.lname == name)
        {
            cout << current->info.ssn << " " << current->info.fname << " " << current->info.lname << " " << current->info.dob << " " << current->info.state << " " << current->info.phoneNum1 << "-" << current->info.phoneNum2 << "-" << current->info.phoneNum3 << endl;
        }
        current = current->next;
    }
    
}

void searchDLLphoneNum (listType *lst)
{
    nodeType *current;
    
    int a, b, c;
    
    cout << "Enter a phone number separated by spaces: ";
    
    cin >> a >> b >> c;
    
    cout << endl;
    
    current = lst->first;
    while (current != NULL)
    {
        if( current->info.phoneNum1 == a && current->info.phoneNum2 == b && current->info.phoneNum3 == c)
        {
            cout << current->info.ssn << " " << current->info.fname << " " << current->info.lname << " " << current->info.dob << " " << current->info.state << " " << current->info.phoneNum1 << "-" << current->info.phoneNum2 << "-" << current->info.phoneNum3 << endl;
        }
        current = current->next;
    }
    
}



double getCPUTime()
{
    struct rusage ruse;
    getrusage(RUSAGE_SELF, &ruse);
    return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 + ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0;
}

int deleteNode(listType *l, nodeType * node);
void searchDelete (listType *lst)
{
    
    nodeType *current;
    
    current = lst->first;
    
    while (current)
    {
        if(current->info.phoneNum1 > 199 && current->info.phoneNum1 < 300)
        {
            nodeType *delete_node = current;
            current = current->next;
      	    int result = deleteNode(lst, delete_node);
            if(result == 1)
                lst->count--;
        }
        else
            current = current->next;
    }
}




int deleteNode(listType *l, nodeType * node)
{
    
    bool found = false;
	//1st node
    if (l->first == NULL)
        cout << "Cannot delete from an empty list." << endl;
	else if(l->first == node)
	{
        found = true;
		nodeType *nodeNext = node->next;
		nodeNext->back = NULL;
		l->first = nodeNext;
		delete 	node;
		return 1;
	}
	
	//last node
	else if(l->last == node)
	{
        found = true;
		nodeType *nodeBack = node->back;
		nodeBack->next = NULL;
		l->last = nodeBack;
		delete 	node;
		return 1;
	}
    
	else
	{
        found = true;
		node->back->next = node->next;
		node->next->back = node->back;
        
		delete node;
		return 1;
        
	}
    
    if (!found)
        cout << "The item is not in the list." << endl;
    
	return 0;
    
}



void printDataArray(ostream &out, entryType *d, int size) {
    int i;
    entryType *p;
    p = d;
    for(i=0;i<size;i++,p++)
    {
        out << p->ssn<<" " << p->fname <<" "<< p->lname <<" "<< p->dob<<" " << p->state<<" "<< p->phoneNum1<<"-" <<p->phoneNum2 << "-" <<p->phoneNum3<<endl;
        
        
    }
}
void printDLList(ostream &out, listType *l)
{
    nodeType *current;
    current = l->first;
    while (current !=NULL)
    {
        out<<current->info.ssn<< " "<<current->info.fname<<" "<<current->info.lname<<" "<<
        current->info.dob<< " " << current->info.phoneNum1<<"-"<<current->info.phoneNum2<<"-" << current->info.phoneNum3<< endl;
        current=current->next;
    }
}

int my_random_in_range(int min, int max) //range : [min, max)
{
    static bool first = true;
    if ( first )
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (max - min);
}

void insertItem(listType *lst, entryType v)
{
	bool found;
	nodeType *current;					//pointer to traverse the list
	nodeType *trailCurrent;				//pointer just before current
    
	nodeType *newNode = new nodeType;		// pointer to instantiate a node
    
    
	newNode->info= v;
	newNode->next=NULL;
	newNode->back=NULL;
    
	if (lst->first==NULL)
	{
		lst->first = newNode;
		lst->last = newNode;
		lst->count++;
        
	}
	else
	{
		found=false;
		current=lst->first;
		while (current !=NULL && !found)	//search the list
			if (current->info.phoneNum1 > v.phoneNum1 || ((current->info.phoneNum1 == v.phoneNum1) && (current->info.phoneNum2 > v.phoneNum2)) || (( current->info.phoneNum1 == v.phoneNum1) && (current->info.phoneNum2 == v.phoneNum2) &&  (current->info.phoneNum3 > v.phoneNum3))) // CHANGE this!!!!
				
                
				found=true;
			else
			{
				trailCurrent=current;
				current = current->next;
			}
        
		if (current==lst->first)	//insert node before first
		{
			lst->first->back=newNode;
			newNode->next = lst->first;
			lst->first=newNode;
			lst->count++;
		}
		else
		{
            
			//insert newNode between trailCurrent and current
			if (current!=NULL)
			{
				
				
				trailCurrent->next = newNode;
				newNode->back = trailCurrent;
				newNode->next= current;
				current->back = newNode;
			}
			else
			{
				trailCurrent->next = newNode;
				newNode->back = trailCurrent;
				lst->last= newNode;
			}
            
			lst->count++;
		}
        
	}
}


void initializeList(listType *l)
{
    
	nodeType *temp;
	while (l->first!=NULL)
	{
		temp=l->first;
		l->first = l->first->next;
		delete temp;
	}
    
	l->last= NULL;
	l->count=0;
    
    
}

void copyArrayIntoDLL(entryType *darray, listType *lst, int asize)
{
	int i;
    entryType *p;						// create a pointer
    p = darray;						// initialize it to the start of the data
    for(i=0;i<asize;i++,p++)			// increment counter i and pointer p
    {
		insertItem(lst,*p);
    }
    
    
}

entryType *findOldest(entryType *d, int size, int start,int &locmin) {
	int i;
	entryType *p,*oldest;
	p = d+start;
	oldest =d+start;
	locmin = start;
	for(i=start;i<size;i++,p++) {
		if (p->dob < (d+locmin)->dob)
        {
            locmin = i;
            oldest = p;
		}
	}
	return oldest;
}

void printOneRecord(ostream &out, entryType *p)
{
	out << p->ssn<<" " << p->fname<<" "<< p->lname <<" "<< p->dob<<" "<< p->state<<" " << p->phoneNum1<<"-" <<p->phoneNum2 << "-" <<p-> phoneNum3 <<endl;
}


entryType findOldest(entryType *d, int size,int &locmin, int start, int end) {
	int i;
	entryType *p,oldest;
	p = d+start;
	locmin = start;
	for(i=start;i<size;i++,p++) {
		if (p->dob < (d+locmin)->dob)
        {
            locmin = i;
            oldest = d[i];
		}
	}
	
	return oldest;
}

/* Overload printOneRecord */

void printOneRecord(ostream &out, entryType p)
{
	out << p.ssn<<" " << p.fname <<" "<< p.lname << " "<< p.dob<<" "<< p.state<<" " << p.phoneNum1<<"-" << p.phoneNum2<<"-" <<p.phoneNum3 <<endl;
}


void swap(entryType *d, int rsize, int r1,int r2)
{
	entryType temp;
	if ((rsize)>0 && r1>=0 && r2 >=0)
	{
		temp	= d[r1];
		d[r1]	= d[r2];
		d[r2]	= temp;
	}
}


void swap(entryType *a, entryType *b)
{
	entryType temp = *a;
	*a = *b;
	*b = temp;
}


entryType *makeMoreSpace(entryType *d, int &size, double factor) {
    
	int newsize = size*factor;
	entryType *d2 = new entryType[newsize];
	for(int i=0;i<size;i++) {
		*(d2+i) = *(d+i);  //copy into new array
	}
	delete[] d;
	size = newsize;
	return d2;
}



void readOneEntryIntoArray(ifstream &f, entryType *v, char mode)
{
    char dash;
    if (mode =='F')
        f >> v->ssn >> v->fname >> v->lname>>v->dob>>v->state >> v->phoneNum1>>dash >> v->phoneNum2 >> dash>> v->phoneNum3;
    else if (mode == 'P'){
        f >> v->ssn >> v->fname >> v->lname>>v->dob>>v->state;
        
    }
    
	
}


entryType *dynReadDataIntoArray(ifstream &fin, entryType *d, int &size, int &rsize,char mode)
{
    
	int i=0;
	entryType *p;			// create a pointer
	p = d;				// initialize to start of the data
	while (!fin.eof()) {
		if (i>=size) {
			d = makeMoreSpace(d,size,2.0);
			p = d+i;
		}
        
		// read one entry
		readOneEntryIntoArray(fin, p,mode);
      
		
        
		p++;		
		i++;
        
	}
    
	fin.close(); // close the file
	rsize = i-1; // important!!!!
    
	return d; // returns a pointer array.
}


void sortByPromoting(entryType *d, int rsize)
{
	entryType *smallest, *p;
	
	smallest = d;
	
	int locmin=0;
	for ( int i = 0; i < rsize; i++,p++ ) {
		locmin=0;
		p= findOldest(d,rsize,i,locmin);
		if (locmin>0)
			swap(p,d+i);
	}
}

bool makeData(string fname, entryType *dataArray, int &datasize, int &rsize)
{
	
    ifstream fin;
	ofstream fout;
    
	fin.open("people1.txt");
    
    if(!fin){
        cout<<"ERROR"<<endl;
        return false;
    }
    
    
	double start=getCPUTime();
	dataArray= dynReadDataIntoArray(fin, dataArray, datasize, rsize, 'P');
	double end=getCPUTime();
	cout<<">>>Done with reading Grade Data into Dynamic Array......."<<endl;
	cout<< ">>>Read: " << rsize << " into " << datasize << endl;
	cout<< ">>>Time to read data into pointer based array "<<end-start<<" Seconds"<< endl;
    
    fin.close();
    cout<<endl<<"Processing Done Successfully...."<<endl;
    
	fout.open(fname.c_str(), ios::out);
	if( !fout ) {
		cout<<">>>Could Not Open Output File"<<endl;
		return false;
	}
    
    for (int i = 0; i< rsize; i++) {
        dataArray[i].phoneNum1 = my_random_in_range(201, 999);
        dataArray[i].phoneNum2 = my_random_in_range(001, 999);
        dataArray[i].phoneNum3 = my_random_in_range(0000, 9999);
        cout<<setfill('0')<<setw(3);
        
        fout<<dataArray[i].ssn<<" "<<dataArray[i].fname<<" "<<dataArray[i].lname<<" "<<dataArray[i].dob<<" "<<dataArray[i].state<<" "<<dataArray[i].phoneNum1<<"-"<<dataArray[i].phoneNum2<<"-"<<setfill('0')<<setw(4)<<dataArray[i].phoneNum3<<endl;
    }
    
    fout.close();
	
	return true;
}

bool fillArrayFromInputFile(string fname,entryType *d, int &dsz, int &rsz, char mode ){
	
	double start(0), end(0);
	
    ifstream fin;
	
    
	fin.open(fname.c_str(), ios::in);
	if (!fin)
	{
		cout<<">>>Could Not Open Input File.Read failed........."<<endl;
		return false;
        
	}
	
    
	cout<<">>>////////////////////Reading Data into Dynamic Array......."<<endl;
	
	
	
	rsz=0;
	start=getCPUTime();
    
	d= dynReadDataIntoArray(fin, d, dsz, rsz,mode);
	
	end=getCPUTime();
	cout<<">>>Done with reading Data into Dynamic Array......."<<endl;
	cout<< ">>>Read: " << rsz << " into " << dsz << endl;
	cout<< ">>>Time to read data into pointer based array "<<end-start<<" Seconds"<< endl;
    
	return true;
}

void printArray(entryType *d, int rsz,int n){
    
	entryType *p = d;
	if (n<=rsz){
		for (int i=0; i<n;i++,p++){
			printOneRecord(cout,p);
		}
	}
    
}

void matchName ( entryType persons[], int size)
{
    
    string name;
    
    cout << "Enter a name exactly correct: ";
    
    cin >> name;
    
    cout << endl;
    
    for ( int i = 0; i < size; i++)
    {
        if ( persons[i].fname == name || persons[i].lname == name)
        {
            cout << persons[i].ssn << " " << persons[i].fname << " " << persons[i].lname
            << " " << persons[i].dob;
            
            cout << endl;
        }
        
    }
}

void matchPhone ( entryType persons[], int size)
{
    
    int num1;
    int num2;
    int num3;
    
    cout << "Enter a phone number (separated by spaces): ";
    
    cin >>num1>>num2>>num3;
    
    cout << endl;
    
    for ( int i = 0; i < size; i++)
    {
        if ( (persons[i].phoneNum1 == num1) && (persons[i].phoneNum2 == num2) && (persons[i].phoneNum3 == num3))
        {
            cout << persons[i].ssn << " " << persons[i].fname << " " << persons[i].lname
            << " " << persons[i].dob;
            
            cout << endl;
        }
        
    }
}


void bubble_sort(entryType *dataArray, int size)
{
	int i;
	for(i=1;i<size;i++)
	{
		int j;
		for(j=size-1;j>=i;j--)
		{
			if((dataArray[j].lname > dataArray[j-1].lname) || ((dataArray[j].lname==dataArray[j-1].lname)&& (dataArray[j].fname > dataArray[j-1].fname)))
			{
				swap(dataArray,size,j,j-1);
			}
		}
		
	}
    
}

/* Efficient BubbleSort */
void bubbleSort(entryType *arr, int n) {
    bool swapped = true;
    int j = 0;
    entryType temp;
    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < n - j; i++) {
            if ((arr[i].lname > arr[i + 1].lname) || ((arr[i].lname == arr[i + 1].lname) && (arr[i].fname > arr[i + 1].fname)))
            {
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

void sel_sort(entryType *dataArray, int size)
{
	// sort
	int i;
	for(i=0;i<size;i++) {
        
		// find smallest
		// guess that the first is smallest
		//int min = dataArray[i];
		int locmin = i;
        
		// search rest to find
		int j;
		for(j=i+1;j<size;j++) {
			if ((dataArray[locmin].lname > dataArray[j].lname) || ((dataArray[locmin].lname == dataArray[j].lname) && (dataArray[locmin].fname > dataArray[j].fname)))
                
            {
				locmin = j;
				//min = dataArray[j];
			}
		}
        
		if (i!=locmin)
			swap(dataArray, size, i, locmin);
        
		
	}
    
}

void insertion_sort(entryType *d, int size)
{
    
	int i;
	for(i=1;i<size;i++)
	{
		int j;
		for(j=i;j>0;j--)
		{
			if ((d[j].lname < d[j-1].lname) || ((d[j].lname==d[j-1].lname) && (d[j].fname < d[j-1].fname)))
			{
				swap(d,size,j,j-1);
			}
		}
		
	}
    
}

void improved_insertion_sort_p(entryType *d, int size) {
    
	// first find the minimum element (in this case based on studentID)
	int i;
	entryType *p, *q;
	p = d+1;
	int locmin = 0;
	for(i=1;i<size;i++,p++) {
		if (p->lname < (d+locmin)->lname || ((p->lname == (d+locmin)->lname) && (p->fname < (d+locmin)->fname)))
        {
			
			locmin = i;
		}
	}
	swap(d,(d+locmin)); // place minimum in the first location, this is our sentinel
    
	// starting at element 2
	for(i=2;i<size;i++) {
        
		// find where element at p = d+i must go
		// the element pointed to by q at the end
		// is the one just to the left of where p
		// must go
		p = d+i;
		q = p-1;
		while((p->lname < q->lname) || ((p->lname == q->lname) && (p->fname < q->fname)))
        {
			q--;
		}
        
		entryType temp = *p;
		while(p>q) {
			*p = *(p-1);
			p--;
		}
		*(q+1) = temp;
	}
}

void improved_insertion_sort(entryType *d, int size)
{
	int i;
	entryType v;
	for (i=size-1; i>0;i--)
		swap(d,size,i-1,i);
	for (i=1;i<=size-1;i++)
	{
		int j=i;
		v=d[i];
		while ((v.lname < d[j-1].lname) || ((v.lname == d[j-1].lname) && (v.fname < d[j-1].fname)))
		{
			d[j]= d[j-1];
			j--;
		}
		d[j]=v;
	}
    
}

void two_sided_bubble_sort(entryType *d, int size)
{
    
    
	// Here, we will use the two sided bubble sort to sort the array dataArray[0:dsize-1].
    for (int x = 1; x <= size/2; x++)
    {
        
        // first bubbling pass - left to right
        for (int i = x-1; i < size-x; i++)
            if (d[i].phoneNum1 > d[i+1].phoneNum1)
                swap(d,size,i,i+1);
        
        // second bubbling pass - right to left
        for (int i = size-x-1; i >= x; i--)
            if ((d[i].lname < d[i-1].lname) || ((d[i].lname == d[i-1].lname) && (d[i].fname < d[i-1].fname)))
                swap(d,size,i,i-1);
	}
    
    
}



int main()
{
    
	int datasize=250; int rsize=0;
	double start(0), end(0);
    
	string dataFileName ="people30.txt";
	string outputFileName ="peopleNew.txt";
	string outputTestFileName="peopleTested1.txt";
	string sortedOutputFileName ="sorted1.txt";
    
	
	ifstream fin;
	ofstream foutsorted, fouttest;
	
	foutsorted.open(sortedOutputFileName.c_str(), ios::out);
	fouttest.open(outputTestFileName.c_str(), ios::out);
	
    
	entryType *dataArray = new entryType[datasize];
  
    
    
	if (!makeData( outputFileName, dataArray,datasize, rsize)){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
    /* END OF MAKING DATA */
    
    dataFileName = outputFileName;
    
    dataArray = NULL;
    delete[] dataArray;
    
    dataArray = new entryType[datasize];
    
    if (!fillArrayFromInputFile(dataFileName, dataArray,datasize, rsize, 'F'))
    {
        cout<<"Error..." ; return 1;
    }
    
    matchName(dataArray, rsize);
    
    matchPhone(dataArray, rsize);
    
    entryType *oldest;
	
	int pos =0;
	oldest = findOldest(dataArray,rsize,0,pos);
	cout<<">>>Oldest Person - Method 1"<<endl;
	cout<<">>>***********************************"<<endl;
	printOneRecord(cout,oldest);
    
    
	cout<<">>>Oldest Person - Method 2"<<endl;
	cout<<">>>***********************************"<<endl;
	int oldestPos;
	entryType oldestRec;
	oldestRec=findOldest(dataArray,rsize,oldestPos,0,rsize);
	printOneRecord(cout,oldestRec);
    
	cout<<">>>Oldest Person- Method 3"<<endl;
	cout<<">>>***********************************"<<endl;
	printOneRecord(cout,dataArray[oldestPos]);
    
	/* Of course I could have done all of this in one function using passing by ref - think about it and try it
	 * I am going to leave you figure out how we could have found the record witht the smallest ID, and the smallest term/Academic year and
	 * (the smallest alphabetical class or the highest grade). Think about this. You will need it for your assignment.
	 * I used one sorting criteria here.
     */
    
	/* Now let us promote the smallestID to the top until by swapping the smallest ID with the record at location 0 of the array */
    
	
	cout<<">>>Printing first swapped records before swap.."<<endl;
	printOneRecord(cout, dataArray);
	printOneRecord(cout, oldest);
    
    
	swap(dataArray, rsize,0,oldestPos);
	
	//Now letus swap them back and use a different swap function
    
	swap(dataArray, rsize,0,oldestPos); /*This puts them back as they were originally */
    
	swap (dataArray, oldest);  /* dataArray points to position 0 in the array, and smallestIDp pointer points to the smallest ID */
    
    
	
	cout<<">>>Printing first swapped records after swap.."<<endl;
	printOneRecord(cout, dataArray);
	printOneRecord(cout, oldest);
    
	/* Now do it one more time for the second smallest */
	pos =0;
	oldest = findOldest(dataArray,rsize,1,pos);
	cout<<">>>Second Oldest person"<<endl;
	cout<<">>>*******************************"<<endl;
	printOneRecord(cout,oldest);
    
	/* Now let us sort it by keeping on promoting as we did in assignment 5 but we will use the pointers */
	cout<<endl<<"********* First Selection Sort using pointers and findOldest ********"<<endl;
	end=getCPUTime();
	cout<<"Now sorting using selection sort - by promoting the oldest person to the top..Please wait.."<<endl;
	start=getCPUTime();
	sortByPromoting(dataArray,rsize);
	end=getCPUTime();
	cout<<">>>Done with Selection/Promotion Sort......."<<endl;
	cout<< ">>>Time of Selection Promotion Sort..."<<end-start<<" Seconds"<< endl;
	printDataArray(foutsorted, dataArray, rsize);
    
    
	/****************************************************************************/
	
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
    
	cout<<endl<<"*****************  Sorting "<< rsize<<" UNSORTED records   *********************"<<endl<<endl;
	//Print array before sorting
	cout<<"***** First "<< PR<<" records in the array before sorting  ***********"<<endl;
	printArray(dataArray,rsize,PR);
	
	
	cout<<endl<<"**************** Bubble Sort ***************"<<endl;
	/*Try this with the 50,000 records and you will wait for a long time - try with much less*/
	start = getCPUTime();
	//sort
	bubbleSort(dataArray,rsize);
	end = getCPUTime();
	cout << "Bubble Sort		"<<"			Time is: " << end-start << " seconds\n";
	printArray(dataArray,rsize,PR);
	/* Delete and reconstruct Array Again */
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
    
    
	/* reset array to original order */
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
    
    /* We already saw selection sort but I will include the full algorithm for you */
    
	cout<<"*************** Selection Sort***********************"<<endl;
	
	
	
	start = getCPUTime();
	sel_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "Selection Sort		"<<"			Time is: "  <<end-start << " seconds\n";
	printArray(dataArray,rsize,PR);
	
	/* Delete and reconstruct Array Again */
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
    
    
	/* reset array to original order */
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
	cout<<endl<<"***********************Insertion Sort*********************"<<endl;
    
    
	start = getCPUTime();
	insertion_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "Insertion Sort		"<<"			Time is: " << end-start << " seconds\n";
	printArray(dataArray,rsize,PR);
    
	/* Delete and reconstruct Array Again */
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
    
    
	/* reset array to original order */
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
	cout<<endl<<"************ Improved Insertion Sort ******************"<<endl;
    
	
	start = getCPUTime();
	improved_insertion_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "Improved Insertion Sort (IIS)		"<<"	Time is: " << end-start << " seconds\n";
	printArray(dataArray,rsize,PR);
	
    
	/* Delete and reconstruct Array Again */
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
    
    
	/* reset array to original order */
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
    
	cout<<endl<<"****************** TWO SIDED BUBBLE SORT(TBS)  ********************"<<endl;
    
	
	cout<<"Starting TBS"<<endl;
	start = getCPUTime();
	two_sided_bubble_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "TWO SIDED BUBBLE SORT(TBS)		"<<"	Time is: " << end-start << " seconds\n";
	printArray(dataArray,rsize,PR);
    
    
	//**************************************************************************************************
	cout<<endl<<endl;
	cout<<"*************  Sorting "<< rsize<<" ALREADY SORTED records   ********************************"<<endl<<endl;
	//**************************************************************************************************
	///*********** Bubble Sort
	
	start = getCPUTime();
	//sort
	bubble_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "Bubble Sort		"<<"			Time is: " << end-start << " seconds\n";
    
    
	//*************** Selection Sort
	
	start = getCPUTime();
	sel_sort(dataArray,rsize);
	end = getCPUTime();
	cout << "Selection Sort		"<<"			Time is: "  <<end-start << " seconds\n";
	
    
    
    
	//***********************Insertion Sort
    
    
	start = getCPUTime();
	insertion_sort(dataArray,rsize);
	end = getCPUTime();
	cout << "Insertion Sort		"<<"			Time is: " << end-start << " seconds\n";
	
    
	//***********************  Improved Insertion Sort
    
	
	
	start = getCPUTime();
	improved_insertion_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "Improved Insertion Sort (IIS)		"<<"	Time is: " << end-start << " seconds\n";
    
    
	
	//***********************  TWO SIDED BUBBLE SORT(TBS)
    
	
	start = getCPUTime();
	two_sided_bubble_sort(dataArray, rsize);
	end = getCPUTime();
	cout << "TWO SIDED BUBBLE SORT(TBS)		"<<"	Time is: " << end-start << " seconds\n";
	
	/* Now we will delete the array and reconstruct it
	 * in preparation to work on the Doubly Linked List Portion of
	 * the assignment -
	 */
    
	/* Delete and reconstruct Array Again */
	delete [] dataArray;
	dataArray = NULL;
	dataArray = new entryType[datasize];
    
    
	/* reset array to original order */
	if (!fillArrayFromInputFile(dataFileName, dataArray, datasize, rsize, 'F')){
		cout<<"Error making Data..exiting program..."<<endl;
		return -1;
	}
    
    // linked list starts
    
	listType studentList;
	studentList.first= NULL;
	studentList.last=NULL;
	studentList.count=0;
	
    initializeList(&studentList);  /*initialize list by deleting all nodes - We know it is empty here, but this is a good practice*/
	
    cout<<endl<<"Copying Array into Student Doubly Linked List...Please wait"<<endl;
	start=getCPUTime();
	
    copyArrayIntoDLL(dataArray, &studentList, rsize); // copy sorted array, no changes
	
    end=getCPUTime();
	cout<<"Time to Copy Array into Student Doubly Linked List:  "<< end-start <<" seconds."<<endl<<endl;
	cout<<"Saving List to file (studentlist.txt)  "<<endl<<endl;
	ofstream listoutfile;
	listoutfile.open("studentlist.txt");
	
    printDLList(listoutfile, &studentList);
	
    listoutfile.close();
    
    ofstream fout;
    
    fout.open("deletion.txt");
    
    searchDelete(&studentList);
    
    printDLList(fout, &studentList);
    
    fout.close();
    
	cout<<"Done!!"<<"Thank god!!!"<<endl;
    
    // Extra credits.
    
    searchDLLname(&studentList);
    
    searchDLLphoneNum(&studentList);
    
	return 0;
}


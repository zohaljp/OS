
#include <climits>
#include<cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdbool.h>
using namespace std;



struct PageTable {

	int framePA;
	char r_w;
};



int search(vector<PageTable>& v, int idx, int value) {
	int i;
	for (i = idx; i < v.size(); i++) {
		if (v[i].framePA == value) {
			return i;
		}
	}
	return v.size();
}


void FIFO(vector <PageTable>& v, int framenumber, char * dq) {
	char* verify = dq;
	int misses = 0;
	int hits = 0;
	int diskread = 0;
	int diskwrite = 0;
	int fram_indx = framenumber;
	int idx;
	vector <PageTable> pageTable;


	for (int i = 0; i < v.size(); i++)
	{
		idx = search(pageTable, 0, v[i].framePA);

		if ((idx == pageTable.size()) && (pageTable.size()==framenumber))
		{
			if ((pageTable.begin()->r_w == 'W') || (pageTable.begin()->r_w == 'w'))
			{
				pageTable.erase(pageTable.begin());
				pageTable.push_back(v[i]);
				diskwrite++;
				diskread++;
				misses++;


			}


			else {
				pageTable.erase(pageTable.begin());
				pageTable.push_back(v[i]);
				diskread++;
				misses++;



			}



		}

			else if (framenumber> pageTable.size() && (idx == pageTable.size()))
			{
			pageTable.push_back(v[i]);
			diskread++;
			misses++;

			}

	
		else 
		{

			hits++;
			if (v[i].r_w == 'W')
				pageTable[idx].r_w = 'W';
		}


		if (strcmp(verify, "d") == 0 || (strcmp(verify, "D") == 0))
		{
			std::cout << "events in trace :" << v[i].framePA << v[i].r_w << endl;

			std::cout << "total memory frames : " << pageTable.size() << endl;

		}
	}




	std::cout << "events in trace :" << v.size() << endl;
	
	std::cout << "total memory frames : " << pageTable.size() << endl;

	std::cout << "total hit: " << hits << endl;
	std::cout << "total misses: " << misses << endl;
	std::cout << "total disk read: " << diskread << endl;
	std::cout << "total disk write: " << diskwrite << endl;
	std::cout << "idx " << framenumber << endl;
	
	pageTable.clear();
}



void LRU(vector <PageTable>& v, int framenumber,char * dq) {

	char *verify = dq; 
	int misses = 0;
	int hits = 0;
	int diskread = 0;
	int diskwrite = 0;
	int fram_indx = framenumber;
	int idx;
	vector <PageTable> pageTable;


	for (int i = 0; i < v.size(); i++)
	{
		idx = search(pageTable, 0, v[i].framePA);

		if ((idx == pageTable.size()) && (pageTable.size() == framenumber))

		{

			if ((pageTable.begin()->r_w == 'W') || (pageTable.begin()->r_w == 'w'))
			{
				pageTable.erase(pageTable.begin());
				pageTable.push_back(v[i]);
				diskwrite++;
				diskread++;
				misses++;


			}


			else {
				pageTable.erase(pageTable.begin());
				pageTable.push_back(v[i]);
				diskread++;
				misses++;



			}


		}


		else if (framenumber > pageTable.size() && (idx == pageTable.size()))
		{
			pageTable.push_back(v[i]);
			diskread++;
			misses++;

		}





		else
		{
			

			
			PageTable temp = pageTable[idx];
			
			pageTable.erase(pageTable.begin() + idx);
			
			
			

			if (v[i].r_w == 'W')
				temp.r_w = 'W';
				
			pageTable.push_back(temp);

			hits++;
			
			
			
			
			
		}

		
		if (strcmp(verify, "d") == 0 || (strcmp(verify, "D") == 0))
		{
			std::cout << "events in trace :" << v[i].framePA  <<v[i].r_w<< endl;

			std::cout << "total memory frames : " << pageTable.size() << endl;

		}






	}


	std::cout << "events in trace :" << v.size() << endl;

	std::cout << "total memory frames : " << pageTable.size() << endl;

	std::cout << "total hit: " << hits << endl;
	std::cout << "total misses: " << misses << endl;
	std::cout << "total disk read: " << diskread << endl;
	std::cout << "total disk write: " << diskwrite << endl;
	std::cout << "idx " << framenumber << endl;

	pageTable.clear();



}


void VMS(vector<PageTable>& v, int framenumber,int p, char* dq) {

	int misses = 0;
	int hits = 0;
	int diskread = 0;
	int diskwrite = 0;
	char* verify = dq;



	int percentage=p;
	

	int framenumberLRU = (framenumber * percentage) / 100;//secondary
	int frame_idx = framenumber - framenumberLRU; //primary

	vector<PageTable> pageTable;
	vector<PageTable> LRU;




	for (int i = 0; i < v.size(); i++)
	{
		int idx = search(pageTable, 0, v[i].framePA);
		int idx1 = search(LRU, 0, v[i].framePA);

		if ((idx == pageTable.size()) && (pageTable.size() == frame_idx) && (LRU.size() < framenumberLRU))// not in fifo, fifo is  full, lru is not full 3
		{


			if (idx1 != LRU.size())
			{
				PageTable temp1 = pageTable[0];
				PageTable temp = LRU[idx1];
				LRU.erase(LRU.begin() + idx1);
				pageTable.erase(pageTable.begin());
				if (v[i].r_w == 'W') {
					temp.r_w = 'W';
				}
					pageTable.push_back(temp);
					LRU.push_back(temp1);
					


					
				
				hits++;
				

			}

				else if  (idx1 == LRU.size())
				{

					PageTable temp1 = pageTable[0];
					pageTable.erase(pageTable.begin());
					LRU.push_back(temp1);

					pageTable.push_back(v[i]);
					misses++;
					diskread++;
				}




			
		}





			if ((idx == pageTable.size()) && (pageTable.size() < frame_idx)) // not in fifo, fifo is not full- 2

			{


			
					pageTable.push_back(v[i]);
					diskread++;
					misses++;
				

			}

			if ((pageTable.size() == frame_idx) && (idx == pageTable.size()) && (idx1 != LRU.size())) //fifo full, page is in lru 4
			{

				

					PageTable temp1 = pageTable[0];
					PageTable temp = LRU[idx1];
					pageTable.erase(pageTable.begin());
					LRU.erase(LRU.begin() + idx1);

					if (v[i].r_w == 'W') {
						temp.r_w = 'W';
					}
						pageTable.push_back(temp);
						LRU.push_back(temp1);
						
						hits++;


				

				

				


			}

			if (((idx == pageTable.size()) && (pageTable.size() == frame_idx) && (LRU.size() == framenumberLRU) && (idx1 == LRU.size())))// not in fifo or lru, both full 5
			{

				if ((LRU.begin()->r_w == 'W') || (LRU.begin()->r_w == 'w'))
				{	

					PageTable temp1 = pageTable[0];
					PageTable temp = LRU[0];

					pageTable.erase(pageTable.begin());
					pageTable.push_back(v[i]);
					LRU.erase(LRU.begin());
					LRU.push_back(temp1);
					diskwrite++;
					diskread++;
					misses++;


				}


				else {
					PageTable temp1 = pageTable[0];
					PageTable temp = LRU[0];

					pageTable.erase(pageTable.begin());
					pageTable.push_back(v[i]);
					LRU.erase(LRU.begin());
					LRU.push_back(temp1);
					diskread++;
					misses++;



				}

			}


			else if (idx != pageTable.size() )
			{
				hits++;
				
				if (v[i].r_w == 'W') {
					pageTable[idx].r_w = 'W';
					
				}
			

				
				


			}


			
			if (strcmp(verify, "d") == 0 || (strcmp(verify, "D") == 0))
			{
				std::cout << "events in trace :" << v[i].framePA << v[i].r_w << endl;

				std::cout << "total memory frames : " << pageTable.size() << endl;

			}






		}

	

	

	
			std::cout << "events in trace :" << v.size() << endl;

			std::cout << "total memory frames in FIFO: " << pageTable.size() << endl;
			std::cout << "total memory frames in LRU: " << LRU.size() << endl;

			std::cout << "total hit: " << hits << endl;
			std::cout << "total misses: " << misses << endl;
			std::cout << "total disk read: " << diskread << endl;
			std::cout << "total disk write: " << diskwrite << endl;


			pageTable.clear();
			LRU.clear();

}









int main (int argc, char* argv[]) {

	int framenumber;
	FILE* traceFile = fopen(argv[1], "r");

	if (traceFile == NULL)
		printf("File cannot be opened");

	framenumber = atoi(argv[2]);

	
	vector <PageTable> bigarray(1000000);



	unsigned int addr;
	char rw;
	int i;

	for (i = 0; fscanf(traceFile, "%x %c", &addr, &rw) != EOF; i++)
	{

		bigarray[i].framePA = addr >> 12;
		bigarray[i].r_w = rw;
	}



	fclose(traceFile);


	//FIFO(bigarray, framenumber);
	//LRU(bigarray, framenumber);
	//VMS(bigarray, framenumber);

	if ( strcmp(argv[3], "LRU") == 0 || strcmp(argv[3], "lru") == 0) {
		char* dq = argv[4];
		LRU(bigarray, framenumber,dq);
	}
	else if (strcmp(argv[3], "FIFO") == 0 || strcmp(argv[3], "fifo") == 0) {
		char *dq = argv[4];
		FIFO(bigarray, framenumber,dq);
	}
	else if (strcmp(argv[3], "VMS") == 0 || strcmp(argv[3], "vms") == 0) {
		int p = atoi(argv[4]);
		char* dq = argv[5];
		if ( p==0|| p==100 || p==1)
			FIFO(bigarray, framenumber, dq);
		else 
			VMS(bigarray, framenumber,p ,dq);
	}
	else printf( "No algorithm was chosen,  make sure to respect the format of inputs Please recompile and redo");


	return 0;



}

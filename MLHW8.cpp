// MLHW8.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<math.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char theline [100] ;

	double data[100][10];
	double test[1000][10];
	double gk_nbor[100][5];
	int k[5] = {1,3,5,7,9};

	// initial
	for(int i=0; i<100; i++){
		for(int j=0; j<5; j++){
			gk_nbor[i][j] = 0;
		}
	}

	//read file
	fstream fin;
	fin.open("train.txt",ios::in);

	//分割字串存入二維陣列
	char *token = NULL;
	char *next_token = NULL;
	char seps[]   = " ,\t\n";
	int a=0;
	while(fin.getline(theline,sizeof(theline),'\n')){
		int b = 0;
		token = strtok_s( theline, seps, &next_token);
		while (token != NULL){
			data[a][b] = atof(token);
            token = strtok_s( NULL, seps, &next_token);
			b++;
		}
		a++;
	}

	// start k-nearest neighbor
	for(int m=0; m<5; m++){
		int already[100][9];		// save the index that is already used
		// initial
		for(int i=0; i<100; i++){
			for(int j=0; j<9; j++){
				already[i][j] = -1;
			}
		}
		int count_k = 0;
		while(count_k!=k[m]){
			double nearest[100][2];
			for(int i=0; i<100; i++){
				nearest[i][0] = -1;			// 0 save the index of nearest neighbor
				nearest[i][1] = 10000;		// 1 save the distance 
			}
			for(int i=0; i<100; i++){
				for(int j=0; j<100; j++){
					double distance = 0;
					for(int d=0; d<9; d++){
						distance = distance + (data[i][d]-data[j][d])*(data[i][d]-data[j][d]);	// calculate the distance
					}
					for(int t=0; t<9; t++){
						if(j==already[i][t]){
							distance = 10000;
						}
					}
					// choice the nearest
					if(distance<=nearest[i][1]){
						nearest[i][0] = j;
						nearest[i][1] = distance;
						already[i][count_k] = j;
					}
				}
			}
			count_k++;
		}
		
		// calculate gk_nbor[100][5];
		for(int i=0; i<100; i++){
			for(int j=0; j<k[m]; j++){				// how many nearest neighbor
				int index = already[i][j];
				gk_nbor[i][m] = gk_nbor[i][m] + data[index][9];
			}
		}
	}

	for(int i=0; i<100; i++){
		for(int j=0; j<5; j++){
			if(gk_nbor[i][j]>0){
				gk_nbor[i][j] = 1;
			}else{
				gk_nbor[i][j] = -1;
			}
		}
	}
	double ein[5] = {0,0,0,0,0};
	for(int i=0; i<5; i++){
		for(int j=0; j<100; j++){
			if(data[j][9]!=gk_nbor[j][i]){
				ein[i]++;
			}
		}
		ein[i] = ein[i]/100;
	}
	for(int i=0; i<5; i++){
		cout<<ein[i]<<endl;
	}

	system("pause");
	return 0;
}
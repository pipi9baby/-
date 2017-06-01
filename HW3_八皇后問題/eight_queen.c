#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h> 
#include<limits.h>

int size = 8;
int *curr_arr;
int *next_arr;

//計算衝突數
int colision(int arr[]){
	int i=0,j=0,num=0,offset=0;
	for(i=0;i<size;i++){
		for(j = i+1;j<size;j++){
			if(arr[i] == arr[j]){
				num++;
			}
			offset = j-i;
			if(abs(arr[i]-arr[j])==offset){
				num++;
			}
		}
	}
	return num;
}
//找所有下一步移動中衝突最少的
void queen(int arr[]){
	int i=0,j=0,col=0,row=0,cols_num = 0,min=0;
	int tmp[size];
	int chess[3][size*size-size];
	for(i=0;i<3;i++){
		for(j=0;j<size*size-size;j++){
			chess[i][j] = INT_MAX;
		}
	}
	
	min = colision(arr);

	for(col=0;col<size;col++){
		for(row=0;row<size;row++){
			if(arr[col] == row){
				continue;
			}
			for(i=0;i<size;i++){
				tmp[i] = arr[i];
			}
			tmp[col] = row;
			cols_num = colision(tmp);
			if(cols_num < min){
				min = cols_num;
				for(i=0;i<size;i++){
					next_arr[i] = arr[i];
				}
				next_arr[col] = row;
			}
		}
	}
}
//主程式
int main() {

	int loop=0;
	char input[5];
	//輸入參數
	printf("請輸入棋盤大小(純數字)：");
	gets(input);
	size = atoi(input);
	curr_arr = (int*)malloc(sizeof(int)*size);
	next_arr = (int*)malloc(sizeof(int)*size);
	printf("請輸入重複迴圈次數(純數字)：");
	gets(input);
	loop = atoi(input);
	//亂數設定
	unsigned seed;
    seed = (unsigned)time(NULL); // 取得時間序列
    srand(seed); // 以時間序列當亂數種子	
	
	int i=0,success=0;
	for(i=0;i<loop;i++){
		//亂數皇后的初始位置
		int j=0;
		for(j=0;j<size;j++){
			curr_arr[j] = rand()%size;
			next_arr[j] = 0;
		}
		//開始爬山演算法
		while(1){
			int count=0;
			queen(curr_arr);
			
			for(j=0;j<size;j++){
				if(curr_arr[j] == next_arr[j]){
					count++;
				}
			}
			if(count == size){
				break;
			}
			for(j=0;j<size;j++){
				curr_arr[j] = next_arr[j];
			}
		}
		if(colision(curr_arr) == 0){
			success++;
			printf("第%d次\n",success);
			for(j=0;j<size;j++){
				printf("%d\t",curr_arr[j]);
			}
			printf("\n+");
			for(j=0;j<size;j++){
				printf("---+");
			}
			printf("\n");
			int k=0;
			for(k=0;k<size;k++){
				printf("|");
				for(j=0;j<size;j++){
					if(j == curr_arr[k]){
						printf(" Q |");
					}else{
						printf("   |");
					}
				}
				printf("\n+");
				for(j=0;j<size;j++){
					printf("---+");
				}
				printf("\n");
			}
			//寫檔
			FILE *wFile;
			wFile = fopen( "output.txt","a" );
			if( NULL == wFile ){
				printf( "open failure" );
				return 1;
			}else{
				int k=0;
				for(k=0;k<size;k++){
					for(j=0;j<size;j++){
						if(curr_arr[k] == j){
							fprintf(wFile,"1");
						}else{
							fprintf(wFile,"0");
						}
					}
					fprintf(wFile,"\n");
					//fwrite(enter,1,sizeof(enter),wFile);
				}
				for(k=0;k<size;k++){
					fprintf(wFile,"=");
				}
				fprintf(wFile,"\n");
				//fwrite(enter,1,sizeof(enter),wFile);
			}
			fclose(wFile);
		}
	}
	system("PAUSE");
	return 0;
}

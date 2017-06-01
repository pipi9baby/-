#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h> 
#include<limits.h>

int size = 8,value=0;
int *curr_arr;
int *next_arr;
int *father;
int *mother;
//次方
int pow(int a,int b){ 
	int n=1,x=0; 
	for(x=0;x<b;x++){ 
		n=n*a;
	}
	return n; 
} 
//計算適應值
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
	return(value-num);
}
//交換
void swap(int A,int B){
	int c=A;
	A=B;
	B=c;
}
//雜交
void merge(){
	int cut = rand()%size;
	int i=0;
	printf("\n");
	for(i=0;i<cut;i++){
		swap(father[i],mother[i]);
	}
}
//突變
int mutation(int arr[]){
	int ran1 = rand()%size;
	int ran2 = rand()%size;
	
	return arr[ran1] = ran2;
}
//選擇父親母親
void choseFM(int arr[],int N){
	int i=0,j=0,col=0,row=0,total_col=0,Fran=0,Mran=0,count=0,min=0;
	int cols_num[N][3];
	int tmp[size];
	for(i=0;i<N;i++){
		for(j=0;j<3;j++){
			cols_num[i][j] = 0;
		}	
	}
	
	for(col=0;col<size;col++){
		for(row=0;row<size;row++){
			if(arr[col] == row){
				continue;
			}
			for(i=0;i<size;i++){
				tmp[i] = arr[i];
			}
			tmp[col] = row;
			min = size*size;
			for(i=0;i<N;i++){
				if(cols_num[i][2]<min){
					min = cols_num[i][2];
				}
			}
			if(min!=size*size){
				for(i=0;i<N;i++){
					if(cols_num[i][2]==min){
						cols_num[i][0] = col;
						cols_num[i][1] = row;
						cols_num[i][2] = colision(tmp);
						break;
					}
				}	
			}
		}
	}
	int stF;
	Fran = rand()%total_col;
	//printf("亂數 %d,total_col %d\n",Fran,total_col);
	for(i=0;i<N;i++){
		//printf("%d\t%d\n",Fran,cols_num[i][2]);
		if(Fran < cols_num[i][2]){
			for(j=0;j<size;j++){
				father[j] = arr[j];
			}
			father[cols_num[i][0]] = cols_num[i][1];
			//printf("%d %d\n",cols_num[i][0],cols_num[i][1]);
			stF=i;
			break;
		}
		
		Fran = Fran - cols_num[i][2];
	}
	do{
		Mran = rand()%total_col;
		//printf("亂數 %d,total_col %d\n",Mran,total_col);
		for(i=0;i<N;i++){
			//printf("%d\t%d\n",Mran,cols_num[i][2]);
			if(Mran < cols_num[i][2]){
				for(j=0;j<size;j++){
					mother[j] = arr[j];
				}
				mother[cols_num[i][0]] = cols_num[i][1];
				//printf("%d %d\n",cols_num[i][0],cols_num[i][1]);
				break;
			}
			Mran = Mran - cols_num[i][2];
		}
	}while(i==stF);
	//*/
}
//主程式
int main() {

	int prob=0,N=0;
	char input[5];
	
	//輸入參數
	printf("請輸入棋盤大小(純數字)：");
	gets(input);
	size = atoi(input);
	curr_arr = (int*)malloc(sizeof(int)*size);
	next_arr = (int*)malloc(sizeof(int)*size);
	father = (int*)malloc(sizeof(int)*size);
	mother = (int*)malloc(sizeof(int)*size);
	printf("請輸入突變的機率為多少分之一：");
	gets(input);
	prob = atoi(input);
	
	printf("請輸入一代群體的個數：");
	gets(input);
	N = atoi(input);
	
	//計算最高適應值
	int i=0,j=0,success=0,st_col=0;
	for(i=0;i<size;i++){
		value += i;
	}

	//亂數設定
	unsigned seed;
    seed = (unsigned)time(NULL); // 取得時間序列
    srand(seed); // 以時間序列當亂數種子	
	
	printf("\n");
	//亂數皇后的初始位置
	for(j=0;j<size;j++){
		curr_arr[j] = rand()%size;
		next_arr[j] = 0;
		printf("%d ",curr_arr[j]);
	}
	printf("\n");
	
	
	//開始基因演算法
	while(1){
		int col=0,count=0;
		choseFM(curr_arr,N);
		
		merge();
		int colF = colision(father);
		int colM = colision(mother);

		if(colF>colM){
			for(j=0;j<size;j++){
				next_arr[j] = father[j];
			}
			col = colF;
		}else{
			for(j=0;j<size;j++){
				next_arr[j] = mother[j];
			}
			col = colM;
		}
		
		//printf("分數：%d\n",colision(next_arr));
		if(colision(next_arr) == value){
			break;
		}
		for(j=0;j<size;j++){
			curr_arr[j] = next_arr[j];
			//printf("%d\t",curr_arr[j]);
		}
		//printf("\n");
		//system("PAUSE");
	}
	
	//print棋盤
	if(colision(next_arr) == value){
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
	//*/
	system("PAUSE");
	return 0;
}

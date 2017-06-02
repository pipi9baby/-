#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h> 
#include<limits.h>

int size = 8,value=0;
int *next_arr;
int *father;
int *mother;
 
//�p��A����
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
//�洫
void swap(int A,int B){
	int c=A;
	A=B;
	B=c;
}
//����
void merge(){
	int cut = rand()%size;
	int i=0;
	for(i=0;i<cut;i++){
		swap(father[i],mother[i]);
	}
}

//��ܤ��˥���
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
	for(i=0;i<N;i++){
		total_col += cols_num[i][2];
	}
	//printf("%d\n",total_col);
	int stF;
	Fran = rand()%total_col;
	//printf("�ü� %d,total_col %d\n",Fran,total_col);
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
		//printf("�ü� %d,total_col %d\n",Mran,total_col);
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
//�D�{��
int main() {

	int prob=0,N=0,loop=0;
	char input[5];
	
	//��J�Ѽ�
	printf("�п�J�ѽL�j�p(�¼Ʀr)�G");
	gets(input);
	size = atoi(input);
	next_arr = (int*)malloc(sizeof(int)*size);
	father = (int*)malloc(sizeof(int)*size);
	mother = (int*)malloc(sizeof(int)*size);
	
	printf("�п�J�U�@�N�s�骺�ӼơG");
	gets(input);
	N = atoi(input);
	
	printf("�п�J���ܪ����v���h�֤����@�G");
	gets(input);
	prob = atoi(input);
	
	printf("�п�J�n�D�X�ӸѡG");
	gets(input);
	loop = atoi(input);
	
	//�p��̰��A����
	int i=0,j=0,success=0,st_col=0;
	for(i=0;i<size;i++){
		value += i;
	}

	//�üƳ]�w
	unsigned seed;
    seed = (unsigned)time(NULL); // ���o�ɶ��ǦC
    srand(seed); // �H�ɶ��ǦC��üƺؤl	
	
	while(loop!=0){
		//�üƬӦZ����l��m
		printf("\n�üư_�l�ȡG\n");
		for(j=0;j<size;j++){
			next_arr[j] = rand()%size;
			printf("%d\t",next_arr[j]);
		}
		printf("\n");
	//�}�l��]�t��k
		while(1){
			//���
			int col=0,count=0;
			choseFM(next_arr,N);
			
			//��t
			merge();
			int colF = colision(father);
			int colM = colision(mother);
			
			//�P�_�ͤU���Ĥl���Ӧn�N�έ���
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
			//�ݾ��v����
			if(rand()%prob==1){
				next_arr[rand()%size] = rand()%size;
				printf("���ܤF�I�I\n");
			}
			
			//printf("���ơG%d\n",colision(next_arr));
			if(colision(next_arr) == value){
				break;
			}
			//system("PAUSE");
		}
		
		//print�ѽL
		success++;
		printf("��%d��\n",success);
		for(j=0;j<size;j++){
			printf("%d\t",next_arr[j]);
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
				if(j == next_arr[k]){
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
		//�g��
		FILE *wFile;
		wFile = fopen( "output.txt","a" );
		if( NULL == wFile ){
			printf( "open failure" );
			return 1;
		}else{
			int k=0;
			for(k=0;k<size;k++){
				for(j=0;j<size;j++){
					if(next_arr[k] == j){
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
		loop--;
	}
	//*/
	system("PAUSE");
	return 0;
}

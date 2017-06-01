#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h> 

int leaves=0,br=0,lv=0,now_lv=0,size=0,find=0,k=0,sd_lv=0,count =-1;
//���l�ƶq�B����ƶq�B���h�ƶq�B�{�b�Ҧb���h�B�`�I�ƶq�B�n�j�M���Ʀr�B�ΨӼ�input���@���}�C��itree�ɶ��ĴX�ӤF
int *array;
typedef struct tree {
	int visit;
	int num;
	struct tree **branch;
} tree;

//����Ƶ{��
int pow(int a,int b){
	int x=0;
	int n=1;
	for(x=0;x<b;x++){
		n=n*a;
	}
	return n;
}

//���̤j��
int max(int a,int b){
	if(a > b){
		return a;
	}else{
		return b;
	}
}
//���̤p��
int min(int a,int b){
	if(a < b){
		return a;
	}else{
		return b;
	}
}

//DFS�ؾ�Ƶ{��
tree* build(tree *prev){
	int i=0,j=0;
	for(i=0;i<br;i++){	
		if(now_lv <= lv){
			struct tree *current = NULL;
			current = (struct tree *)malloc(sizeof(struct tree));
			current->branch = (struct tree**)malloc(br*sizeof(struct tree *));
			current->visit = 0;
			
			if(now_lv == lv){
				current->num = array[k];
				k++;
				for(j=0;j<br;j++){
					current->branch[j] = NULL;
				}
			}else{
				if(now_lv%2 == 0){
					current->num = INT_MIN;
				}else if(now_lv%2 == 1){
					current->num = INT_MAX;
				}
				
			}
			//printf("%d:%d,����:%d\t",now_lv,current->num,i);
			prev->branch[i] = current;
			now_lv++;
			build(current);
			now_lv = now_lv-1;
			//node_num++;
			//printf("\n��%d��leaf�ا�\n",node_num);
		}
	}
}

int DFS(tree *current, int alpha,int beta,int cu_lv,bool minimax){
	current->visit = 2;
	int i=0,j=0;
	count++;
	if(cu_lv == lv){
		return current->num;
	}
	if(minimax){
	//���̤j
		for(i=0;i<br;i++){
			//count++;
			alpha = max(alpha,DFS(current->branch[i],alpha,beta,cu_lv+1,false));
			current->num = alpha;
			if(beta <= alpha){
				//printf("current node:��%d�h��%d\nalpha�G%d beta�G%d\n",cu_lv,current->num,alpha,beta);
				//printf("count�G%d\n",count);
				//printf("break!!\n");
				break;
			}
		}
		return alpha;
	}else{
	//���̤p
		for(i=0;i<br;i++){
			//count++;
			beta = min(beta,DFS(current->branch[i],alpha,beta,cu_lv+1,true));
			current->num = beta;
			if(beta <= alpha){
				//printf("current node:��%d�h��%d\nalpha�G%d beta�G%d\n",cu_lv,current->num,alpha,beta);
				//printf("count�G%d\n",count);
				//printf("break!!\n");
				break;
			}
		}
		return beta;
	}
	
}

//DFS�j�M
tree* DFS_search(tree *current){
	if(current->visit == 2){
		if(current->num != INT_MAX || current->num != INT_MAX){
			printf("%d\t",current->num);
		}else{
			printf("NULL\t");
		}
	}
	int i=0,j=0;
	current->visit = 1;
	for(i=0;i<br;i++){
		if(current->branch[i] != NULL){
			if(current->branch[i]->visit != 1){
				DFS_search(current->branch[i]);			
			}
		}
	}
}

int main() {
    FILE *fr;
    int file_open_en = 0;
    char file_name[30];
	char ch,str[5];

	//�}��
	while(file_open_en == 0){
		printf("�п�J�ɮצW��(�t���ɦW)�G");
		gets(file_name);

		fr = fopen(file_name,"r");
		file_open_en = 1;
		if(fr == NULL){
			printf("�}�ɥ���!!\n�Э��s��J�C");
			file_open_en = 0;
		}
	}
	//Ū��
	int col = 0, k = 0, i=0,j=0;

    while(((ch = fgetc(fr)) != EOF)){
		if(ch == '\n'){
			col++;
			if(col == 1){
				br = atoi(str);//����ƶq
				printf("����ƶq%d\n",br);
			}else if(col == 2){
				lv = atoi(str);//���h��
				printf("���h�ƶq%d\n",lv);
				size = (1-pow(br,lv+1))/(1-br);//��ʾ𪺸`�I�ƶq
				leaves = pow(br,lv);//���l���ƶq
				printf("���l�ƶq%d\n",leaves);
				array = (int*)malloc(sizeof(int)*leaves);//�ʺA�t�m�@�Ӥ@���}�C�sleaves����
			}else if(col == 3){
				array[i] = atoi(str);
			}else if(col == 4){
				find = atoi(str);
			}else{
				printf("��J�ɮ׮榡���~�I�I\n��J�ɮ����u��4��A���ˬd�O�_���T�C");
			}
			k=0;
		}else if(ch == ','){
			array[i] = atoi(str);
			memset(str, '\0', 5);
			i++;
			k=0;
		}else if(isdigit(ch)){
			str[k] = ch;
			k++;
		}else if(ch == '-'){
			str[k] = ch;
			k++;
		}

	}
    fclose(fr);
	struct tree *root    = NULL;
	struct tree *current = NULL;
    struct tree *prev    = NULL;
    
	//�ʺA���tROOT���Ŷ�
	current = (struct tree *)malloc(sizeof(struct tree));
	current->branch = (struct tree**)malloc(br*sizeof(struct tree *));
	current->num = INT_MIN;
	current->visit = 0;
	
	for(i=0;i<br;i++){
		current->branch[i] = NULL;
	}
	prev = current;
	root = current;
	
	printf("�n�s�W���`�I��%d\n",size);
	int num=0;
	//�}�l�ؾ�
	now_lv++;
	build(current);
	
	//DFS�j�M���
	DFS(root,INT_MIN,INT_MAX,0,true);
	

	//DFS_search
	printf("=======================================================================\n");
	printf("DFS��X�����X�L���C��node���ȡG\n");
	DFS_search(root);
	
	printf("\nROOT�̲׵��G�G%d",root->num);
	printf("\n���X����ƶq�G%d\n",count);
	system("PAUSE");
	return 0;
}
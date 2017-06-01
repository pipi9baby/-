#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

int leaves=0,br=0,lv=0,now_lv=0,size=0,find=0,k=0;
//���l�ƶq�B����ƶq�B���h�ƶq�B�{�b�Ҧb���h�B�`�I�ƶq�B�n�j�M���Ʀr�B�ΨӼ�input���@���}�C��itree�ɶ��ĴX�ӤF
int *array;
typedef struct tree {
	int visit;
	int num;
	struct tree **branch;
} tree;

//DFS�ؾ�Ƶ{��
tree* build(tree *prev){
	int i=0,j=0;
	//printf("%d",prev->num);//��ܩҸ`�I�Ʀr
	//printf("%d\t", now_lv);//��ܩҦb���h
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
				current->num = 0;
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

tree* DFS(tree *current){
	int i=0,j=0;
	for(i=0;i<br;i++){
		if(current->branch[i] != NULL){
			if(now_lv <= lv){
				if(now_lv%2 == 0){
					if(i == 0){
						current->num = current->branch[i]->num;
					}else if(current->num > current->branch[i]->num){
						current->num = current->branch[i]->num;
					}
				}else if(now_lv%2 == 1){
					if(i == 0){
						current->num = current->branch[i]->num;
					}else if(current->num < current->branch[i]->num){
						current->num = current->branch[i]->num;
					}
				}
				now_lv++;
				DFS(current->branch[i]);
				now_lv--;
			}
		}
	}
}

//DFS�j�M
tree* DFS_search(tree *current){
	printf("%d\t",current->num);
	int i=0,j=0;
	current->visit = 1;
	for(i=0;i<br;i++){
		if(current->branch[i] != NULL){
			if(current->branch[i]->visit == 0){
				//printf("test:%d\t",current->branch[i]->num);
				DFS_search(current->branch[i]);			
			}
		}
	}
}

//����Ƶ{��
int pow(int a,int b){
	int x=0;
	int n=1;
	for(x=0;x<b;x++){
		n=n*a;
	}
	return n;
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
	current->num = 0;
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
	int q=0;
	for(q=0;q<lv;q++){
		now_lv=1;
		DFS(root);
	}

	//DFS_search
	printf("=======================================================================\n");
	printf("DFS��X�C��node���ȡG\n");
	DFS_search(root);
	
	printf("\nROOT�̲׵��G�G%d\n",root->num);
	
	system("PAUSE");
	return 0;
}

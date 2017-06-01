#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

int leaves=0,br=0,lv=0,now_lv=0,size=0,find=0,k=0;
//葉子數量、分支數量、階層數量、現在所在階層、節點數量、要搜尋的數字、用來數input的一維陣列塞進tree時塞到第幾個了
int *array;
typedef struct tree {
	int visit;
	int num;
	struct tree **branch;
} tree;

//DFS建樹副程式
tree* build(tree *prev){
	int i=0,j=0;
	//printf("%d",prev->num);//顯示所節點數字
	//printf("%d\t", now_lv);//顯示所在階層
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
			//printf("%d:%d,分支:%d\t",now_lv,current->num,i);
			prev->branch[i] = current;
			now_lv++;
			build(current);
			now_lv = now_lv-1;
			//node_num++;
			//printf("\n第%d顆leaf建完\n",node_num);
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

//DFS搜尋
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

//次方副程式
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

	//開檔
	while(file_open_en == 0){
		printf("請輸入檔案名稱(含副檔名)：");
		gets(file_name);

		fr = fopen(file_name,"r");
		file_open_en = 1;
		if(fr == NULL){
			printf("開檔失敗!!\n請重新輸入。");
			file_open_en = 0;
		}
	}
	//讀檔
	int col = 0, k = 0, i=0,j=0;

    while(((ch = fgetc(fr)) != EOF)){
		if(ch == '\n'){
			col++;
			if(col == 1){
				br = atoi(str);//分支數量
				printf("分支數量%d\n",br);
			}else if(col == 2){
				lv = atoi(str);//階層數
				printf("階層數量%d\n",lv);
				size = (1-pow(br,lv+1))/(1-br);//整棵樹的節點數量
				leaves = pow(br,lv);//葉子的數量
				printf("葉子數量%d\n",leaves);
				array = (int*)malloc(sizeof(int)*leaves);//動態配置一個一維陣列存leaves的值
			}else if(col == 3){
				array[i] = atoi(str);
			}else if(col == 4){
				find = atoi(str);
			}else{
				printf("輸入檔案格式錯誤！！\n輸入檔案應只有4行，請檢查是否正確。");
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
    
	//動態分配ROOT的空間
	current = (struct tree *)malloc(sizeof(struct tree));
	current->branch = (struct tree**)malloc(br*sizeof(struct tree *));
	current->num = 0;
	current->visit = 0;
	
	for(i=0;i<br;i++){
		current->branch[i] = NULL;
	}
	prev = current;
	root = current;
	
	printf("要新增的節點數%d\n",size);
	int num=0;
	//開始建樹
	now_lv++;
	build(current);
	
	//DFS搜尋填值
	int q=0;
	for(q=0;q<lv;q++){
		now_lv=1;
		DFS(root);
	}

	//DFS_search
	printf("=======================================================================\n");
	printf("DFS輸出每個node的值：\n");
	DFS_search(root);
	
	printf("\nROOT最終結果：%d\n",root->num);
	
	system("PAUSE");
	return 0;
}

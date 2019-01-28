#include "structs.h"


int main(int argc, char *argv[]){
	
	int i=0;
	int j=0;
	int counter=0;
	int flag = 0;
	int k,frames,q,max;
	
	if(argc!=5){
	 printf("You should give 4 arguments.\n 1)Number of page faults\n 2)Number of frames\n 3)Number of references\n 4)Max number of references\n");
	 return -1;
	}
	
	k = atoi(argv[1]);
	frames=atoi(argv[2]);
	q=atoi(argv[3]);
	max=atoi(argv[4]);
	
	char line1[15];
	node *n = NULL;
	
	list l;
	listInitialize(&l);
	
	
	//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	FILE* gcc = fopen("gcc.trace","r+");
	FILE* bzip = fopen("bzip.trace","r+");
	
	while(1){
		for(i=0;i<q;i++){
			
			fgets(line1,15,gcc);
			n=nodeCreate(line1,1);
			listInsert(&l,n);
			counter++;	
			if(counter==max){
				flag = 1;
				break;
			}
		}
		if(flag==1)break;
		for(i=0;i<q;i++){
			
			fgets(line1,15,bzip);
			n=nodeCreate(line1,2);
			listInsert(&l,n);
			counter++;
			if(counter==max){
				flag = 1;
				break;
			}	
		}
		if(flag==1)break;
	
	}
	
	//////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	//inverted page table size = memory size = memory frames = frames
	char* ** invertedPT;
	allocate_matrix(&invertedPT,frames,3,10);
	for(i=0;i<frames;i++){
		for(j=0;j<3;j++){
			strcpy(invertedPT[i][j],"e\0");
		}
	}
	
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	int found =0;
	int hits=0;
	int pfaults=0;
	int sumpfaults=0;
	int readsfromdisk=0;
	int writestodisk=0;
	
	while(l.start!=NULL){
		found =0;
		n = returnNode(&l);

		//check if the reference is in the page table
		//hit case
		for(i=0;i<frames;i++){
			if(strcmp(n->reference , invertedPT[i][0])==0 && n->pid == atoi(invertedPT[i][1])){
				hits ++;
				found = 1;
				break;
			}
		}
		if(found){
			nodeDestroy(&l);
			continue;
			
		}
		///////////////////////////////////////////////////////
		//fault case
		
		int spot = checktable(invertedPT, frames);
		//fullpt
		if(spot == -2){
			pfaults++;
			sumpfaults++;
			if(n->RorW == 'R'){
				readsfromdisk++;
			}
			else{
				writestodisk++;
			}
			
			if(k+1==pfaults){
				invertedPT = fwf(invertedPT,frames);
				pfaults=0;
			}
			
		}
		//has a spot
		else if(spot!=-2){
			sumpfaults++;
			if(n->RorW == 'R'){
				readsfromdisk++;
			}
			else{
				writestodisk++;
			}
			char id[2];
			id[0]= n->pid + '0';
			id[1] = '\0'; 
			
			strcpy(invertedPT[spot][0],n->reference);
			strcpy(invertedPT[spot][1],id);
			invertedPT[spot][2][0] = n->RorW;
			invertedPT[spot][2][1] = '\0';
		}
		
		
		nodeDestroy(&l);
	}
	
	printf("\n");
	printf("Number of PFs             : %d\n",sumpfaults);
	printf("Number of Page hits       : %d\n",hits);
	printf("Number of reads from disk : %d\n",readsfromdisk);
	printf("Number of writes to disk  : %d\n",writestodisk);
	printf("Number of frames          : %d\n",frames);
	
	
	
	//////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////
	
	for(i=0;i<frames;i++){
		for(j=0;j<3;j++){
			free(invertedPT[i][j]);
		}
	}
	for(i=0;i<frames;i++){
		free(invertedPT[i]);
	}
	free(invertedPT);
	
	//listPrint(&l);

	listDestroy(&l);
	
	fclose(gcc);
	fclose(bzip);
	



	return 0;
}

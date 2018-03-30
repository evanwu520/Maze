#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define column 4
#define row 4

typedef struct {
    int x; 
    int y;
} Point;

//�O���Ҧ��i�H����I�����| 
typedef struct {
	int index;
    Point record [];
} Allrecord;

Point setPoint(int, int);
void createMaze(char maze[row][column], Point start, Point end);
void visit(char[row][column], Point, Point, void (*)(char[row][column]));
void save(char[row][column]);//�p��C�����|���B��
Point move(int dir);
void pintArray(char maze[row][column]);
Allrecord array[100];//save all result
int index = -1;//result index
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//�r���C��
bool isFindInResut(int x, int y, int minIndex);//�O�_�����|���O��
void copyArray(char[row][column], char[row][column]);/*copy array*/

 
int main(void) { 

    //�ɶ��ü� 
	srand(time(NULL));
    Point entrancePoint = setPoint((rand() % row), (rand() % column));	//�üƱ��I 
    Point exitPoint = setPoint((rand() % row), (rand() % column));		//�üƲ��I 
    
    
    char printMaze[row][column];//�e�{�Ϊ� 
    char maze[row][column];
    createMaze(maze, entrancePoint, exitPoint);//�إ߰g�c     
    copyArray(maze, printMaze);//copy

	pintArray(maze);//print maze                   
    visit(maze, entrancePoint, exitPoint, save);
    printf("�`�@��%d���X��\n",index+1);
    
//    for(int i=0; i<=index; i++){
//    	printf("��%d�ӵ��G, �� %d �B\n",i+1, array[i].index ) ;
//	}
	//�����X�f 
    if(index != -1){
    	//��̵u���|��index 
		int min = -1;
		int minIndex = 0;
		bool first = true;
		
		for(int i=0; i<=index; i++){
			if(first){
				min = array[i].index;
				first =false;
			}
			if(array[i].index < min){
				min = array[i].index;
				minIndex = i;
			}
		}
		//�L�X�̵u���|��  
//		for(int i=0; i<row; i++){
//			for(int j=0; j<column; j++){
//				SetConsoleTextAttribute(hConsole, 240);//white
//				//�_�I����I 
//				if((i == entrancePoint.x && j == entrancePoint.y) || (i == exitPoint.x && j == exitPoint.y)){
//					SetConsoleTextAttribute(hConsole, 252); //red
//					printMaze[i][j] = '2';
//				}else if(isFindInResut(i, j, minIndex)){
//					SetConsoleTextAttribute(hConsole, 252); //red
//				}
//				 printf("%c ", printMaze[i][j]);
//			}
//			printf("\n");
//		}
		
		SetConsoleTextAttribute(hConsole, 7);
		printf("��%d�ճ̤֨�%d�B\n", minIndex+1, min);
		printf("\n");
	}
	system("pause");
	
    return 0; 
}
/*�O�_�����|���O��*/ 
bool isFindInResut(int x, int y, int minIndex){
	bool find = false;	
	
	
	for(int i=0; i<=array[minIndex].index; i++){
		if(x == array[minIndex].record[i].x && y == array[minIndex].record[i].y){
			find = true;
			break;
		}
//		printf("%d	%d\n", array[minIndex].record[i].x, array[minIndex].record[i].y);

	}
	return find;
}
/*copy array*/
void copyArray(char source [][column] , char distance [][column]){
	for(int i = 0; i < row; i++) { 
    	for(int j = 0; j < column; j++){
    		distance[i][j] = source[i][j];
		}
    }
}
Point setPoint(int x, int y) {
    Point p = {x, y};
    return p;
}
/*�M������X�f*/ 
void visit(char maze [row][column], Point start,  Point end, void (*save)(char[row][column])){
          
   	//�P�_���S���W�X�}�C 
    if((start.x <row && start.x >= 0) &&  (start.y <column && start.y >=0)){
     	
     	//�P�_�O�_�i�H�� 
     	if(maze[start.x][start.y] != '1' &&  maze[start.x][start.y] != '3'){
     		
     		//���L���� 
     		maze[start.x][start.y] = '3';
        	//���X�f 
	        if(start.x == end.x &&  start.y == end.y) {
	        	++index;     //���\�Ӽ� 
	            save(maze);	//�x�s���\���G 
	        } else {
	         	//�@���I�n���K�Ӥ�V 
	         	int dirCount=1;
	    		while(dirCount<=8){
	    		 	visit(maze, setPoint(start.x + move(dirCount).x, start.y + move(dirCount).y), end, save);
	    			dirCount+=1; 	
	    		}
	         }
	         //�٭� 
	         maze[start.x][start.y] = '0';
		}
    }
}

/*�إ߰g��*/ 
void createMaze(char maze[row][column], Point start, Point end){
	
	for(int i=0; i<row; i++){
		
		for(int j=0; j<column; j++){
			 //����1-100�ü� 
			int  value =(rand() % 100)+1;
			// ���� ���ͥi������ 
			if(value % 2 == 0  ){
				maze[i][j]='0';
			}else{
				maze[i][j]='1';
			}
		}
	}
	//�_�I���I 
	maze[start.x][start.y]='2';
	maze[end.x][end.y]='2';
}
/*�p��C�����|���B��*/ 
void save(char maze[row][column]) {
	printf("��%d��\n",index+1); 
    int count=-1;
    for(int i = 0; i < row; i++) { 
        for(int j = 0; j < column; j++){
        	//save��U�����|  x, y �ȷ|���A ���ϧη|�� 
        	if(maze[i][j] =='2' || maze[i][j] =='3'){
				array[index].record[++count].x = i;
        		array[index].record[count].y = j;
        		array[index].index = count;
				printf("��");         
			}else{
				printf("�i"); 
			}
		}
		printf("\n");
    } 
    printf("\n");
}

/*��X���G*/ 
void pintArray(char maze[row][column]){
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			
			SetConsoleTextAttribute(hConsole, 240);//white
			
			 if(maze[i][j] == '2' && maze[i][j] == '2') {
				SetConsoleTextAttribute(hConsole, 252); //red
			}
		    printf("%c ", maze[i][j]);
		}
			printf("\n"); 
	}
	printf("\n"); 
	SetConsoleTextAttribute(hConsole, 7);
}

/*���ʽd��*/ 
Point move(int dir){
	
  Point p;
  
  switch(dir){
  	
  	case 1:
      p=setPoint(-1,-1);
      break;
   case 2:
      p=setPoint(-1,0);
      break;
   case 3:
      p=setPoint(-1,1);
      break;
   case 4:
      p=setPoint(0,1);
      break;
   case 5:
      p=setPoint(1,1);
      break;
   case 6:
      p=setPoint(1,0);
      break;
   case 7:
      p=setPoint(1,-1);
      break;
   case 8:
      p=setPoint(0,-1);
  }	
  return p;
}

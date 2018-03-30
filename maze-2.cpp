#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define column 15
#define row 15
#define MAXSTACK column*row /*�w�q�̤j���|�e�q*/


typedef struct {
    int x; 
    int y;
    int dir;
} Point;

Point stack[column*row];  //���|���}�C�ŧi 
int top=-1;	                 //���|������

void push(Point); 
Point pop();
Point setPoint(int, int);
void createMaze(char maze[row][column], Point start, Point end);
void pintArray(char maze[row][column],int reuslt, Point specifyPoint);
void initMarkArray(char mark[row][column]);
Point move(int dir);
bool isFind(int x, int y);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//�r���C��
bool findExit(char maze[row][column], char mark[row][column], Point start, Point end, Point specify);//��X�f 

int main(void) { 

	//�ɶ��ü� 
	srand(time(NULL));
	
    Point entrancePoint = setPoint((rand() % row), (rand() % column));	//�üƱ��I 
    Point exitPoint = setPoint((rand() % row), (rand() % column));		//�üƲ��I 
    
    char maze[row][column];
    char mark[row][column];
    
    initMarkArray(mark);//��l 
	createMaze(maze, entrancePoint, exitPoint);//�إ߰g�c 
	//���T�w�S���X�f 
	bool exit = findExit(maze, mark, entrancePoint, exitPoint, entrancePoint);
  
	//�P�_���S�����X�f 
	if(exit){
		printf("%s  \n", "���X�f!!");
		
		//pintArray(maze, 1, setPoint(100,100));//print  result 1
	    
	    //���J�üƲ��� specify point �B���ର�쥻���\���u
	    Point specify;
	    
		while(true){
			specify = setPoint((rand() % row), (rand() % column));;
			if(!isFind(specify.x, specify.y)){
				break;
			}
		}
		pintArray(maze, 1, specify);//print result 1
		
		//�T�w�_�I�i�H���줤���I
		top =-1;//��l 
		initMarkArray(mark);//��l 
		
		//���줤���I 
		if(findExit(maze, mark, entrancePoint, specify, specify)){
			 initMarkArray(mark);//��l 
			//�����I�줤�� 
			if(findExit(maze, mark, specify, exitPoint,exitPoint)){
				pintArray(maze, 2, specify);
			}
		}
	}else{
		printf("%s  \n", "�䤣��X�f!!");
	}
    
    system("pause");
    
    return 0; 
}
//trace maze function 
bool findExit(char maze[row][column], char mark[row][column], Point start, Point end, Point specify){
	
	Point current;
	int dirCount, nextRow, nextColumn, currentRow, currentColumn; 
    
	
	current.x = start.x;
    current.y = start.y;
    current.dir = 1;
    push(current);
	mark[start.x][start.y]='1';
    
    while(top>-1){
    		
    	current = pop();
    	currentRow = current.x;
    	currentColumn = current.y;
    	dirCount = current.dir;
    	//printf("dirCount %d\n", current.dir);
    	
    	//�@���I�n���K�Ӥ�V 
    	while(dirCount<=8){
    		
    		//�U�@��potint 
    		nextRow = currentRow + move(dirCount).x;
    		nextColumn = currentColumn + move(dirCount).y;
    		
    		//�P�_���S���W�X�}�C 
    		if((nextRow <row && nextRow >= 0) &&  (nextColumn <column && nextColumn >=0)){
    			
    			if(maze[nextRow][nextColumn] != '1'  && mark[nextRow][nextColumn] !='1'){//�P�_�O���O�����A�ӥB�S���L 
    		     	//printf("%d  %d  %d\n", nextRow, nextColumn, dirCount);
					//record point
					mark[nextRow][nextColumn]='1'; 
					//push current point 
					current.x = currentRow;
					current.y = currentColumn;
					current.dir = dirCount;
					push(current);
					//next point 
					currentRow = nextRow;
					currentColumn = nextColumn;
					dirCount = 0;
				}
				
				//���X�f 
    			if(nextRow == end.x && nextColumn == end.y){
    				
    				current.x = nextRow;
				    current.y = nextColumn;
//				    printf(">>%d	%d\n", current.x, current.y);
					push(current);
    				return true;
				}
			}
			dirCount++;
		}
	} 
	
	return false;
}
/*�O�_����쵲�G��*/ 
bool isFind(int x, int y){

    bool find = false;	
    
	for(int i=0; i<=top; i++){
		if(x == stack[i].x && y==  stack[i].y){
			find = true;
		}
	}
	
	return find;
}

/*�������L����*/ 
void initMarkArray(char mark[row][column]){
	
	for(int i=0; i<row; i++){
		
		for(int j=0; j<column; j++){
			mark[i][j]='0';
		}
	}
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
/*��X���G*/ 
void pintArray(char maze[row][column], int reuslt, Point specifyPoint){
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			
			SetConsoleTextAttribute(hConsole, 240);//white
			
			if(specifyPoint.x == i && specifyPoint.y == j){//special�y�Ъ��� 
				SetConsoleTextAttribute(hConsole, 249); //blue
				maze[i][j] = '3';
			}else if(maze[i][j] == '2' && maze[i][j] == '2') {
				SetConsoleTextAttribute(hConsole, 252); //red
			}else if(isFind(i,j)){
				if(reuslt == 1){
					SetConsoleTextAttribute(hConsole, 252); //red
				}else{
					
					SetConsoleTextAttribute(hConsole, 242); //green
				}
			} 
		    printf("%c ", maze[i][j]);
		}
			printf("\n"); 
	}
	printf("\n"); 
	SetConsoleTextAttribute(hConsole, 7);
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
/*�]�w row index, column index*/ 
Point setPoint(int x, int y) {
    Point p = {x, y};
    return p;
}


/*�N���w����Ʀs�J���|*/
void push(Point data){
	if(top>=MAXSTACK){
		printf("���|�w��,�L�k�A�[�J\n");	
	}else{
		stack[++top]=data;
	} 
}

/*�q���|���X���*/
Point pop(){
	return stack[top--];
}

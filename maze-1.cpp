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
} Point;

Point stack[column*row];  //���|���}�C�ŧi 
int top=-1;	                 //���|������

void push(Point); 
Point pop();
Point setPoint(int, int);
void createMaze(char maze[row][column], Point start, Point end);
void pintArray(char maze[row][column], int result);
void initMarkArray(char mark[row][column]);
Point move(int dir);
bool isFind(int x, int y);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int main(void) { 

	//�ɶ��ü� 
	srand(time(NULL));
	
    Point entrancePoint = setPoint((rand() % row), (rand() % row));	//�üƱ��I 
    Point exitPoint = setPoint((rand() % row), (rand() % column));		//�üƲ��I 
    Point current;
    
    char maze[row][column];
    char mark[row][column];
    
    int dirCount, nextRow, nextColumn, currentRow, currentColumn; 
    bool exit = false;
    
    initMarkArray(mark);//��l 
	createMaze(maze, entrancePoint, exitPoint);//�إ߰g�c 
	pintArray(maze,1);//��X�g�c print result 1
	
    current.x = entrancePoint.x;
    current.y = entrancePoint.y;
    push(current);
	mark[entrancePoint.x][entrancePoint.y]='1';
    
    while(top>-1 && !exit){
    		
    	current = pop();
    	currentRow = current.x;
    	currentColumn = current.y;
    	dirCount = 1;
    	
    	//�@���I�n���K�Ӥ�V 
    	while(dirCount<=8){
    		
    		//�U�@��potint 
    		nextRow = currentRow + move(dirCount).x;
    		nextColumn = currentColumn + move(dirCount).y;
    		
    		//�P�_���S���W�X�}�C 
    		if((nextRow <row && nextRow >= 0) &&  (nextColumn <column && nextColumn >=0)){
    			
    			//�P�_�O���O�����A�ӥB�S���L 
    			if(maze[nextRow][nextColumn] != '1'  && mark[nextRow][nextColumn] !='1'){
    				
    		     	//printf("%d  %d  %d\n", nextRow, nextColumn, dirCount);
					//record point
					mark[nextRow][nextColumn]='1'; 
					//push current point 
					current.x = currentRow;
					current.y = currentColumn;
					push(current);
					//next point 
					currentRow = nextRow;
					currentColumn = nextColumn;
					dirCount = 0;
				}
    			
    			//���X�f 
    			if(nextRow == exitPoint.x && nextColumn == exitPoint.y){
    				current.x = nextRow;
				    current.y = nextColumn;
					push(current);
    				exit = true;
    				break;
				}
			
			}
			dirCount++;
		}
	} 
	//�P�_���S�����X�f 
	if(exit){
		printf("%s  \n", "���X�f!!");
		pintArray(maze, 2);//print result 2
		pintArray(maze, 3);//print result 3
	}else{
		printf("%s  \n", "�䤣��X�f!!");
	}
		
    
    system("pause");
    
    return 0; 
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
void pintArray(char maze[row][column], int result){
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			
			SetConsoleTextAttribute(hConsole, 240);//white
			
			if(result == 2 ||  result == 3){
				if(isFind(i,j)){
					SetConsoleTextAttribute(hConsole, 252); //red
				}else{
					 //�m�����bstack x y �y�Ъ��� 
					 if(result == 3){
					 	maze[i][j] = '*';
					 }
				}
			}else{
				//�J�f�B�X�f 
			    if(maze[i][j] == '2'){
			    	SetConsoleTextAttribute(hConsole, 252); //red
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

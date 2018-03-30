#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define column 15
#define row 15
#define MAXSTACK column*row /*定義最大堆疊容量*/


typedef struct {
    int x; 
    int y;
    int dir;
} Point;

Point stack[column*row];  //堆疊的陣列宣告 
int top=-1;	                 //堆疊的頂端

void push(Point); 
Point pop();
Point setPoint(int, int);
void createMaze(char maze[row][column], Point start, Point end);
void pintArray(char maze[row][column],int reuslt, Point specifyPoint);
void initMarkArray(char mark[row][column]);
Point move(int dir);
bool isFind(int x, int y);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//字體顏色
bool findExit(char maze[row][column], char mark[row][column], Point start, Point end, Point specify);//找出口 

int main(void) { 

	//時間亂數 
	srand(time(NULL));
	
    Point entrancePoint = setPoint((rand() % row), (rand() % column));	//亂數啟點 
    Point exitPoint = setPoint((rand() % row), (rand() % column));		//亂數終點 
    
    char maze[row][column];
    char mark[row][column];
    
    initMarkArray(mark);//初始 
	createMaze(maze, entrancePoint, exitPoint);//建立迷宮 
	//先確定沒有出口 
	bool exit = findExit(maze, mark, entrancePoint, exitPoint, entrancePoint);
  
	//判斷有沒有找到出口 
	if(exit){
		printf("%s  \n", "找到出口!!");
		
		//pintArray(maze, 1, setPoint(100,100));//print  result 1
	    
	    //插入亂數產生 specify point 且不能為原本成功路線
	    Point specify;
	    
		while(true){
			specify = setPoint((rand() % row), (rand() % column));;
			if(!isFind(specify.x, specify.y)){
				break;
			}
		}
		pintArray(maze, 1, specify);//print result 1
		
		//確定起點可以走到中間點
		top =-1;//初始 
		initMarkArray(mark);//初始 
		
		//走到中間點 
		if(findExit(maze, mark, entrancePoint, specify, specify)){
			 initMarkArray(mark);//初始 
			//中間點到中間 
			if(findExit(maze, mark, specify, exitPoint,exitPoint)){
				pintArray(maze, 2, specify);
			}
		}
	}else{
		printf("%s  \n", "找不到出口!!");
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
    	
    	//一個點要走八個方向 
    	while(dirCount<=8){
    		
    		//下一個potint 
    		nextRow = currentRow + move(dirCount).x;
    		nextColumn = currentColumn + move(dirCount).y;
    		
    		//判斷有沒有超出陣列 
    		if((nextRow <row && nextRow >= 0) &&  (nextColumn <column && nextColumn >=0)){
    			
    			if(maze[nextRow][nextColumn] != '1'  && mark[nextRow][nextColumn] !='1'){//判斷是不是有路，而且沒走過 
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
				
				//找到出口 
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
/*是否有找到結果值*/ 
bool isFind(int x, int y){

    bool find = false;	
    
	for(int i=0; i<=top; i++){
		if(x == stack[i].x && y==  stack[i].y){
			find = true;
		}
	}
	
	return find;
}

/*紀錄走過的路*/ 
void initMarkArray(char mark[row][column]){
	
	for(int i=0; i<row; i++){
		
		for(int j=0; j<column; j++){
			mark[i][j]='0';
		}
	}
}
/*移動範圍*/ 
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
/*輸出結果*/ 
void pintArray(char maze[row][column], int reuslt, Point specifyPoint){
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			
			SetConsoleTextAttribute(hConsole, 240);//white
			
			if(specifyPoint.x == i && specifyPoint.y == j){//special座標的值 
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

/*建立迷客*/ 
void createMaze(char maze[row][column], Point start, Point end){
	
	for(int i=0; i<row; i++){
		
		for(int j=0; j<column; j++){
			 //產生1-100亂數 
			int  value =(rand() % 100)+1;
			// 雙數 產生可走的路 
			if(value % 2 == 0  ){
				maze[i][j]='0';
			}else{
				maze[i][j]='1';
			}
		}
	}
	//起點終點 
	maze[start.x][start.y]='2';
	maze[end.x][end.y]='2';
}
/*設定 row index, column index*/ 
Point setPoint(int x, int y) {
    Point p = {x, y};
    return p;
}


/*將指定的資料存入堆疊*/
void push(Point data){
	if(top>=MAXSTACK){
		printf("堆疊已滿,無法再加入\n");	
	}else{
		stack[++top]=data;
	} 
}

/*從堆疊取出資料*/
Point pop(){
	return stack[top--];
}

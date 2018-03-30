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

//記錄所有可以到終點的路徑 
typedef struct {
	int index;
    Point record [];
} Allrecord;

Point setPoint(int, int);
void createMaze(char maze[row][column], Point start, Point end);
void visit(char[row][column], Point, Point, void (*)(char[row][column]));
void save(char[row][column]);//計算每條路徑的步數
Point move(int dir);
void pintArray(char maze[row][column]);
Allrecord array[100];//save all result
int index = -1;//result index
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//字體顏色
bool isFindInResut(int x, int y, int minIndex);//是否找到路徑的記錄
void copyArray(char[row][column], char[row][column]);/*copy array*/

 
int main(void) { 

    //時間亂數 
	srand(time(NULL));
    Point entrancePoint = setPoint((rand() % row), (rand() % column));	//亂數啟點 
    Point exitPoint = setPoint((rand() % row), (rand() % column));		//亂數終點 
    
    
    char printMaze[row][column];//呈現用的 
    char maze[row][column];
    createMaze(maze, entrancePoint, exitPoint);//建立迷宮     
    copyArray(maze, printMaze);//copy

	pintArray(maze);//print maze                   
    visit(maze, entrancePoint, exitPoint, save);
    printf("總共有%d條出路\n",index+1);
    
//    for(int i=0; i<=index; i++){
//    	printf("第%d個結果, 走 %d 步\n",i+1, array[i].index ) ;
//	}
	//有找到出口 
    if(index != -1){
    	//找最短路徑的index 
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
		//印出最短路徑圖  
//		for(int i=0; i<row; i++){
//			for(int j=0; j<column; j++){
//				SetConsoleTextAttribute(hConsole, 240);//white
//				//起點跟終點 
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
		printf("第%d組最少走%d步\n", minIndex+1, min);
		printf("\n");
	}
	system("pause");
	
    return 0; 
}
/*是否找到路徑的記錄*/ 
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
/*尋找全有出口*/ 
void visit(char maze [row][column], Point start,  Point end, void (*save)(char[row][column])){
          
   	//判斷有沒有超出陣列 
    if((start.x <row && start.x >= 0) &&  (start.y <column && start.y >=0)){
     	
     	//判斷是否可以走 
     	if(maze[start.x][start.y] != '1' &&  maze[start.x][start.y] != '3'){
     		
     		//走過的路 
     		maze[start.x][start.y] = '3';
        	//找到出口 
	        if(start.x == end.x &&  start.y == end.y) {
	        	++index;     //成功個數 
	            save(maze);	//儲存成功結果 
	        } else {
	         	//一個點要走八個方向 
	         	int dirCount=1;
	    		while(dirCount<=8){
	    		 	visit(maze, setPoint(start.x + move(dirCount).x, start.y + move(dirCount).y), end, save);
	    			dirCount+=1; 	
	    		}
	         }
	         //還原 
	         maze[start.x][start.y] = '0';
		}
    }
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
/*計算每條路徑的步數*/ 
void save(char maze[row][column]) {
	printf("第%d組\n",index+1); 
    int count=-1;
    for(int i = 0; i < row; i++) { 
        for(int j = 0; j < column; j++){
        	//save當下的路徑  x, y 值會錯， 但圖形會對 
        	if(maze[i][j] =='2' || maze[i][j] =='3'){
				array[index].record[++count].x = i;
        		array[index].record[count].y = j;
        		array[index].index = count;
				printf("◇");         
			}else{
				printf("█"); 
			}
		}
		printf("\n");
    } 
    printf("\n");
}

/*輸出結果*/ 
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

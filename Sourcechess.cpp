#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define true 1
#define false 0
#define N 8
#define KRED  "\x1B[31m"
#define RESET "\x1B[0m"
#define GRN   "\x1B[32m"
#define CYN   "\x1B[36m"
#define bold      "\33[1m"
#define underline "\33[4m"
#define unformat  "\33[0m"
#define	 rook	 	"\u265C" 
#define	 knite	 	"\u265e" 
#define	 bishop		"\u265D" 
#define	 qween		"\u265A" 
#define	 king		"\u265B" 
#define	 pion		"\u265F"
#define  space 		" "

		      //printf("%c[%d;%df ",0x1B,y,x);
#define	 print(tool)	printf("%c[%d;%d;%dm %s ",'\e',at,txt,bg,tool)
#define  change_bg	(bg==yellow_b)?(bg=cyan_b):(bg=yellow_b)
#define  change_tx	(chessb[i][j]>97)?(txt=white_t):(txt=black_t)					 

typedef enum color_attributes {all_off,bold_on,Underscore=4,blink_on,rev_video_on=7,con_on} color_a;
typedef enum color_txt  {black_t=30,red_t,green_t,yellow_t,blue_t,magenta_t,cyan_t,white_t} color_t;
typedef enum color_bg   {black_b=40,red_b,green_b,yellow_b,blue_b,magenta_b,cyan_b,white_b} color_b;

char* s1 = "can not move over another tool";
char* s2 = "please try again"; 
int win = 0;
int turn = 1; //1 - WHITE     2 - BLACK   
int successflag = 0;
void showchessboard (char chessb[ ][8]);     
void initboard(char * chessb );
void gotoxy(int x,int y);
void exchange(char * , char *);
int checkPlayer(char);
int checkInput(char []);
int isAlpha(char );
int isDigit(char );
void setIndex(char [] ,int*,int*,int*,int* );
int checkPawnMove(char*,char*,int ,int,int,int);
int checkkingmove(char*,char*,int ,int,int,int);
int checkrookmove(char*,char*,int ,int,int,int);
int checkbishopmove(char*,char*,int ,int,int,int);
int checkknitemove(char*,char*,int ,int,int,int);
int checkqueenmove(char*,char*,int ,int,int,int);
int isEmpty(char );
void eat(char*, char*);
void swap(char*,char*);
void printboard(char [][8]);
int checklastmove(char * , char *);
int checkleagalpiece(char *, char *);

int main(){
	
	char chess[8][8] =   {'r','n','b','q','k','b','n','r',
                            'p','p','p','p','p','p','p','p',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            'P','P','P','P','P','P','P','P',
                            'R','N','B','Q','K','B','N','R'};
	initboard((char*)chess);                 
	showchessboard(chess);
	char tool ;
	
	char  moveString[5];
	char * source , * dest;
	int i = 0 , j = 0 , m = 0, n = 0 ;	
	for(win = false ;win = true;)
	{
	do{	
	showchessboard(chess);
//    printboard(chess);
	do{
	printf(CYN"%s player plays \n",(turn == 1?"white":"black"));
	printf("please enter source and destinatio\n"RESET);
	scanf("%4s",moveString);
	puts(moveString);
	setIndex(moveString ,&i , &j , &m ,&n);
	source = &chess[i][j];//printf("%x\n",source);
  	dest = &chess[m][n];//printf("%x\n",dest);
    }while(!checkInput(moveString) && checkleagalpiece(source,dest));
//	setIndex(moveString ,&i , &j , &m ,&n);
//  	source = &chess[i][j];//printf("%x\n",source);
//  	dest = &chess[m][n];//printf("%x\n",dest);
 printf("NOW PLAYS  --> %d\n",turn);	
  	tool = *source;
	printf("the tool is --> %c\n",tool);
    if(tool < 'Z')tool+=32;
  	   switch (tool)
        {
            case 'p':
				successflag  = checkPawnMove(source,dest,i ,j,m,n );
                break;
            case 'r':
                successflag  = checkrookmove(source,dest,i ,j,m,n );
                break;
            case 'k':
                successflag  = checkkingmove(source,dest,i ,j,m,n);
                break;
            case 'b':
                successflag  = checkbishopmove(source,dest,i ,j,m,n);
                break;
            case 'q':
                successflag  = checkqueenmove(source,dest,i ,j,m,n);
                break;
            case 'n':
                successflag  = checkknitemove(source,dest,i ,j,m,n);
                break;
            default:
                printf(KRED"Illegal piece\n please try again"RESET);
                continue;
        }
	}  while(!successflag);
	turn = turn==1?2:1;
	successflag = 0;
	 printf("NOW PLAYS  --> %d\n",turn);	
	
	
	
	 
	}
 return 0; 
} 
/*void printboard(char board[][8])
{int i,j;
for(i=0;i<8;i++)
{
	for(j=0;j<8;j++)
		printf("%c\t",board[i][j]);
	printf("\n");
}  


}*/ 
int isAlpha(char c){return (c>='A'&&c<='H')?1:0;}
int isDigit(char d){return (d>='1'&&d<='8')?1:0;}  
int isEmpty(char c){return (c==' ')?1:0;}
void eat(char* s,char* d){
	char replay;
	     if (*d == 'k'){ win = true;
			  printf(GRN"%s player is the winner!!!!!!!!!!!!\n",turn==1?"white":"black"RESET);
			  printf("do you wish for a nother games ? y/n");
			  scanf("%c",&replay);
			  if(replay == 'y')printf("new game");
			  else
			  printf(" not new game");
			  
			  }
	     ;*d = *s ; *s = ' ';
	    
	    
}
int checkleagalpiece(char* s ,char* d)
{
if (turn == 1  && (*s<'a')){printf(KRED"wrong tool\n"RESET);return 0;}
if (turn == 1  && (*d>'a')){printf(KRED"can not go over white tool\n"RESET);return 0;}	
if (turn == 2  && *s >'I'){printf(KRED"wrong tool\n"RESET);return 0;}
if (turn == 2  && (*d<'I')){printf(KRED"can not go over black tool\n"RESET);return 0;}	
return 1;	
}

int checkqueenmove(char* s,char* d,int i ,int j,int m,int n)
{
int flag = 0;
if (i==m || n==j)
	flag = checkrookmove(s,d ,i,j,m,n);
else 
    flag = checkbishopmove(s,d ,i,j,m,n);

return flag;

}

int checkknitemove(char* s,char* d,int i ,int j,int m,int n)
{

if((abs(i-m)==2&&abs(j-n)==1)||(abs(j-n==2)&&abs(i-m)==1))
{checklastmove(s,d); return 1;}
else{printf(KRED"wrong move , please try again\n"RESET);}

return 0;
}

int checkbishopmove(char* s,char* d,int i ,int j,int m,int n)
{
int a = abs(d-s)/8 , b = abs(d-s), k;
char* temp = s;
//if (b%8==0){printf(KRED"wrong move, please try again\n"RESET); return 0;}
if(b%7==0 || b%9 == 0)
{
if (i>m && j>n && b%9 == 0)
{
for (k=0;k<a-1;k++)
{
	temp -= 9;
 if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0 ;}
}
}
else if (i>m && j<n && b%7 == 0)
{
for (k=0;k<a-1;k++){
	temp -= 7;
if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0 ;} 	 
}
}

else if (i<m && j>n && b%7 == 0)
{
for (k=0;k<a-1;k++){
	temp += 7;
 if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0 ;} 	 
}
}
else if (i<m && j<n && b%9 == 0)
{
for (k=0;k<a-1;k++){
	temp += 9;
 if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0 ;} 	 
}
}

return checklastmove(s,d);	
}
return 0;
}
int  checkrookmove(char* s,char* d,int i ,int j,int m,int n)
{
int k,a = abs(d-s)/8 , b = abs(d-s);
char* temp = s;
if ((j==n)&&(s<d))
{
for (k=0;k<a-1;k++)
{
temp += 8;
 if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0 ;} 	 
}	

}	
else if ((j==n)&&(s>d))
{
for (k=0;k<a-1;k++)
{
temp -= 8;
if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0;} 	
}	
}
else if ((i==m)&&(s<d))
{
for(k=0;k<b-1;k++)
temp -= 1;
if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0;} 	
}	
else if ((i==m)&&(s>d))
{
for(k=0;k<b-1;k++)
temp += 1 ;
if(!isEmpty(*temp)){printf(KRED"can not move over a nother tool\n"RESET);return 0;} 	
}
return checklastmove(s,d);	

	
}
int checklastmove(char* s, char* d)
{
if (turn == 1 && *d ==' '){swap(s,d);return 1;}
else if(turn == 1 && *d<'I'){eat(s,d);return 1;}
else if (turn == 1 && *d >'a'){printf(KRED"can not go over white tool!!\n please try again\n"RESET);}
else if (turn == 2 && *d ==' '){swap(s,d);return 1;}
else if(turn == 2 && *d>'a'){eat(s,d);return 1;}
else if (turn == 2 && *d <'Z'){printf(KRED"can not go over black tool!!\n please try again\n"RESET);}

return 0;


}
int checkkingmove(char* s,char* d,int i ,int j,int m,int n)
{
if((abs(i-m)==1&&j==n) ||(i==m && abs(j-n)==1)||(abs(i-m)==1 && abs(j-n)==1))	
{return checklastmove(s,d);}
else{printf(KRED"incorrect move, please try again"RESET);}
return 0;		 
}

int checkPawnMove(char* s,char* d,int i,int j ,int m ,int n)
{	//white is play
if (turn == 1 )
{
     if(*s<'a'){printf(KRED"wrong tool\n"RESET);}
  else
     if(i>=m){printf(KRED"can not go backword!!\n"RESET);}
  else 
     if( i == 1 && (d-s == 8 || d-s == 16) && *d==' ') {swap(s,d);printf("swap   ");printf("%c -- %c \n",*s,*d);return 1;}   
  else
	  if(d-s == 8 && *d == ' ' ){swap(s,d);return 1;}
  else 
     if (*d > 96 && d-s == 8 )printf(KRED"can not make move over white tool\n"RESET);
  else
	  if(*d < 'Z' && ( d-s == 7 || d-s == 9)){eat(s,d);printf("eating\n");printf("%c -- %c \n",*s,*d);return 1;}	
  else
		 printf(KRED"pion is blocked... can not move\n"RESET);  
  	
}	
else//black is play
   {
	    if(*s > 'z'){printf(KRED"wrong tool\n"RESET);}
	else   
	    if (i<=m)printf(KRED"can not go backword!!\n"RESET);
	else
		if(i==6 && (s-d == 8|| s-d ==16) && *d==' '){swap(s,d);printf("swap      ");printf("%c -- %c \n",*s,*d);return 1;}    
	else
	    if(s-d == 8 && *d == ' ' ){swap(s,d);return 1;}  
	else 
        if (*d < 'Z' && s-d == 8 )printf(KRED"can not make move over black tool\n"RESET); 
	else
        if(*d > 'a' && ( s-d == 7 || s-d == 9)){eat(s,d);printf("eating\n");printf("%c -- %c \n",*s,*d);return 1;}	
	else
		 printf(KRED"pion is blocked... can not move\n"RESET);
   }
return 0;
}
void setIndex(char s[] ,int* i,int* j, int* m, int* n)
{
*i = abs('1'-s[1]); printf("%d",*i);			
*j = s[0]-'A';printf("%d\n",*j);	
*m = abs('1'-s[3]);printf("%d",*m);
*n = s[2]-'A';printf("%d\n",*n);	
	}                      
int checkInput(char s[])
    
{	if(s[0]==s[2]&&s[1]==s[3]){printf(KRED"source and destination equal, please try again\n"RESET);return 0;}
    if(strlen(s)!= 4)return 0;
	if ( isAlpha(s[0]) && isDigit(s[1]) && isAlpha(s[2]) && isDigit(s[3]))
		{return 1;}
	 else
	 {
		printf(KRED"wrong input , please try again\n"RESET); 
        return 0 ;
      }
	return 0;
}
void swap(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}
//////////////////////////////////////////////////////////////////

	void initboard(char* chessb){
	char chess[][8] =      {'r','n','b','q','k','b','n','r',
                            'p','p','p','p','p','p','p','p',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            ' ',' ',' ',' ',' ',' ',' ',' ',
                            'P','P','P','P','P','P','P','P',
                            'R','N','B','Q','K','B','N','R'};
	char* temp=(char*)chess;
	while((temp-(char*)chess)<64)*chessb++=*temp++;	
	}       


 ////////////////////////////////////////////////////////////////////////////////////////////// 

	void showchessboard(char chessb[ ][8]){
	char i,j;
	color_t txt;		// color text
	color_b  bg;		// color back ground
	color_a  at=all_off;	//attributes
	system("clear");
        printf("\e[%d;%dm\n\n\n\n\t\t   A  B  C  D  E  F  G  H\n",at,red_t);        
        for(i=0;i<8;i++)	//rows
        {
		change_bg;
		printf("\e[%d;%dm\t\t%c ",at,red_t,49+i);//the number on the left side
                for(j=0;j<8;j++){  //collums
			change_bg;
			change_tx; // if needed 			
			switch(chessb[i][j]){ 
				case 'r':print(rook);	
					break;
				case 'n': print(knite);
					break;
				case 'b': print(bishop);
					break;
				case 'q': print(qween);
					break;
				case 'k':print(king);
					break;
				case 'p': print(pion);
					break;
				case 'R': print(rook);
					break;
				case 'N':print(knite);
					break;
				case 'B':print(bishop);
					break;
				case 'Q':print(qween);
					break;
				case 'K':print(king);
					break;
				case 'P':print(pion);
					break;
				default :print(space);
			}

		}
                printf("\e[%d;%dm %d\n  ",at,red_t,i+1);//the number on the right side
        }   
        printf("%c[%d;%dm\t\t   A  B  C  D  E  F  G  H\n\n\n\n",'\e',at,red_t);
	printf("%c[%d;%dm",'\e',at,black_t);//back to default black text
        }
 //////////////////////////////////////////////////////////////////////////////////////////////
       
 void gotoxy(int x,int y)
{
  printf("%c[%d;%df ",0x1B,y,x);
}
             
        
        
        

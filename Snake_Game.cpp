#include<iostream>
#include<conio.h>
#include<time.h>
#include<windows.h>
using namespace std;
void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int main();
class Snake
{
      int length , no , bns , level_no , x , y , u , v;
      string str;
      struct space          //  Structure
      {    int bx , by;   struct space *next;   struct space *prev;  } *head, *tail;
    public:
      Snake() : length(9), no(9), bns(0), x(27), y(11), head(NULL), tail(NULL), str("+x")
      {
         rules();
         system("cls");  level();
      }
      void main_page()
      {
         for(int i=0;i<length;i++,x++)
         {
            struct space *temp=(struct space *)malloc(sizeof(struct space));
            temp->bx=x;          temp->by=y;
            temp->next=head;     temp->prev=NULL;
            if(head!=NULL)  head->prev=temp;
            head=temp;
            if(tail==NULL)  tail=head;
         }
         gotoxy(27,11);
         for(int i=0;i<length;i++)
         cout<<(char)254;      // Printing Snake
    
         srand(time(NULL));   // Initializing Seed random
          random();
    
          Sleep(2500);
          snake(str,x-1,y);
      }
       void color(int c)
       {
          SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
       }
       void snake(string str,int x,int y)
       {
          char key;
          while(!kbhit())
          {
              str=="+x"?x++:(str=="-x"?x--:(str=="+y"?y++:y--));
              color(543);
              if(!check_boundry(x,y)||check_itself(x,y))  game_over_box();
              gotoxy(x,y);    cout<<(char)254;   increment(x,y);    cancel();
              check_bonus(x,y);    waqt();
              color(15);
              Sleep(level_no);
          }	
          key=getch();
          if(key==72)       str="-y";   //up Key
          else if(key==75)  str="-x";   //left Key
          else if(key==77)  str="+x";   //right Key
          else if(key==80)  str="+y";   //down Key
          else if(key=='p')  {  char ch;   while((ch=getch())!='p');  }   // For Pause
          
          snake(str,x,y);
       }
       void game_over_box(int arg=0)
       {
          //Box  For Game over
          color(236);
    
          //  Small Box for Game Over writen
          gotoxy(24,6); for(int i=0;i<10;i++) cout<<"==";     // Uper line
    
          for(int i=0,z=7;i<2;i++,z++) {    gotoxy(24,z);  cout<<char (186);   }   //  left side line
          for(int i=0,z=7;i<2;i++,z++) {    gotoxy(43,z);  cout<<char (186);   }  //  Right side line
          //  Small Box Finish
    
          //  Larger Box for score
          gotoxy(24,9);    for(int i=0;i<10;i++)    cout<<"==";   // Uper Line
          gotoxy(24,15);   for(int i=0;i<10;i++)    cout<<"==";  //  Lower line
    
          for(int i=0, z=10;i<5;i++,z++) {  gotoxy(24,z);  cout<<char (186);  }  // Left Side line
          for(int i=0, z=10;i<5;i++,z++) {  gotoxy(43,z);  cout<<char (186);  } // Right Side line
          //   Larger Box finish
    
          color(13);
          if(arg==1)        // Wins
          {   gotoxy(27,7);    cout<<"Congratulations";   gotoxy(27,11);   cout<<" You Win! ";   }
    
          else  {   gotoxy(27,7);   cout<<" \aGame Over !";    // Lose
          gotoxy(27,11);   cout<<" Your Score ";  gotoxy(28,13);  cout<<" "<<bns<<" Points";  }
    
          //close box
    
          color(543);
          gotoxy(7,22);   for(int i=0;i<77;i++)   cout<<" ";
          gotoxy(13,22);  system("pause");   cin.ignore(2);
          
             //Closing or playing again
          system("cls");    /*gotoxy(27,11);
          cout<<"Play again? (Y/N)";   char reply;
          gotoxy(28,12);   cin>>reply;
          system("cls");
          if(reply=='y'||reply=='Y')  main(); */
          if( (MessageBox(NULL,"Do You want to Play Again?","Continue",4)) ==IDYES ) main();
          else comment_box();
       }
       inline bool check_boundry(int x_co,int y_co)
       {
          return(x_co>1&&y_co>3&&x_co<=77&&y_co<20);
       }
       bool check_itself(int x,int y)
       {
          struct space *temp=NULL;
          temp=head;
          for(int j=0;j<length&&temp->next!=NULL;j++)
          {
             if(temp->bx==x&&temp->by==y)
              return(true);
             else temp=temp->next;
          }
          return(false);
       }
       void random()
       {
           u=rand()%74;  v=rand()%15;
             gotoxy(u+=3,v+=4);
             check_random();
          int col=rand()%100;  if(col==17) col++;
          color(col);   cout<<"\f";
       }
       void check_random()
       {
          for(struct space *temp=head;temp!=tail->next;temp=temp->next)
            if(temp->bx==u&&temp->by==v)
             random();
       }
       void check_bonus(int x,int y)
       {
            if(u==x&&v==y) {  length++;   bns++;
            if(bns==100) game_over_box(1);  random();  gotoxy(72,2);  color(543);  cout<<bns; }
       }
       void decrement()
       {
            if(no==length){
            struct space *temp=tail;
            tail=tail->prev;   free(temp); }
            else no++;
       }
       void cancel()
       {
            gotoxy(tail->bx,tail->by);  cout<<" ";
            decrement();
       }
       void increment(int x, int y)
       {
            struct space *temp=(struct space *)malloc(sizeof(struct space));
            temp->bx=x;        temp->by=y;
            temp->next=head;   temp->prev=NULL;
            head->prev=temp;   head=temp;
       }
       void display()
       {
            for(int i=0;i<80;i++)   cout<<"*";  //top of the page
    
            gotoxy(0,24);   color(288);       //Bottom of the page
            for(int i=0;i<80;i++)   cout<<"*"; 
    
               // Boundaries
            gotoxy(0,3);    color(78);    //uper Boundary
            for(int i=0;i<80;i++)   cout<<"=";
    
            gotoxy(0,4);   for(int i=0;i<16;i++)   cout<<"||\n";   //left Boundary
    
            for(int t=4,i=0;i<16;i++,t++)  {  gotoxy(78,t);   cout<<"||";  }  //Right boundary
    
            gotoxy(0,20);    for(int i=0;i<80;i++)  cout<<"=";  //Lower boundary
            // Boundaries
    
            gotoxy(0,0);   color(543);   //retaining the color matching with background
    
            gotoxy(4,2);   color(543);   cout<<"   TIME: ";   gotoxy(25,2);   cout<<"DEVELOPED BY \"";
            color(90);   cout<<"MR.AAZIB SAFI";   color(543);   cout<<"\"";
            gotoxy(60,2);   cout<<"   POINTS : "<<bns;
    
            gotoxy(7,22);
            cout<<"\t>> Use Arrow keys !\t\t >> Press P for Pause";
       }
       void waqt()
       {
            static int min=0,sec=0,msec=0;
            msec++;
            if(msec>=25)
            {  sec++; msec=0;  }
            if(sec>=59)
            {  min++; sec=0; msec=0;  }
            gotoxy(13,2);
            cout<<min<<":"<<sec<<":"<<msec;
       }
       void rules()
       {
            system("color 30");
            cout<<"\n\n\n\t\t\tRULES AND REGULATIONS\n\n\n\t"
            <<" 1 >> User have to pick the points displayed in the screen.\n\n\t"
            <<" 2 >> Length of the snake will increase with every picked point.\n\n\t"
            <<" 3 >> Snake should not cross the boundaries and with itself also\n\t"
            <<"      otherwise game will be over.\n\n\t"
            <<" 4 >> Do not press arrow key opposite to the direction of movement of\n\t      Snake.\n\n\t"
            <<" 5 >> 100 points will make you a winner of the Snake Game.\n\n\t"
            <<"\n\t\t\tBEST OF LUCK !\n\n\t\t";
            system("Pause");
       }
       void level()
       { 
          cout<<"\n\n\t\t\tSELECT YOUR LEVEL";
          cout<<"\n\n\n\t\t1) Easy\n\n\n\t\t2) Normal\n\n\n\t\t3) Hard\n\n\t\t\tChoice(   )\b\b\b";
          cin>>level_no; if(level_no==1) level_no=150; else if(level_no==2) level_no=100; else level_no=60;
          system("cls");
       }
       void comment_box()
       {    
          system("cls");    system("color 30");
          // comment box start
          gotoxy(24,6);    for(int i=0;i<20;i++)   cout<<"==";        // Uper line of small box
          for(int i=0,z=7;i<2;i++,z++) {   gotoxy(24,z);  cout<<char (186);   }    // Left Line of small box
          for(int i=0,z=7;i<2;i++,z++) {   gotoxy(63,z);  cout<<char (186);   }   // Right Line of small box
    
          gotoxy(24,9);   for(int i=0;i<20;i++)   cout<<"==";   // Uper line of larger box
          gotoxy(24,15);  for(int i=0;i<20;i++)   cout<<"==";  // lower line of larger box
    
          for(int i=0, z=10;i<5;i++,z++) {  gotoxy(24,z);  cout<<char (186);  }  //Left Line of larger box
          for(int i=0, z=10;i<5;i++,z++) {  gotoxy(63,z);  cout<<char (186);  }  //Left Line of larger box
          // box finish
    
          gotoxy(30,8);    cout<<" Your Comment Please !";   //Writen in the box
    
          gotoxy(27,10);   for(int c=11,i=1;getche()!='\r';i++)    //Taking comment
          {   if(i==145)  {  Sleep(1500);  break; }   if(i%32==0)  gotoxy(27,c++);  }
                   
          system("cls");
          //Sending comment
          gotoxy(23,9);    cout<<"SENDING ";
          for(int i=0;i<6;i++)  {   cout<<char(254);   Sleep(700);  }
    
          system("cls");    gotoxy(20,9);
          cout<<"Your comment has been sent to MR.AAZIB SAFI\n\n\n\n\t\t\t";    system("pause");
          exit(0);
       }
};
int main()
{
       Snake obj;
       system("cls");
       gotoxy(23,9);
       cout<<"LOADING";
       for(int i=0;i<6;i++) {  cout<<char(254);  Sleep(700); }
       system("cls");
       system("color 1d");
       obj.display();
       obj.main_page();
}

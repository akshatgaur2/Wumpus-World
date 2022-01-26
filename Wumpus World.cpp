//Code By Akshat Gaur
#include <iostream>
#include <stdlib.h>
using namespace std;

int agent[2]={3,1}, value=0, u=1;
char face, path[50];
struct node{
    bool p=0 , w=0, t=0 , s=0 , b=0 , g=0;
    bool safe=0, agent=0, v=0;
    bool w1=0,p1=0;  //dangerzones
}arr[4][4];

//SOE !!!**
//Need to update!
void Risk(int &a, int &b, int x){
    if(x==1){
        //Wumpus
        if(a-1>=0){
            if(arr[a-1][b].safe == 1 || arr[a-1][b].v == 1){
                arr[a-1][b].w1=0;
            }
            else
                arr[a-1][b].w1=1;
        }
        if(a+1<=3){
            if(arr[a+1][b].safe == 1 || arr[a+1][b].v == 1){
                arr[a+1][b].w1=0;
            }
            else
                arr[a+1][b].w1=1;
        }
        if(b-1>=0){
            if(arr[a][b-1].safe == 1 || arr[a][b-1].v == 1){
                arr[a][b-1].w1=0;
            }
            else
                arr[a][b-1].w1=1;
        }
        if(b+1<4){
            if(arr[a][b+1].safe == 1 || arr[a][b+1].v == 1){
                arr[a][b+1].w1=0;
            }
            else
                arr[a][b+1].w1=1;
        }

    }
    else if(x==2){
        //Pit
        if(a-1>=0){
            if(arr[a-1][b].safe == 1 || arr[a-1][b].v == 1){
                arr[a-1][b].p1=0;
            }
            else
                arr[a-1][b].p1=1;
        }
        if(a+1<=3){
            if(arr[a+1][b].safe == 1 || arr[a+1][b].v == 1){
                arr[a+1][b].p1=0;
            }
            else
                arr[a+1][b].p1=1;
        }
        if(b-1>=0){
            if(arr[a][b-1].safe == 1 || arr[a][b-1].v == 1){
                arr[a][b-1].p1=0;
            }
            else
                arr[a][b-1].p1=1;
        }
        if(b+1<4){
            if(arr[a][b+1].safe == 1 || arr[a][b+1].v == 1){
                arr[a][b+1].p1=0;
            }
            else
                arr[a][b+1].p1=1;
        }
    }
    else if(x==3){
        if(a-1>=0){
                arr[a-1][b].safe=1;
        }
        if(a+1<=3){
                arr[a+1][b].safe=1;
        }
        if(b-1>=0){
                arr[a][b-1].safe=1;
        }
        if(b+1<4){
                arr[a][b+1].safe=1;
        }
    }

}
void Display(){
    int i,j;
    printf("\n\n");
    for(i=0;i<4;i++){
        printf("| ");
        for(j=0;j<4;j++){
            if(arr[i][j].p==1)
                printf("P");
            if(arr[i][j].w==1)
                printf("W");
            if(arr[i][j].t==1)
                printf("T");
            if(arr[i][j].s==1)
                printf("S");
            if(arr[i][j].b==1)
                printf("B");
            if(arr[i][j].g==1)
                printf("G");
            if(arr[i][j].agent==1)
                printf("A");

            //  Is block Safe?
            //     printf("?");
            printf("\t| ");
        }
        printf("\n");
    }
    printf("(P ->Pit ; - ->Safe ; W->Wumpus ; T-> Treasure ; S -> Stench ; B -> Breeze; G-> Glitter)");
}

void Turn(int x){
    switch(x){
        case 1: //left
        {
            switch(face){
                case 'N':
                {
                    face = 'W';
                    return;
                }
                case 'E':
                {
                    face = 'N';
                    return;
                }
                case 'S':
                {
                    face = 'E';
                    return;
                }
                case 'W':
                {
                    face = 'S';
                    return;
                }
                default:
                    break;
            }
        }
        case 2: //right
        {
            switch(face){
                case 'N':
                {
                    face = 'E';
                    return;
                }
                case 'E':
                {
                    face = 'S';
                    return;
                }
                case 'S':
                {
                    face = 'W';
                    return;
                }
                case 'W':
                {
                    face = 'N';
                    return;
                }
                default:
                    break;
            }
        }
        default:
            break;
    }
}

char Opp(char c){
    if (c=='N'){
        return 'S';
    }
    else if (c=='E'){
        return 'W';
    }
    else if (c=='W'){
        return 'E';
    }
    else if (c=='S'){
        return 'N';
    }
    return '\0';
}

void Backtrack(int &a, int &b){
    while(u>0){
        face = Opp(path[u]);
        // while(face != c){
        //     printf("\nTurning Right\n");
        //     Turn(2);
        // }

        arr[a][b].agent=0;
        arr[a][b].t=0;
        switch(face){
            case 'N':
            {
                a= a-1;
                break;
            }
            case 'E':
            {
                b= b+1;
                break;
            }
            case 'S':
            {
                a= a+1;
                break;
            }
            case 'W':
            {
                b= b-1;
                break;
            }
            default:
                break;
        }
        arr[a][b].agent=1;
        arr[a][b].t=1;
        Display();
        value-=1;
        path[u]='\0';
        u--;
    }
    value+=1000;
    printf("\nAgent got out of Cave with Gold!! (1000 pts)\n Victory!!!\t Your Final Score is: %d",value);
    exit(0);
}

bool Check(int &a,int &b){
    // Check Glitter (-pick), Wall(-Boink sound and return), Pit(value -1000, Game-over/Checkpoint), Wumpus (- Kill/shoot/Scream or Die(user choice))
    arr[a][b].v =1;

    if(arr[a][b].safe ==1) arr[a][b].safe =1;
    else if(arr[a][b].p ==1){
        printf("\nPit is here!\nYou fell into the pit and died ToT (lost 1000 pts)...\nStarting from the last Checkpoint\n");
        value-=1000;
        //visited = -1 ??
    }
    else if(arr[a][b].w ==1){
        printf("\nWumpus is here!!\n");
        //visited = -1 ??
        printf("\nAlert!!! Wumpus is here!\tWhat Should We Do??\n1. Shoot Wumpus (-10 pts)\n2. Die (Let him eat you)(-1000 pts)\n");
        int x;
        scanf("%d",&x);
        if(x==1){
            value-=10;
            printf("\nYou killed Wumpus.(lost 10 pts)\nScream Heard! Wumpusis DEAD. . . Game Continues\n");
            arr[a][b].w = 0;
        }
        else if(x==2){
            value-=1000;
            printf("\nGAME OVER! Wumpus ate you. (lost 1000 pts)\nStarting from last Checkpoint. . . \n");
        }

    }
    else{
        arr[a][b].safe =1;
    }

    if(arr[a][b].b ==1){
        printf("\nBreeze Sensed! Pit Near-by!!\n");
        //update Pit risk
        Risk(a,b,2);
    }
    if(arr[a][b].s ==1){
        printf("\nStench Sensed! Wumpus Near-by!!\n");
        //update wumpus risk
        Risk(a,b,1);
    }
    if(arr[a][b].g ==1){
        printf("\nGlitter Sensed! Treasure Found!!\nPath followed is: ");
        for (int i =0;i<u;i++)
            printf("%c -> ",path[i]);
        printf("%d.",path[u]);
        Display();
        printf("\nGrabbed the Treasure, Returning Home! :`)\n");
        Backtrack(a,b);

        //exit(0);
            //pick Treasure and backtrack!!!!!!
    }
    if(arr[a][b].b !=1 && arr[a][b].s !=1){
        // update surr as safe
        Risk(a,b,3);
    }
    //after updating risks check again for w? and p? together

    return 1;
}

void Follow(int &a, int &b){

    arr[a][b].agent=1;
    Display();
    if(!Check(a,b)){
        arr[a][b].agent=0;
       return;
    }   //SOE
    int x=a,y=b;
    for(int i =1; i<=5 ; i++){
        for (int i1=0; i1<4; i1++){
            if(i1==2 && i!=4) {
                Turn(1);
                printf("\nIts where the Agent came from, We don't wanna go there... NO!\nTurned Left\n");
                continue;
            } //SOE
            switch(face){
                case 'N':
                {
                    a= a-1;
                    break;
                }
                case 'E':
                {
                    b= b+1;
                    break;
                }
                case 'S':
                {
                    a= a+1;
                    break;
                }
                case 'W':
                {
                    b= b-1;
                    break;
                }
                default:
                    break;
            }

            //Check if inside
            if(a<0 || a>3 || b<0 || b>3){
                printf("\nMoving Forward. . .BUMP!! \tWoops there's a Wall!\n  Returned...\n");
                Turn(1);
                printf("\nTurned Left, Now facing: %c\n",face);
                a=x;
                b=y;
                value-=1;
                //continue;
            }
            else if(i==1 && (arr[a][b].safe == 1 || (arr[a][b].w1 ==1 && arr[a][b].p1 ==1) )){
                arr[x][y].agent=0;
                value-=1;
                path[u]=face;
                u++;
                Follow(a,b);
                path[u]='\0';
                u--;
            }
            //unknown?

            else if(i==2 && arr[b][b].w1 == 1){
                arr[x][y].agent=0;
                value-=1;
                path[u]=face;
                u++;
                Follow(a,b);
                path[u]='\0';
                u--;
            }
            else if(i==3 && arr[a][b].p1 == 1){
                arr[x][y].agent=0;
                value-=1;
                path[u]=face;
                u++;
                Follow(a,b);
                path[u]='\0';
                u--;
            }
            else if(i==4){
                arr[x][y].agent=0;
                value-=1;
                path[u]=face;
                u++;
                Follow(a,b);
                path[u]='\0';
                u--;
            }
            else{
                // turn left
                Turn(1);
                printf("Turned Left\tNow facing: %c\n",face);
                //continue;
            }
        }
    }
    // F --L -- F --L --F --L --F --x4

}


//  Updated!
void Sign(int &a, int &b){
    //make danger Sign Beginning
    if(arr[a][b].w==1){
        if(a<3) arr[a+1][b].s = 1;
        if(a>0) arr[a-1][b].s = 1;
        if(b<3) arr[a][b+1].s = 1;
        if(b>0) arr[a][b-1].s = 1;
    }
    else if(arr[a][b].p==1){
        if(a<3) arr[a+1][b].b = 1;
        if(a>0) arr[a-1][b].b = 1;
        if(b<3) arr[a][b+1].b = 1;
        if(b>0) arr[a][b-1].b = 1;
    }
    else if(arr[a][b].t==1) arr[a][b].g= 1;
}
void Coord (int &a,int &b){
    //Set Coord
    a=4-a;
    b=b-1;
}


int main()
{
    int i,a,b;
    cout<<"Enter Wumpus Coordinates(x,y) : ";
    cin>>a>>b;
    Coord(a,b);
    arr[a][b].w= 1;
    Sign(a,b);


    cout<<"Enter Gold Coin Coordinates(x,y) : ";
    cin>>a>>b;
    Coord(a,b);
    arr[a][b].t = 1;
    Sign(a,b);

    while (true){
        cout<<"Enter Pit Coordinates(x,y) : ";
        cin>>a>>b;
        Coord(a,b);
        arr[a][b].p = 1;
        Sign(a,b);

        cout<<"Do you want to add another Pit? [1]Yes [0]No : ";
        cin>>i;
        if(i==0) break;
    }

    arr[3][0].agent=1;
    arr[3][0].safe =1;
    arr[3][0].v =1;
    // Input Finish!

    //Display();
    face= 'E';
    a=3;b=0;
    path[0]='E';
    Follow(a,b);


    return 0;
}
//-1 ->pit ; 0->safe ; 1->Wumpus ; 2-> Treasure ; 3 -> Stench ; 4 -> Breeze; 5-> Glitter
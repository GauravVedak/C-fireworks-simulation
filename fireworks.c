#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<math.h>

int Particle(int D,int i);
int Colour(int i,int k,int t);
int Firenum;

struct firework{
    float fpx;
    float fpy;
    int type;
    float fvx;
    float fvy;
    int explode;
}fire[50];

struct partical{
    float ppx[80];
    float ppy[80];
    int co[80];
    float pvx[80];
    float pvy[80];
    float dia;
}par[50];

int main()
{
    int page=0;
    srand(time(0));  //random seed
    int i=0,j,f=0,gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    setfillstyle(SOLID_FILL,WHITE);
        Firenum=50;
        for(i=0;i<Firenum;i++){
            fire[i].explode=1;
            par[i].dia=0.0;
        }
        
        
        i=0;
        for(;;){
            setactivepage(page);
            cleardevice();
            setvisualpage(1-page);
            if(rand()%500<10){          //assign values  2%
                if(f>Firenum)
                    f=0;
                fire[f].fpx=rand()%getmaxx();
                fire[f].fpy=getmaxy();
                fire[f].fvy= -1*((rand()%400)/100.0 +2.5);
                fire[f].explode=0;
                fire[f].type=rand()%2;
                f++;
            }
             
            delay(4);

            for(i=0;i<Firenum;i++){             //values draw
                if(fire[i].fvy>=0){
                    Particle(fire[i].explode,i);
                }
                else{
                    setcolor(YELLOW);
                    circle((int)fire[i].fpx,(int)fire[i].fpy,5);
                    floodfill(fire[i].fpx,fire[i].fpy,YELLOW);
                    line(fire[i].fpx,fire[i].fpy+4+5,fire[i].fpx,(-4*fire[i].fvy) +fire[i].fpy+4+5);
                    line(fire[i].fpx+2,fire[i].fpy+4+5,fire[i].fpx+2,(-2*fire[i].fvy) +fire[i].fpy+4+5);
                    line(fire[i].fpx-2,fire[i].fpy+4+5,fire[i].fpx-2,(-2*fire[i].fvy) +fire[i].fpy+4+5);
                    line(fire[i].fpx+1,fire[i].fpy+4+5,fire[i].fpx+1,(-3*fire[i].fvy) +fire[i].fpy+4+5);
                    line(fire[i].fpx-1,fire[i].fpy+4+5,fire[i].fpx-1,(-3*fire[i].fvy) +fire[i].fpy+4+5);
                    fire[i].fpy+=fire[i].fvy;
                    fire[i].fvy+= 0.05;
                }
            }
            page = 1-page;
        }
    return 0;
}

int Particle(int D,int i){
    int k;
    double ang;
    if(D==0){
        for(k=0;k<80;k++){                  //assign value
            ang=2*3.141592*((double)(rand()%360)/360.0);
            par[i].ppx[k]=(int)fire[i].fpx;
            par[i].ppy[k]=(int)fire[i].fpy;
            par[i].pvx[k]=cos(ang)*(rand()%4 +1); //to calculate x axis
            par[i].pvy[k]=sin(ang)*(rand()%4 +1); //to calculate y axis
            par[i].co[k]=Colour(i,k,fire[i].type);
            par[i].dia=3.0;
        }
        fire[i].explode=1;
    }
    else{
        if(par[i].dia>=1.0){
            for(k=0;k<80;k++){
                setcolor(par[i].co[k]);
                circle(par[i].ppx[k],par[i].ppy[k],par[i].dia);
                par[i].ppx[k]+=par[i].pvx[k];
                par[i].ppy[k]+=par[i].pvy[k];
                par[i].pvy[k]+=0.1;
            }
            par[i].dia += -0.075;
        }
    }
    return 0;
}

int Colour(int i,int k,int t){  //
    switch(t){
        case 1:
            if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>6){
                return 5;
            }
            else if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>4){
                return 9;
            }
            else if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>2){
                return 11;
            }
            else{
                return 10;
            }
            break;
        case 0:
            if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>6){
                return 4;
            }
            else if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>4){
                return 13;
            }
            else if(abs(par[i].pvx[k])+abs(par[i].pvy[k])>2){
                return 12;
            }
            else{
                return 15;
            }
            break;
    }
}
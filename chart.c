#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
int statNum;
char* states0;
char* states1;
char* states2;
int* outputs1;
int* outputs2;
}mealy;

typedef struct{
int statNum;
char* states0;
char* states1;
char* states2;
int* outputs;
}moore;

typedef struct{
int work;
int s1,s2;
int s3,s4;
}square;

int findIndex(char*states,int num,char s){
for(int i=0;i<num;i++){
  if(states[i]==s){
return i;
  }
}
}


int findMax(int a,int b){
  return a>b?a:b;
}


mealy*createMeS(){
mealy*MeS=malloc(sizeof(mealy));
printf("Enter the number of states in the table:");
scanf("%d",&(MeS->statNum));
MeS->states0=malloc(MeS->statNum);
MeS->states1=malloc(MeS->statNum);
MeS->states2=malloc(MeS->statNum);
MeS->outputs1=malloc(MeS->statNum*sizeof(int));
MeS->outputs2=malloc(MeS->statNum*sizeof(int));
return MeS;
}

moore*createMoS(){
moore *MoS=malloc(sizeof(moore));
printf("Enter the number of states in the table:");
scanf("%d",&(MoS->statNum));
MoS->states0=malloc(MoS->statNum);
MoS->states1=malloc(MoS->statNum);
MoS->states2=malloc(MoS->statNum);
MoS->outputs=malloc(MoS->statNum*sizeof(int));
return MoS;
}



mealy* readTableMealy(mealy*mes){

//mealy*mes= createMeS();
printf("Enter the initial states:");

for(int i=0; i<mes->statNum; i++){
scanf(" %c",& mes->states0[i]);
}

printf("Enter the  next states in the input=0 case:");

for(int i=0; i<mes->statNum; i++){
scanf(" %c",& mes->states1[i]);
}

printf("Enter the next states in the input=1 case:");

for(int i=0; i<mes->statNum; i++){
scanf(" %c",& mes->states2[i]);
}

printf("Enter the outputs in the input=0 case:");

for(int i=0; i<mes->statNum; i++){
scanf("%d",& mes->outputs1[i]);
}

printf("Enter the outputs in the input=1 case:");

for(int i=0; i<mes->statNum; i++){
scanf("%d",& mes->outputs2[i]);
}
  return mes;
}

moore*readTableMoore(moore*mos){
//moore*mos=createMoS();
printf("Enter the initial states:");

for(int i=0; i<mos->statNum; i++){
scanf(" %c",& mos->states0[i]);
}

printf("Enter the next states when input=0 case :");

for(int i=0; i<mos->statNum; i++){
scanf(" %c",& mos->states1[i]);
}
printf("Enter the next states when input=1 case :");

for(int i=0; i<mos->statNum; i++){
scanf(" %c",& mos->states2[i]);
}

printf("Enter the outputs :");

for(int i=0; i<mos->statNum; i++){
scanf("%d",& mos->outputs[i]);
}
return mos;
}

void implicationChartMealy(mealy*mes){
int rows=mes->statNum-1;
square **chart=malloc(rows*sizeof(square*));
for(int i=0;i<rows;i++){
chart[i]=malloc((i+1)*sizeof(int));}

for(int i=0;i<mes->statNum;i++){
for(int j=i+1;j<mes->statNum;j++){
  if(mes->outputs1[i]!=mes->outputs1[j]||mes->outputs2[i]!=mes->outputs2[j]){
     chart[j-1][i].work=-1;
  }}}

for(int i=0;i<mes->statNum;i++){
for(int j=i+1;j<mes->statNum;j++){
if(chart[j-1][i].work!=-1){
chart[j-1][i].s1=mes->states1[i];
chart[j-1][i].s2=mes->states1[j];
chart[j-1][i].s3=mes->states2[i];
chart[j-1][i].s4=mes->states2[j];
}}}

int new=-1;

while(new==-1){
new=0;
for(int i=0;i<mes->statNum;i++){
for(int j=i+1;j<mes->statNum;j++){
if(chart[j-1][i].work==-1){
continue;
}
else{
int r1=findIndex(mes->states0,mes->statNum,chart[j-1][i].s1);
int c1=findIndex(mes->states0,mes->statNum,chart[j-1][i].s2);
int max1=findMax(r1,c1);
int r2=findIndex(mes->states0,mes->statNum,chart[j-1][i].s3);
int c2=findIndex(mes->states0,mes->statNum,chart[j-1][i].s4);
int max2=findMax(r2,c2);
if(chart[max1-1][(r1+c1)-max1].work==-1||chart[max2-1][(r2+c2)-max2].work==-1){
  chart[j-1][i].work=-1;
new=-1;
}}}
}
}
char red[mes->statNum];
memcpy(red, mes->states0, mes->statNum);
for(int i=0;i<mes->statNum;i++){
for(int j=i+1;j<mes->statNum;j++){
if(chart[j-1][i].work!=-1){
red[j]=red[i];
}
}
}

for(int i=0;i<mes->statNum;i++){
int vis=0;
if(red[i]!=mes->states0[i])
continue;
for(int j=0;j<mes->statNum;j++){
  if(red[j]==mes->states0[i]){
    if(vis==0){
    printf("{%c",mes->states0[j]);
    vis=1;}
    else{
    printf(",%c",mes->states0[j]);
    }
}
} 
if(vis==1)
 printf("}");  
}
}

void implicationChartMoore(moore*mos){
int rows=mos->statNum-1;
square **chart=malloc(rows*sizeof(square*));
for(int i=0;i<rows;i++){
chart[i]=malloc((i+1)*sizeof(int));}

for(int i=0;i<mos->statNum;i++){
for(int j=i+1;j<mos->statNum;j++){
  if(mos->outputs[i]!=mos->outputs[j]||mos->outputs[i]!=mos->outputs[j]){
     chart[j-1][i].work=-1;
  }}}

for(int i=0;i<mos->statNum;i++){
for(int j=i+1;j<mos->statNum;j++){
if(chart[j-1][i].work!=-1){
chart[j-1][i].s1=mos->states1[i];
chart[j-1][i].s2=mos->states1[j];
chart[j-1][i].s3=mos->states2[i];
chart[j-1][i].s4=mos->states2[j];
}}}

int new=-1;

while(new==-1){
new=0;
for(int i=0;i<mos->statNum;i++){
for(int j=i+1;j<mos->statNum;j++){
if(chart[j-1][i].work==-1){
continue;
}
else{
int r1=findIndex(mos->states0,mos->statNum,chart[j-1][i].s1);
int c1=findIndex(mos->states0,mos->statNum,chart[j-1][i].s2);
int max1=findMax(r1,c1);
int r2=findIndex(mos->states0,mos->statNum,chart[j-1][i].s3);
int c2=findIndex(mos->states0,mos->statNum,chart[j-1][i].s4);
int max2=findMax(r2,c2);
if(chart[max1-1][(r1+c1)-max1].work==-1||chart[max2-1][(r2+c2)-max2].work==-1){
  chart[j-1][i].work=-1;
new=-1;
}}}
}
}
char red[mos->statNum];
memcpy(red, mos->states0, mos->statNum);
for(int i=0;i<mos->statNum;i++){
for(int j=i+1;j<mos->statNum;j++){
if(chart[j-1][i].work!=-1){
red[j]=red[i];
}
}
}

for(int i=0;i<mos->statNum;i++){
int vis=0;
if(red[i]!=mos->states0[i])
continue;
for(int j=0;j<mos->statNum;j++){
  if(red[j]==mos->states0[i]){
    if(vis==0){
    printf("{%c",mos->states0[j]);
    vis=1;}
    else{
    printf(",%c",mos->states0[j]);
    }
}
} 
if(vis==1)
 printf("}");  
}
}


int main(){
int type;
printf("Is it 1.mealy or 2.moore system:");
scanf("%d",&type);
if(type==1){
mealy*mes=createMeS();
readTableMealy(mes);
implicationChartMealy(mes);}
if(type==2){
moore*mos=createMoS();
readTableMoore(mos);
implicationChartMoore(mos);
}
return 0; }   

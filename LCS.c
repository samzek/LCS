#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum Direction {UP,HOR,DIAG,HORUP} Direction;

typedef struct matrix_t {
	int len;
	Direction dir;
}Matr;

Matr *LCS_Length(char *A,char *B){

int lenA = strlen(A);
int lenB = strlen(B);
Matr *m = (Matr *) malloc ((lenA)*(lenB)*sizeof(Matr));

int i;
for(i = 1; i < lenA;i++)
	m[i].len = 0;
int j;
for (j = 0; j < lenB;j++)
	m[j*lenA].len = 0;

for(i = 1; i < lenA;i++){
    for (j = 1; j < lenB;j++){
		if (A[i] == B[j]){
			m[j + (i * lenB)].len = m[(j-1) + (i-1)*lenB].len + 1;
			//printf("DIAG A[i]=%c B[i]=%c len=%d\n",A[i],B[j],m[j + (i * lenB)].len);
			m[j + (i*lenB)].dir = DIAG;
		}
		else if (m[j + (i-1) * lenB].len >= m[(j-1) + (i*lenB)].len){
			m[j + i*lenB].len = m[j + (i-1)*lenB].len;
		//	printf("UP A[i]=%c B[i]=%c len=%d\n",A[i],B[j],m[j + (i * lenB)].len);
			m[j + i*lenB].dir = UP;
		}
		else {
			m[j + i*lenB].len = m[(j-1) + i*lenB].len;
                  //   printf("HOR A[i]=%c B[i]=%c len=%d\n",A[i],B[j],m[j + (i * lenB)].len);
			m[j + i*lenB].dir = HOR;
		}	
	}
}					
return m;
};

void Print_LCS(Matr *m,int i,int j,char *A,int lenB){

if ((i == 0) || (j ==0))
	return;
if (m[j + (i*lenB)].dir == DIAG){
	Print_LCS(m,i-1,j-1,A,lenB);
	printf("%c",A[i]);
}
else if (m[j+(i*lenB)].dir == UP)
	Print_LCS(m,i-1,j,A,lenB);
else
	Print_LCS(m,i,j-1,A,lenB);

};

int main(int argc,char **argv){

FILE *file = fopen(argv[1], "r");
char line[1024];
char *A;
char *B;
int i,endA,endB;
Matr *lcs;
while (fgets(line, 1024, file)) {
	if (line[0] == '\n')
		continue;
	else {
		endA = 0;
		while (line[endA] != ';')endA++;
		A = (char *) malloc ((endA+1) *sizeof(char));
		for (i = 0; i < endA;i++)
			A[i+1] = line[i];
		A[0] = '0';
		endB = 0;
		while (line[endB+endA+1] != '\n') endB++;
		B = (char *) malloc ((endB+1) *sizeof(char));
		for (i = 0;i < endB;i++)
			B[i+1] = line [endA+1 + i];
		B[0] = '0';
	//	printf("%s;%s\n",A,B);
		lcs = LCS_Length(A,B);
		//printf("len A=%d;len B=%d\n",strlen(A),strlen(B));
		//printf("lcs[lenA][lenB]=%d\n",lcs[strlen(B)-1+(strlen(A)-1)*(strlen(B)-1)].len);
		Print_LCS(lcs,strlen(A)-1,strlen(B)-1,A,strlen(B));
		if(lcs[endB + endA*strlen(B)].len > 0)
			printf("\n");
	}	
}
return 0;

}



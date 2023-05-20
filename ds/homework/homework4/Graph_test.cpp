#include "../../Header/GraphMatrix.h"
#include <stdlib.h>
int main() {
	GraphMatrix<char, int> g;
	int n = 10;
	int e = 60;
	char vectex1 = (char) ('A' + rand()%25);
	char vectex2 = (char) ('A' + rand()%25);
	char vectex3 = (char) ('A' + rand()%25);
	char vectex4 = (char) ('A' + rand()%25);
	char vectex5 = (char) ('A' + rand()%25);
	char vectex6 = (char) ('A' + rand()%25);
	char vectex7 = (char) ('A' + rand()%25);
	char vectex8 = (char) ('A' + rand()%25);
	char vectex9 = (char) ('A' + rand()%25);
	char vectex10 = (char) ('A' + rand()%25);
	g.insert ( vectex1 );
	g.insert ( vectex2 );
	g.insert ( vectex3 );
	g.insert ( vectex4 );
	g.insert ( vectex5 );
	g.insert ( vectex6 );
	g.insert ( vectex7 );
	g.insert ( vectex8 );
	g.insert ( vectex9 );
	g.insert ( vectex10 );
	for(int i = 0; i <10; i++) {
		printf("%c ",g.V[i].data);
	}
	int count = 0;
	for(int i = 0; i<10; i++)
		for(int j = i+1; j <10; j++) {
			int z = 1;

			if (rand()%100 >= 50&&z<=e) {
				g.insert(z,rand()%9,i,j);
				g.insert(z,rand()%9,j,i);
			}
			z = z+3;
		}


	printf("\nÁÚ½Ó¾ØÕó\n");
	for(int i =0; i<10; i++) {
		for (int j =0; j<10; j++) {
			if ( g.exists (i, j))
				printf(" %d ",g.weight(i,j));
			else
				printf(" 0 ");
		}
		printf("\n");
	}
	cout<<"²âÊÔbfs£º"<<endl;
	g.bfs(1);
	cout<<"²âÊÔdfs£º"<<endl;
	g.dfs(1);


	printf("×î¶ÌÂ·¾¶°¸Àı\n");
	DijkstraPU<char,int> Dij;
	g.pfs(0,Dij);
	for (int i = 9; i>0 ; i-- ) {
		int j = i;
		printf("%c->",g.vertex(j));
		while( g.parent(j) != 0) {
			j = g.parent(j);
			printf("%c->",g.vertex(j));
		}
		printf("%c\n",g.vertex(0));
	}

	printf("×îĞ¡Ö§³ÅÊ÷°¸Àı");
	PrimPU<char,int> mintree;
	printf("\n");
	g.pfs(0,mintree);
	for (int i = 9; i>0 ; i-- ) {
		int j = i;
		printf("%c->",g.vertex(j));
		int c = 0;
		while( g.parent(j) != 0) {
			c = c+g.weight(g.parent(j),j);
			j = g.parent(j);
			printf("%c->",g.vertex(j));
		}
		c = c+g.weight(g.parent(j),j);
		printf("%c  ",g.vertex(0));
		printf("%d \n",c);
	}

}



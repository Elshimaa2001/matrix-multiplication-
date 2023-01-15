#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]
struct element{
    int row;
    int column;
    int l;
    int m;
    int n;
    int* A; 
    int* B; 
    int* C;

};
/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void matmult(int* A, int* B, int* C, int l, int m, int n)
{
    for(int i=0; i<l; i++)
        for(int j=0; j<n; j++)
        {
            int sum = 0;
            for(int k=0; k<m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}
/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
 ////////////////row by row
void *method1(void *thing)
 {struct element *value = (struct element *) thing;
 int n=value->n;
 for( int j = 0 ; j < n ; j++ )
    { 
    	int l=value->l;
    	int m=value->m;
    	int i=value->row;
    	int* A=value->A; 
    	int* B=value->B; 
    	int* C=value->C;
        int sum1 = 0;
        for( int k = 0 ; k < m ; k++ )
        {
            sum1+=Item(A,i,k,m)*Item(B,k,j,n);
            Item(C,i,j,n)=sum1;  
        }
    }
    pthread_exit(NULL);}

void matmult_v2(int* A, int* B, int* C, int l, int m, int n)
{
   
    pthread_t meth[l];
    for(int i=0;i<l;i++){
    	struct element *temp1 = malloc(sizeof(struct element));
            temp1->A=A;
            temp1->B=B;
            temp1->C=C;
            temp1->l=l;
            temp1->m=m;
            temp1->n=n;
            temp1->row=i;
        //creating thread for row
        pthread_create(&meth[i],NULL,*method1,(void*)temp1);
       }
    for(int i=0;i<l;i++){
        pthread_join(meth[i], NULL);
    }
}



/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
 /////////////////////element by elemnt
 void * method3(void *thing){
    struct element *value = (struct element *) thing;
    int i=value->row;
    int j=value->column;
    int l=value->l;
    int m=value->m;
    int n=value->n;
    int* A=value->A; 
    int* B=value->B; 
    int* C=value->C;
    int sum=0;
     
    for(int l1=0;l1<m;l1++){
        sum+=Item(A,i,l1,m)*Item(B,l1,j,n);
        Item(C,i,j,n)=sum;
    }
    pthread_exit(NULL);
}
void matmult_v1(int* A, int* B, int* C, int l, int m, int n)
{
    pthread_t high[l*n];
    int k=0;
    for(int i=0;i<l;i++){
        for(int j=0;j<n;j++){
            struct element *tempp = malloc(sizeof(struct element));
            tempp->A=A;
            tempp->B=B;
            tempp->C=C;
            tempp->l=l;
            tempp->m=m;
            tempp->n=n;
            tempp->row=i;
            tempp->column=j;
     
            pthread_create(&high[k++],NULL,*method3,tempp);
           
             
        }}
        for(int t=0;t<l*n;t++)
        {
        pthread_join(high[t], NULL);
        }
    }
    
      
    


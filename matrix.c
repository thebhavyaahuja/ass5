#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

Matrix* create_matrix(int r,int c){
    Matrix* m=(Matrix*)malloc(sizeof(Matrix));
    m->num_rows=r;
    m->num_cols=c;
    m->data=(long long int**)calloc(r,sizeof(long long int*));
    for(int i=0;i<r;i++){
        m->data[i]=(long long int*)calloc(c,sizeof(long long int));
    }
    return m;
}

void destroy_matrix(Matrix* m){
    if(m==NULL){
        return;
    }
    for(int i=0;i<m->num_rows;i++){
        free(m->data[i]);
        m->data[i]=NULL;
    }
    free(m->data);
    free(m);
}

Matrix* add_matrix(Matrix* A,Matrix* B){
    if(A->num_rows!= B->num_rows || A->num_cols!= B->num_cols){
        return NULL;
    }
    else{
        Matrix* C = create_matrix(A->num_rows,A->num_cols);
        for(int i=0;i<A->num_rows;i++){
            for(int j=0;j<A->num_cols;j++){
                C->data[i][j]= A->data[i][j] + B->data[i][j];
            }
        }
        return C;
    }
}

Matrix* mult_matrix(Matrix* A, Matrix* B){
    if(A->num_cols != B->num_rows){
        return NULL;
    }
    else{
        Matrix* C = create_matrix(A->num_rows, B->num_cols);
        for(int i = 0; i < A->num_rows; i++){
            for(int j = 0; j < B->num_cols; j++){
                for(int k = 0; k < A->num_cols; k++){
                    C->data[i][j] += A->data[i][k] * B->data[k][j];
                }
            }
        }
        return C;
    }
}

Matrix* scalar_mult_matrix(long long int s, Matrix* M){
    Matrix* C = create_matrix(M->num_rows,M->num_cols);
    for(int i=0;i<M->num_rows;i++){
        for(int j=0;j<M->num_cols;j++){
            C->data[i][j]= M->data[i][j] *s;
        }
    }
    return C;
}

Matrix* transpose_matrix(Matrix* A){
    Matrix* C = create_matrix(A->num_cols,A->num_rows);
    for(int i=0;i<A->num_cols;i++){
        for(int j=0;j<A->num_rows;j++){
            C->data[i][j]= A->data[j][i];
        }
    }
    return C;
}

Matrix* submatrix(Matrix* M, int r, int c){//excludes this row and column from matrix
    Matrix* new= create_matrix(M->num_rows-1,M->num_cols-1);
    int newi=0,newj=0;
    for(int i=0;i<M->num_rows;i++){
        if(i==r){
            continue;
        }
        for(int j=0;j<M->num_rows;j++){
            if(j==c){
              continue;
            }
            new->data[newi][newj]=M->data[i][j];
            newj++;
        } 
        newj=0;
        newi++;
    }
    return new;
}

long long int determinant(Matrix* M){
    if(M->num_rows!=M->num_cols){
        return -1;
    }
    else{
        if(M->num_rows==1){
            return M->data[0][0];
        }
        if(M->num_rows==2){
            return M->data[0][0]*M->data[1][1] - M->data[0][1]*M->data[1][0];
        }
        else{
            long long int d=0;
            for(int i=0;i<M->num_cols;i++){
                Matrix* sub=submatrix(M,0,i);
                long long int Cf=M->data[0][i]* determinant(sub);
                destroy_matrix(sub);
                if(i%2==0){
                    d+=Cf;
                }
                else{
                    d+=-Cf;
                }
            }
            return d;
        }
    }
    return ;
}

void print_matrix(Matrix* m) {
    printf("%d %d\n", m->num_rows, m->num_cols);
    for (int i = 0; i < m->num_rows; i++) {
        for (int j = 0; j < m->num_cols; j++) {
            printf("%lld ", m->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* read_matrix_from_file(char* filename){
    FILE* fptr = fopen(filename,"r");
    if(fptr==NULL){
        printf("ERROR: INVALID ARGUMENT\n");
        return NULL;
    }
    int num_rows,num_cols;
    if(fscanf(fptr,"%d %d",&num_rows,&num_cols)!=2){
        printf("ERROR: INVALID ARGUMENT\n");
        return NULL;
    }
    Matrix* M=create_matrix(num_rows,num_cols);
    for(int i=0;i<num_rows;i++){
        for(int j=0;j<num_cols;j++){
            if(fscanf(fptr,"%lld",&M->data[i][j])!=1){
                printf("ERROR: INVALID ARGUMENT\n");
                fclose(fptr);
                destroy_matrix(M);
                return NULL;
            }
        }
    }
    fclose(fptr);
    return M;
}

void write_matrix_to_file(char* filename, Matrix* M){
    FILE* fptr=fopen(filename,"w");
    if(fptr==NULL){
        printf("ERROR: INVALID ARGUMENT\n");
        return NULL;
    }
    fprintf(fptr,"%d %d\n",M->num_rows,M->num_cols);
    for(int i=0;i<M->num_rows;i++){
        for(int j=0;j<M->num_cols;j++){
            fprintf(fptr,"%lld ",M->data[i][j]);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return NULL;
}





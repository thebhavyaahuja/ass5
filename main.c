#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    int q;
    scanf("%d",&q);
    FILE* file=fopen("mx_history","a");

    for(int i=0;i<q;i++){
        char s[20];
        int x;
        scanf("%s",&s);

        if(strcmp(s,"history")==0){
            fprintf(file,"LOG::history\n");
            fclose(file);
            file=fopen("mx_history","r");
            char c;
            while((c=fgetc(file))!=EOF){
                printf("%c",c);
            }
            fclose(file);
            file=fopen("mx_history","a");
        }
        else{
           scanf("%d",&x);
           fprintf(file,"LOG::%s %d\n",s,x);
        }
        if(strcmp(s,"add_matrix")==0){
            if(x==0){
                int m,n;
                scanf("%d %d",&m,&n);
                scanf("\n");
                Matrix* M=create_matrix(m,n);
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        scanf("%lld",&M->data[i][j]);
                    }
                }
                int o,p;
                scanf("%d %d",&o,&p);
                scanf("\n");
                Matrix* N=create_matrix(o,p);
                for(int i=0;i<o;i++){
                    for(int j=0;j<p;j++){
                        scanf("%lld",&N->data[i][j]);
                    }
                }
                Matrix* K=add_matrix(M,N);
                if(K==NULL){
                    printf("ERROR: INVALID ARGUMENT\n");
                }
                else{print_matrix(K);}
            }
            if(x==1){
                char file1[5000];
                char file2[5000];
                char ofile[5000];
                scanf("%s %s %s",file1,file2,ofile);
                Matrix* M=read_matrix_from_file(&file1);
                Matrix* N=read_matrix_from_file(&file2);
                Matrix* K=add_matrix(M,N);
                if(K==NULL){
                    printf("ERROR: INVALID ARGUMENT\n");
                }
                else{
                    write_matrix_to_file(&ofile,K);
                }
            }
        }
        if(strcmp(s,"mult_matrix")==0){
            if(x==0){
                int m,n;
                scanf("%d %d",&m,&n);
                scanf("\n");
                Matrix* M=create_matrix(m,n);
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        scanf("%lld",&M->data[i][j]);
                    }
                }
                int o,p;
                scanf("%d %d",&o,&p);
                scanf("\n");
                Matrix* N=create_matrix(o,p);
                for(int i=0;i<o;i++){
                    for(int j=0;j<p;j++){
                        scanf("%lld",&N->data[i][j]);
                    }
                }
                Matrix* K=mult_matrix(M,N);
                if(K==NULL){
                    printf("ERROR: INVALID ARGUMENT\n");
                }
                else{print_matrix(K);}
            }
            if(x==1){
                char file1[5000];
                char file2[5000];
                char ofile[5000];
                scanf("%s %s %s",file1,file2,ofile);
                Matrix* M=read_matrix_from_file(&file1);
                Matrix* N=read_matrix_from_file(&file2);
                Matrix* K=mult_matrix(M,N);
                if(K==NULL){
                    printf("ERROR: INVALID ARGUMENT\n");
                }
                else{
                    write_matrix_to_file(&ofile,K);
                }
            }
        }
        if(strcmp(s,"transpose_matrix")==0){
            if(x==0){
                int m,n;
                scanf("%d %d",&m,&n);
                scanf("\n");
                Matrix* M=create_matrix(m,n);
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        scanf("%lld",&M->data[i][j]);
                    }
                }
                Matrix* K=transpose_matrix(M);
                print_matrix(K);
            }
            if(x==1){
                char file1[5000];
                char ofile[5000];
                scanf("%s %s",file1,ofile);
                Matrix* M=read_matrix_from_file(&file1);
                Matrix* K=transpose_matrix(M);
                write_matrix_to_file(&ofile,K);
            }
        }
        if(strcmp(s,"scalar_mult_matrix")==0){
            int s;
            scanf("%d",&s);
            if(x==0){
                int m,n;
                scanf("%d %d",&m,&n);
                scanf("\n");
                Matrix* M=create_matrix(m,n);
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        scanf("%lld",&M->data[i][j]);
                    }
                }
                Matrix* K=scalar_mult_matrix(s,M);
                print_matrix(K);
            }
            if(x==1){
                char file1[5000];
                char ofile[5000];
                scanf("%s %s",file1,ofile);
                Matrix* M=read_matrix_from_file(&file1);
                Matrix* K=scalar_mult_matrix(s,M);
                write_matrix_to_file(&ofile,K);
            }
        }
        if(strcmp(s,"determinant")==0){
            if(x==0){
                int m,n;
                scanf("%d %d",&m,&n);
                scanf("\n");
                Matrix* M=create_matrix(m,n);
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        scanf("%lld",&M->data[i][j]);
                    }
                }
                int K=determinant(M);
                if(M->num_rows!=M->num_cols){
                    printf("ERROR: INVALID ARGUMENT");
                }
                else{
                    printf("%d\n",K);
                }
            }
            if(x==1){
                char file1[5000];
                scanf("%s",file1);
                Matrix* M=read_matrix_from_file(&file1);
                int K=determinant(M);
                if(M->num_rows!=M->num_cols){
                    printf("ERROR: INVALID ARGUMENT\n");
                }
                else{
                    printf("%d\n",K);
                }
            }
        }
    }
    return 0;
}


#include<stdio.h>

//variable declaration
int n,constMatrix[20][20];
//structure
struct routes{
    int distance[100];
    int adjNode[100];
}node[100];


//function to write the cost matrix
void readCostMatrix(){
    int i,j;
    printf("\nenter the costMatrix: \n");
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            scanf("%d",&constMatrix[i][j]);
            constMatrix[i][i]=0;
            node[i].distance[j]=constMatrix[i][j];
            node[i].adjNode[j]=j;

        }
    }
}

//function to  compute the routing table
void computeRoutingTable(){
    int i,j,k;
    for(i=0;i<n;++i){
        for(j=0;j<n;++j){
            for(k=0;k<n;++k){
                //if i to j distance > i to k then k to j then update it .
                if(node[i].distance[j]> constMatrix[i][k]+node[k].distance[j]){
                    node[i].distance[j]=node[i].distance[k]+node[k].distance[j];
                    node[i].adjNode[j]=k;
                }
            }
        }
    }

}
//function to display routing table
void displayTable(){
    int i,j;
    for(i=0;i<n;++i){
        printf("\nROUTE %d",i+1);
        for(j=0;j<n;++j){
            printf("\nnode %d via %d : distance %d", j+1,node[i].adjNode[j]+1,node[i].distance[j]);
        }
        printf("\n");
    }

}

//main function
void main(){
    printf("\nEnter the no of nodes : %s");
    scanf("%d",&n);

    readCostMatrix();
    computeRoutingTable();
    displayTable();
}

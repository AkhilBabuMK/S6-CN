//1 - read all the data
//2 - you have to print the bucket state based on the user inputs
//3 - 2 states = the user input successfully stored; some pkt will dropped due to over flow
//4 - also have some outgoing pkts
#include<stdio.h>
int main(){
    int incoming, outgoing, buck_size, n, store = 0;
    printf("Enter bucket size, outgoing rate and no of inputs: ");
    scanf("%d %d %d", &buck_size, &outgoing, &n);

    while (n != 0) {
        printf("Enter the incoming packet size : ");
        scanf("%d", &incoming);
        printf("Incoming packet size %d\n", incoming);
        if (incoming <= (buck_size - store)){
            store += incoming;
            printf("Bucket buffer size %d out of %d\n", store, buck_size);
        } else {
            printf("Dropped %d no of packets\n", incoming - (buck_size - store));
            printf("Bucket buffer size %d out of %d\n", store, buck_size);
            store = buck_size;
        }
        store = store - outgoing;
        if(store < 0)
            store = 0;
        printf("After outgoing %d packets left out of %d in buffer\n", store, buck_size);
        n--;
    }
}
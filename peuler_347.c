#include <stdio.h>
#include<math.h>

long long int M(int p, int q, int N){
    //WATCH OUT: p>q, p!=q OTHERWISE IT DOESN'T WORK
    int i,j,sum=0;
    double num=1.0,max=0.0;

    //Maximum number of factors obtained checking how much p are needed to obtain num<=N
    while(num<=(N*1.0)){
        num*=q;
        sum+=1;
    }
    num/=q;
    sum-=1;

    //Try all the combinations of p, q and 1 in order to calculate num
    //provided that num<=N and p,q have no 0 exponent
    for(i=sum-1;i>0;i--){
        for(j=1;j<=sum-i;j++){
            num = pow(p,i)*pow(q,j);
            if((num>max)&&(num<=(N*1.0))){
                max=num;
            }
        }
    }

    return (long long int) max;

}

unsigned int is_prime(int N){
    int i,max;
    if(N<2){return 0;}
    if(N==2){return 1;}
    max = ceil(sqrt(N));
    for (i=2;i<=max;i++){
        if(N%i==0){return 0;}
    }
    return 1;

}

int primes_lesseq_than(int N, int* list){
    int i, num = 0;
    for(i=0;i<=N;i++){
        if(is_prime(i)){
            list[num]=i;
            num+=1;
        }
    }
    return num;
}

//8 byte variable in order to avoid oversize when N=E7
long long int S(int N,int* list_primes,int num_primes){
    //WATCH OUT: list_primes is crescent order, OTHERWISE IT DOESN'T WORK
    int i,j,product;
    long long int sum=0,m;

    for(i=0;i<num_primes-1;i++){
        for(j=i+1;j<num_primes;j++){
            product = list_primes[i]*list_primes[j];
            if(product<=N){
                m = M(list_primes[j],list_primes[i],N);
                sum+=m;
            }
            else{break;} //We jump next prime because higher j -> higher product -> always larger than previous
        }
    }

    return sum;
}

int main(){
    int p=5,q=3,N=10000000;
    printf("Choose N = ");
    scanf("%d",&N);
    int list_primes[500000]; //For N=E7, we need to store first N/2 primes = 348513
    int num_primes=0,num_pairs=0;
    long long int sum=0;

    //We only need factors<=N/2 because 2 is the lowest factor and must be p*q<=N
    num_primes = primes_lesseq_than(N/2,list_primes);

    printf("# of primes = %d\n",num_primes);

    //Obtain p,q pairs suitable for N selected
    sum = S(N,list_primes,num_primes);
    printf("S(%d)=%lld\n",N,sum);


    return 0;
}

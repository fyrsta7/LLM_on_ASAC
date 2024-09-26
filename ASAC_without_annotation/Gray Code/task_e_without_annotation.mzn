int: n;
int: k;
int: max_n=pow(2,n);
array[1..n,1..max_n,1..n] of var 0..1: gray;
constraint gray[1,1,1]=0 /\ gray[1,2,1]=1;
constraint forall(i in 1..n-1)(
  forall(j in 1..pow(2,i))(
    forall(t in 1..i)(
      gray[i+1,j,t+1]=gray[i,j,t]
    ) /\ gray[i+1,j,1]=0
  )
  /\ forall(j in 1..pow(2,i))(
    forall(t in 1..i)(
      gray[i+1,pow(2,i+1)-j+1,t+1]=gray[i,j,t]
    ) /\ gray[i+1,pow(2,i+1)-j+1,1]=1
  )
);
solve satisfy;
output["\(gray[n,k+1,i])" | i in 1..n];

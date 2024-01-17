#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct{
    int gia;
    char khach[10],sp[10],shop[10],gio[20];
}don;
int cmp(const void *a,const void *b){
      don *k=(don*)a;  
      don *h=(don*)b;
      return strcmp(k->gio,h->gio);  
}
int cmp1(const void *a,const void *b){
     don *k=(don*)a;
     don *h=(don*)b;
     if(strcmp(k->shop,h->shop)!=0){
        return strcmp(k->shop,h->shop);
     }else return strcmp(k->khach,h->khach);
}
int bnsreach(don *a,int n,char *x){//tim phan tu dau theo shop
    int l=0;
    int r=n-1;
    int tmp=-1;
   while(l<=r){
    int m=(l+r)/2;
    if(strcmp(x,a[m].shop)==0){
         tmp=m;
         r=m-1;
    }else if(strcmp(x,a[m].shop)>0){
        l=m+1;
    }else r=m-1;
   }
   return tmp;
}
int bnsreach1(don *a,int n,char *x){//tim pt cuoi theo shop
    int l=0;
    int r=n-1;
    int tmp=-1;
   while(l<=r){
    int m=(l+r)/2;
    if(strcmp(x,a[m].shop)==0){
         tmp=m;
         l=m+1;
    }else if(strcmp(x,a[m].shop)>0){
        l=m+1;
    }else r=m-1;
   }
   return tmp;
}
int bnsreach2(don *a,int n,char *x){ //tim pt dau theo khach
    int l=0;
    int r=n-1;
    int tmp=-1;
   while(l<=r){
    int m=(l+r)/2;
    if(strcmp(x,a[m].khach)==0){
         tmp=m;
         r=m-1;
    }else if(strcmp(x,a[m].khach)>0){
        l=m+1;
    }else r=m-1;
   }
   return tmp;
}
int bnsreach3(don *a,int n,char *x){ //tim pt dau theo gio
    int l=0;
    int r=n-1;
    int tmp=-1;
   while(l<=r){
    int m=(l+r)/2;
    if(strcmp(x,a[m].gio)<=0){
         tmp=m;
         r=m-1;
    }else if(strcmp(x,a[m].gio)>0){
        l=m+1;
    }
   }
   return tmp;
}
don a[1000000] ,b[1000000], c[1000000];
int main(){
char str0[20];
char str[20];
int n=0,sum=0;
while(scanf("%s",a[n].khach)&&strcmp(a[n].khach,"#")!=0){
    scanf("%s %d %s %s",a[n].sp,&(a[n].gia),a[n].shop,a[n].gio);
    sum+=a[n].gia;
    n++;
}
for(int i=0;i<n;i++){
    b[i]=a[i];
}
qsort(a,n,sizeof(don),cmp);
// for(int i=0;i<n;i++){
// printf("%s %s %d %s %s\n",a[i].khach,a[i].sp,a[i].gia,a[i].shop,a[i].gio);
// }
// }
qsort(b,n,sizeof(don),cmp1);
while(scanf("%s",str)&&strcmp(str,"#")!=0){
    if(strcmp(str,"?total_number_orders")==0){
        printf("%d\n",n);
    }
    if(strcmp(str,"?total_revenue")==0){
        printf("%d\n",sum);
    }    
    if(strcmp(str,"?revenue_of_shop")==0){
        int q=0;
        scanf("%s",str);
        int tmp=bnsreach(b,n,str);
        
        for(int j=tmp;j<n;j++){
            if(strcmp(b[j].shop,str)==0){
                   q+=b[j].gia;
            }else break;
        }
        printf("%d\n",q);
    }
    if(strcmp(str,"?total_consume_of_customer_shop")==0){
        int t=0;
        int j=0;
          scanf("%s %s",str0,str);
          int l=bnsreach(b,n,str);
          int r=bnsreach1(b,n,str);
          for(int i=l;i<=r;i++){
            c[j]=b[i];
           // printf("%s %s %d %s %s\n",c[j].khach,c[j].sp,c[j].gia,c[j].shop,c[j].gio);
            j++;
          }
          int target=bnsreach2(c,r-l+1,str0);
          for(int i=target;i<r-l+1;i++){
            if(strcmp(c[i].khach,str0)==0){
                    t+=c[i].gia;
            } else break;
          }
          printf("%d\n",t);
          
    }
    if(strcmp(str,"?total_revenue_in_period")==0){
        int p=0;
          scanf("%s %s",str0,str);
          int l=bnsreach3(a,n,str0);
          for(int i=l;i<n;i++){
            if(strcmp(a[i].gio,str)<=0){
                p+=a[i].gia;
              }else break;
            } 
          printf("%d\n",p);
        }
    }
    return 0;
}
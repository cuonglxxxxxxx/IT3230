#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
    char ma[10];
    int sl;
    char phong[10];
    char ks[5];
    char day[15];
    int chilr;
}order;
struct bntree{
    order *key;
  struct bntree *left;
  struct bntree *right;
};typedef struct bntree bntree;
order *makekey(char *ma,int sl,char *phong,char *ks,char *day,int chilr){
       order *new=(order*)malloc(sizeof(order));
       strcpy(new->ma,ma);
       strcpy(new->phong,phong);
       strcpy(new->ks,ks);
       strcpy(new->day,day);
       new->sl=sl;
       new->chilr=chilr;
       return new;
}
bntree *maketree(order *a){
    bntree *new=(bntree*)malloc(sizeof(bntree));
    new->key=makekey(a->ma,a->sl,a->phong,a->ks,a->day,a->chilr);
    new->left=new->right=NULL;
    return new;
}
order a[1000000];
bntree *insert(bntree *t,order *a){
     if(t==NULL){
       t=maketree(a);
     }else if(strcmp(a->ma,t->key->ma)>0){
        t->right=insert(t->right,a);
     }else if(strcmp(a->ma,t->key->ma)<0){
        t->left=insert(t->left,a);
     }
     return t;
}
bntree *search(bntree *t,char *ma){
       if(t==NULL){
        return NULL;
       }if(strcmp(ma,t->key->ma)==0){
        return t;
       }else if(strcmp(ma,t->key->ma)>0){
        return search(t->right,ma);
       }else return search(t->left,ma);
}
void laydulieu(order *b,int *n,char *ten){
  FILE *f;
  f=fopen(ten,"r");
  fscanf(f,"%d",n);
  for(int i=0;i<*n;i++){
    fscanf(f,"%s %d %s %s %s %d",b[i].ma,&b[i].sl,b[i].phong,b[i].ks,b[i].day,&b[i].chilr);
  }
}
void chuyendulieu(bntree *t,FILE *f){
    if(t!= NULL){
        fprintf(f,"%s %d %s %s %s %d\n",t->key->ma,t->key->sl,t->key->phong,t->key->ks,t->key->day,t->key->chilr);
    chuyendulieu(t->left,f);
    chuyendulieu(t->right,f);
    }
}
bntree *findmin(bntree *t){
    if(t==NULL){
        return NULL;
    }else if(t->left==NULL){
        return t;
    }else return findmin(t->left);
}
bntree *findmax(bntree *t){
    if(t==NULL){
        return NULL;
    }else if(t->right==NULL){
        return t;
    }else return findmax(t->right);
}
bntree *delete(bntree *t,char *x){
      bntree *tmp;
      if(t==NULL){
        return NULL;
      }else if(strcmp(t->key->ma,x)>0){
        t->left=delete(t->left,x);
      }else if(strcmp(t->key->ma,x)>0){
        t->right=delete(t->right,x);
        }else if(t->left&&t->right){
            tmp=findmin(t->right);
            t->key=tmp->key;
            t->right=delete(t->right,t->key->ma);
        }else {
            tmp=t;
           if(t->left==NULL){
                   t=t->right;
           }else if(t->right==NULL){
            t=t->left;
           }
           free(tmp);
        }
        return t;
}
int main(){
int n;
char lenh[2];
char str[10];
int sl,chilr;
char phong[10];
char ks[10];
char day[15];
bntree *t=NULL;
while(scanf("%s",lenh)&&strcmp(lenh,"#")!=0){
    if(strcmp(lenh,"1")==0){
        laydulieu(a,&n,"order.txt");
        printf("%d\n",n);
            for(int i=0;i<n;i++){
            t=insert(t,&a[i]);
        }
    }
    if(strcmp(lenh,"2")==0){
        int k=0;
        for(int i=0;i<n;i++){
            if((a[i].sl-2*a[i].chilr)<0){
                k++;
            }
        }for(int i=0;i<n;i++){
    printf("%s %d %s %s %s %d\n",a[i].ma,a[i].sl,a[i].phong,a[i].ks,a[i].day,a[i].chilr);
}
        printf("%d\n",k);
    }
    if(strcmp(lenh,"3")==0){
        scanf("%s",str);
        bntree *tmp=search(t,str);
        if(tmp!=NULL){
              printf("%s %d %s %s %s %d\n",tmp->key->ma,tmp->key->sl,tmp->key->phong,tmp->key->ks,tmp->key->day,tmp->key->chilr);
        }else printf("Not found\n");
    }
    if(strcmp(lenh,"4")==0){
        scanf("%s %d %s %s %s %d",str,&sl,phong,ks,day,&chilr);
        bntree *tmp=search(t,str);
        if(tmp==NULL){
            printf("Not found\n");
        }else 
        if(strcmp(tmp->key->ks,ks)!=0||strcmp(tmp->key->phong,phong)!=0||(sl-2*chilr)<0||(tmp->key->sl==sl&&tmp->key->chilr==chilr&&strcmp(tmp->key->day,day)==0)){
            printf("Invaild\n");
        }else{
        strcpy(tmp->key->day, day);
        tmp->key->sl = sl;
        tmp->key->chilr = chilr;
        // t=delete(t,str);
        // order *b=makekey(str,sl,phong,ks,day,chilr);
        // t=insert(t,b);
        printf("Update\n");
        bntree *tmpp=search(t,str);
        printf("%s %d %s %s %s %d\n",tmpp->key->ma,tmpp->key->sl,tmpp->key->phong,tmpp->key->ks,tmpp->key->day,tmpp->key->chilr);
        }
        
    }
    if(strcmp(lenh,"5")==0){
        scanf("%s",str);
        bntree *tmp=search(t,str);
        if(tmp==NULL){
            printf("Not found\n");
        }else t=delete(t,str);
        n--;
    }
    if(strcmp(lenh,"6")==0){
        scanf("%s %d %s %s %s %d",str,&sl,phong,ks,day,&chilr);
        t=insert(t,makekey(str,sl,phong,ks,day,chilr));
        bntree *tmp=search(t,str);
         printf("%s %d %s %s %s %d\n",tmp->key->ma,tmp->key->sl,tmp->key->phong,tmp->key->ks,tmp->key->day,tmp->key->chilr);
    }
    if(strcmp(lenh,"7")==0){
     FILE *f;
     f=fopen("order.txt","w");
     fprintf(f,"%d\n",n);
     chuyendulieu(t,f);
     fclose(f);
    }
}
}
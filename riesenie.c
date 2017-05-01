/* 
	author: Martin Kocun
	zadanie: 1.3.22
*/
#define _GNU_SOURCE
#define CHYBA -1
#define MIN_N 1
#define MIN_L 2
#define OK 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char A[]="abcdefghijklmnopqrstuvwxyz";

char *get_chain(char *letters)
{
	unsigned int l=strlen(letters);
	char* res=malloc((2*l+1)*sizeof(char));
	char c;

	if(l==0)
		res[0]=0;
	else 
		if(l==1) {
			c=letters[0];
			res[0]=c;
			res[1]=c;
			res[2]=0;	
		}
		else {
			c=letters[0];
			res[0]=c;
			res[2]=c;
			
			for(int i=0;i<l-2;i++) {
				c=letters[1+i];
				res[1+2*i]=c;
				res[1+2*i+3]=c;
			}
			
			c=letters[l-1];
			res[2*l-1]=c;
			res[2*l-3]=c;	 
			res[2*l]=0;
		}
	return res;
}

char *split_string(char *s, unsigned int n)
{
	char *res;


	res=malloc((n+1)*sizeof(char));
	strncpy(res,s,n);
	res[n]=0;
	return res;
}

char nahodne_prepletene_slovo(char *w, unsigned int l, unsigned int n)
{
	char *my_alphabet;
	char *shuffled_alphabet;
	char *chain_alphabet;
	char *chain;
	int max_unique_chain_letters;
	int unique_chain_letters;
	int chain_len;
	int random_num;
	int i;
	int j;
	int k;
	int num;

	if(n < MIN_N || l < MIN_L) {
		return CHYBA;
		
	} else {

		my_alphabet=split_string(A,n);
		shuffled_alphabet=strfry(strdup(my_alphabet));

		if(n==1) {
			for(int i=0;i<l;i++){
				w[i]=my_alphabet[0];
			}
			w[l]=0; 
		} else {
			max_unique_chain_letters=n<l/2 ? n : l/2;
			unique_chain_letters=rand()%max_unique_chain_letters+1;

			chain_alphabet=split_string(shuffled_alphabet,unique_chain_letters);
			chain=get_chain(chain_alphabet);
			free(chain_alphabet);
			
			chain_len=strlen(chain);
			random_num=l-chain_len;
			i=0;
			
			for(j=0;j<chain_len-2;j++){
				w[i]=chain[j];
				i++;	
				if(random_num>0){
					num=rand()%(random_num+1);
					for(k=0;k<num;k++){
						w[i]=my_alphabet[rand()%n];
						i++;
					}
					random_num-=num;	
				}
			}
			w[i]=chain[chain_len-2];
			i++;
			for(j=0;j<random_num;j++){
				w[i]=my_alphabet[rand()%n];
				i++;
			}
			w[l-1]=chain[chain_len-1];
			w[l]=0;

			free(chain);
		}

		free(my_alphabet);
		free(shuffled_alphabet);
	}

	return OK;
}


int main()
{
	int l,n;
	char *w;
	
	srand(time(NULL));
	l=rand()%20+2;
	n=rand()%strlen(A)+1;
	w=malloc((l+1)*sizeof(char));
	if(nahodne_prepletene_slovo(w,l,n)==OK){
		printf("l:%d, n:%d, w:%s\n",l,n,w);
	} else {
		printf("Nastala chyba");
	}
	free(w);


	return 0;
}

#include <unistd.h>
#include <stdarg.h>
#define limit 10000

typedef enum {false,true} bool;
typedef enum {plus=1,blank=2,zero=4,reverse=8} flag;
typedef struct{
	bool minus;
	bool bool_precision;
	flag flags;
	int width;
	int precision;
	char type_prefix;
	char type;
} my_format;
void mini_printf(const char* args,...);
void print_format_number(my_format format,long num);
void print_format_char(my_format format,char ch);
void print_format_string(my_format format,char* str);
void write_format(my_format format,char* str,int count);
int print_normal(const char* args);
int get_format(const char* args,my_format* format);
int my_strlen(const char* args);

void mini_printf(const char* args,...){
	int count=0;
	va_list argptr;
	va_start(argptr,args);

	while(*args!='\0'){
		if (*args=='%'){
			my_format format;
			count=get_format(args,&format);
			switch(format.type){
			case 'b':
			case 'd':
			case 'x':
			case 'X':
				print_format_number(format,va_arg(argptr,long));
				args+=count;break;
			case 'c':
				print_format_char(format,(va_arg(argptr,int)));
				args+=count;break;
			case 's':
				print_format_string(format,va_arg(argptr,char*));
				args+=count;break;
			case '%':
				write(1,"%",1);args+=count;break;
			default:
				write(1,"%",1);args++;break;
			}
		}else{
			args+=print_normal(args);	
		}
	}
	
	va_end(argptr);
}


void print_format_number(my_format format,long num){
	char str[limit]={0,};
	char temp;
	int count=0;
	int i,j;
	long div;
	bool upper=false;
	if (num<0){
		if (format.type=='d'){
			num=-num;
			format.minus=true;
		}else{
			num=0xffffffff+num+1;
		}
	
	}
	switch(format.type){
	case 'b':div=2;break;
	case 'd':div=10;break;
	case 'x':div=16;upper=false;break;
	case 'X':div=16;upper=true;break;
	}
	while(num){
		if (div==16){
			switch(num%div){
			case 10:str[count++]=upper?'A':'a';break;
			case 11:str[count++]=upper?'B':'b';break;
			case 12:str[count++]=upper?'C':'c';break;
			case 13:str[count++]=upper?'D':'d';break;
			case 14:str[count++]=upper?'E':'e';break;
			case 15:str[count++]=upper?'F':'f';break;
			default:str[count++]=num%div+'0';
			}

		}
		else{
			str[count++]=num%div+'0';
		}
		num/=div;
		
	}

	while(format.precision>count){
		str[count++]='0';
	}
	
	if (format.precision==0){
		if (format.flags&zero){
			while(format.width>count+(format.minus|(format.flags&plus))){
				str[count++]='0';
			}
		}
	}
	if (format.type=='d'){
		if (format.minus==true){
			str[count++]='-';
		}else if (format.flags&plus){
			str[count++]='+';
		}
	}
	for(i=0,j=count-1;i<count/2;i++,j--){
		temp=str[j];
		str[j]=str[i];
		str[i]=temp;
	}

	write_format(format,str,count);
}
void print_format_char(my_format format,char ch){
	char c[1];
	c[0]=ch;
	write_format(format,c,1);
}
void print_format_string(my_format format,char* str){
	int len,i;
	char tmp;
	len=my_strlen(str);
	char strs[len];
	for(i=0;i<len;i++){
		strs[i]=str[((format.flags&reverse)?len-1-i:i)];
	}
	write_format(format,strs,(format.bool_precision&&(format.precision<len)?format.precision:len));
}

int print_normal(const char* args){
	int i=1;
	while(*(args+i)!='\0' && *(args+i)!='%'){
		i++;
	}
	write(1,args,i);
	return i;
}

void write_format(my_format format,char* str,int count){
	int i;
	int blank_count=count;
	if (!(format.flags&blank)){
		while(format.width>blank_count){
			write(1," ",1);
			blank_count++;
		}
	}
	write(1,str,count);
	if (format.flags&blank){
		while(format.width>blank_count){
			write(1," ",1);
			blank_count++;
		}
	}
}

int get_format(const char* args,my_format* format){
	int i=1;
	int next=0;
	format->minus=false;
	format->bool_precision=false;
	format->flags=0;
	format->width=0;
	format->precision=0;
	format->type_prefix=0;
	format->type=0;
	while(*(args+i)!='\0'){
		switch(next){
			case 0:	
				switch(*(args+i)){
				case '+':format->flags|=plus;i++;break;
				case '-':format->flags|=blank;i++;break;
				case '0':format->flags|=zero;i++;break;
				case '~':format->flags|=reverse;i++;break;
				default:next++;
				}
				break;
			case 1:
				if (*(args+i)>='0' && *(args+i)<='9'){
					format->width=format->width*10+(*(args+i)-'0');
					i++;
				}
				else
					next++;
				break;
			case 2:
				if (*(args+i)=='.'){
					format->bool_precision=true;
					i++;
					next++;
				}
				else
					next+=2;
				break;
			case 3:
				if (*(args+i)>='0' && *(args+i)<='9'){
					format->precision=format->precision*10+(*(args+i)-'0');
					i++;
				}
				else
					next++;
				break;
			case 4:
				if (*(args+i)=='l' || *(args+i)=='h'){
					format->type_prefix=*(args+i);
					i++;
				}
				next++;
				break;
			case 5:
				format->type=*(args+i);
				next++;
				i++;
				return i;
		}	
			
	}
}

int my_strlen(const char* args){
	int n=0;
	while(*(args++)!=0){
		n++;
	}
	return n;
}

#include "MathCalculator.h"

string type_transform(string str)
{
	string::iterator i;
	for(i=str.begin();i!=str.end();i++)
		if(*i<'Z'&&*i>'A')
			*i=*i+32;
	return str;
}

string reform(string str)
{
	string::iterator i;
	str=type_transform(str);
	for(i=str.begin();i!=str.end();i++)
	{
		if(*i=='p'&& *(i+1)=='i')
		{
			*(i++)=18 ; *i=' ';
			continue;
		}
		if(*i=='e')
		{
			*i=19;
			continue;
		}
		if(i!=str.begin() && *(i-1)=='(' && *i=='-'||i==str.begin() && *i=='-')
		{
			*i=20;
			continue;
		}
		if(*i=='s'&& *(i+1)=='i'&& *(i+2)=='n')
		{
			*(i++)=21; *(i++)=' '; *i=' ';
			continue;
		}
		if(*i=='c'&&*(i+1)=='o'&&*(i+2)=='s')
		{
			*(i++)=22; *(i++)=' '; *i=' ';
			continue;
		}
		if(*i=='t'&&*(i+1)=='a'&&*(i+2)=='n')
		{
			*(i++)=23; *(i++)=' '; *i=' ';
			continue;
		}
		if(*i=='l' &&*(i+1)=='o' &&*(i+2)=='g')
		{
			*(i++)=24; *(i++)=' '; *i=' ';
			continue;
		}
		if(*i=='l' &&*(i+1)=='g')
		{
			*(i++)=24; *i=' ';
			continue;
		}
		if(*i=='l'&&*(i+1)=='n')
		{
			*(i++)=25; *i=' ';
			continue;
		}
	}
	return str;
}

string input(string& original)    //杈撳叆琛ㄨ揪寮忥紝鍌ㄥ瓨闈炵┖鐧藉瓧绗�
{
	string a_original;
	string result;
	string::iterator i;
	for(i=original.begin();i!=original.end();i++)
		if(*i!=' ' && *i!='\t')
			a_original.push_back(*i);
	a_original=reform(a_original);
	for(i=a_original.begin();i!=a_original.end();i++)
		if(*i!=' ')
			result.push_back(*i);
	return result;
}

double my_pow(double x,double y)
{
	if(x>0)
		return pow(x,y);
	if(x==0)
		return 0;
	if(y-(double)((int)y)<1e-18)
	{
		if(((int)y)%2==1)
			return (-pow(-x,y));
		else
			return pow(-x,y);
	}
	return pow(x,y);
}

void unary_oper(STACK& number,double optr)
{
	if(optr==(double)20)
		number.element[number.top]=-number.element[number.top];
	if(optr==(double)21)
		number.element[number.top]=sin(number.element[number.top]);
	if(optr==(double)22)
		number.element[number.top]=cos(number.element[number.top]);
	if(optr==(double)23)
		number.element[number.top]=tan(number.element[number.top]);
	if(optr==(double)24)
		number.element[number.top]=log10(number.element[number.top]);
	if(optr==(double)25)
		number.element[number.top]=log(number.element[number.top]);
}

void binary_oper(STACK& number,double optr)
{
	double x,y;
	x=number.pop();
	y=number.pop();
	if(optr==(double)'+')
		number.push(x+y);
	if(optr==(double)'-')
		number.push(y-x);
	if(optr==(double)'*')
		number.push(x*y);
	if(optr==(double)'/')
		number.push(y/x);
	if(optr==(double)'^')
		number.push(my_pow(y,x));
}

void oper(STACK& number,double optr)
{
	if(optr==(double)'+'||optr==(double)'-'||optr==(double)'*'||optr==(double)'/'||optr==(double)'^')
		binary_oper(number,optr);
	else
		unary_oper(number,optr);
}

int level(double optr)
{
	if(optr==(double)'+'||optr==(double)'-'||optr==(double)20)
		return 1;
	if(optr==(double)'*'||optr==(double)'/')
		return 2;
	if(optr==(double)'^')
		return 3;
	if(optr>=(double)21&&optr<=(double)25)
		return 4;
	else
		return 0;
}

double compute(string original)
{
	STACK S_number;
	STACK S_operator;
	string a_original;
	string::iterator i;
	double tmp_num=0,tmp;
	int state=0,point=0;
	try
	{
		a_original=input(original);
		for(i=a_original.begin();i!=a_original.end();i++)
		{
			if(*i>='0'&&*i<='9')
			{
				if(state==0&&point==0)
				{
					tmp_num=*i-'0';
					state=1;
				}
				else if(state==1&&point==0)
					tmp_num=tmp_num*10+*i-'0';
				else if(state==1&&point!=0)
				{
					tmp_num=tmp_num+(double)(*i-'0')/pow((double)10,(double)point);
					point++;
				}
			}
			else if(*i=='.')
				point=1;
			else
			{
				if(state==1)
				{
					S_number.push(tmp_num);
					tmp_num=0;
					state=0;
					point=0;
				}
				if(*i==18)
					S_number.push(pi);
				else if(*i==19)	
					S_number.push(e);
				else if(*i!='('&&*i!=')')
				{
					while(S_operator.top!=-1 && level(S_operator.element[S_operator.top])>=level(*i))
						oper(S_number,S_operator.pop());
					S_operator.push((double)(*i));
				}
				else if(*i=='(')
					S_operator.push((double)'(');
				else if(*i==')')
				{
					while(S_operator.element[S_operator.top]!=(double)'(')
						oper(S_number,S_operator.pop());
					S_operator.pop();
				}
			}
		}
	}catch(...){
		cout<<"error!"<<endl;
	}
	if(state==1)
		S_number.push(tmp_num);
	while(S_operator.top!=-1)
	oper(S_number,S_operator.pop());
	return S_number.pop();
}

double calculator(string original,char key,double point)
{
	string::iterator i,j;
	string tmp;
	stringstream t;
	t<<point;
	t>>tmp;
	tmp.insert(0,"(");
	tmp.insert(tmp.end(),')');
	for(i=original.begin();i!=original.end();)
	{
		if(*i==key)
		{
			j=i+1;
			original.replace(i,j,tmp);
			i=j;
		}
		else i++;
	}
	return compute(original);
}

double integration(string original, char key, double point1, double point2)
{
	double tmp_result=0;
	double tmp;
	double cur;
	for(cur=point1;cur+0.05<point2;cur=cur+0.05)
	{
		tmp=calculator(original,key,cur+0.025);
		tmp_result+=tmp*0.05;
	}
	tmp=calculator(original,key,(cur+point2)/2);
	tmp_result+=tmp*(point2-cur);
	return	tmp_result;
}

double derivative(string original, char key, double point)
{
	double tmp1;
	double tmp2;
	double result1;
	double result2;
	double dx=1e-3;
	tmp1=calculator(original,key,point+dx);
	tmp2=(original,key,point);
	result1=(tmp1-tmp2)/dx;
	dx=dx/2;
	tmp1=calculator(original,key,point+dx);
	tmp2=calculator(original,key,point);
	result2=(tmp1-tmp2)/dx;
	while(1)
	{
		if(result2-result1<0.001||result1-result2<0.001)
			break;
		result1=result2;
		dx=dx/2;
		tmp1=calculator(original,key,point+dx);
		tmp2=calculator(original,key,point);
		result2=(tmp1-tmp2)/dx;
	}
	return result2;
}

double limit(string original, char key, double point)
{
	double tmp1;
	double tmp2;
	double dx=1e-3;
	tmp1=calculator(original,key,point+dx);
	dx=dx/2;
	tmp2=calculator(original,key,point+dx);
	while(1)
	{
		if(tmp2-tmp1<0.001||tmp1-tmp2<0.001)
			break;
		tmp1=tmp2;
		dx=dx/2;
		tmp2=calculator(original,key,point+dx);
	}
	return tmp2;
}

double preload(string in, int integrate_state, int derivative_state, int limit_state, double point1, double point2, char key)
{
	if(integrate_state)
		return integration(in, key, point1, point2);
	if(derivative_state)
		return derivative(in, key, point1);
	if(limit_state)
		return limit(in, key, point1);
	return compute(in);
}

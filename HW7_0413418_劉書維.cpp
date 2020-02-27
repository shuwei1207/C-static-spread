#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	float ZeroRate[20];
	float free_ZeroRate[20];
	float Yield[20];
	float price;
	float free_yield[20];
	float C;
	float yield_spread;
	int n;
	
	printf("輸入債息:"); 
	scanf("%f",&C);
	printf("輸入yeild spread:"); 
	scanf("%f",&yield_spread);
	printf("輸入期數:"); 
	scanf("%d",&n);
	int i;
	
	for(i=0;i<n;i++)
	{	
		printf("輸入Yield Rate%d:",i+1);
		scanf("%f",&Yield[i]);
	}
	ZeroRate[0] = Yield[0]-yield_spread;
	
	//計算risk free價格
	for(i=0;i<n;i++)
	{
		free_yield[i]=Yield[i]-yield_spread;
	}
	for(i=1;i<n;i++)
	{	
		float BondValue = 0;
		int j;
		for(j=0;j<=i;j++)
		{	
			float Discount = 1;
			int k;
			for(k=0;k<=j;k++)
			{	
				Discount = Discount/(1+free_yield[i]);
			}
			BondValue = BondValue + Discount*C;
			if(j==i)
			{	
				BondValue = BondValue + Discount*100;
			}
		}
		printf("risk free bond price=%f\n",BondValue);
		for(j=0;j<i;j++)
		{	
			float PV = C;
			int k;
			for(k=0;k<=j;k++)
			{	
				PV = PV/(1+ZeroRate[j]);
			}
			BondValue = BondValue - PV;
		}
		ZeroRate[i] = pow((C+100)/BondValue,1.0/(i+1))-1;
	}
	
	for(i=0;i<n;i++)
	{	
		printf("第%d期的 risk free zero rate=%f\n",i+1,ZeroRate[i]);
		free_ZeroRate[i]=ZeroRate[i];	
	}
	ZeroRate[0] = Yield[0];
	
	for(i=1;i<n;i++)
	{	
		float BondValue = 0;
		int j;
		for(j=0;j<=i;j++)
		{	
			float Discount = 1;
			int k;
			for(k=0;k<=j;k++)
			{	
				Discount = Discount/(1+Yield[i]);
			}
			BondValue = BondValue + Discount*C;
			if(j==i)
			{	
				BondValue = BondValue + Discount*100;
			}
		}
		
		printf("price=%f\n",BondValue);
		price=BondValue;
		for(j=0;j<i;j++)
		{	
			float PV = C;
			int k;
			for(k=0;k<=j;k++)
			{	
				PV = PV/(1+ZeroRate[j]);
			}
			BondValue = BondValue - PV;
		}
		ZeroRate[i] = pow((C+100)/BondValue,1.0/(i+1))-1;
	}
	for(i=0;i<n;i++)
	{	
		printf("第%d期zero rate=%f\n",i+1,ZeroRate[i]);
	}
	//bisection mthod
		float Low = 0;
		float High= 1;
		while (High - Low >= 0.001)
		{
			float Middle =(Low + High) / 2;//欲找之IRR
			float Value = 0;
			for (i = 1; i <= n; i ++)
			{
				float Discount = 1;
				int j;
				for (j = 0; j <= i; j++)
				{
					Discount= Discount / (1+free_ZeroRate[j] + Middle);
				}
				Value = Value + Discount*C;
			}
			Value = Value - price;
			if (Value>0)
			{
				Low = Middle;
			}
			else
			{ 
				High = Middle;
 			}
		}
		printf("static spread=%f",High);	
	return 0;
}

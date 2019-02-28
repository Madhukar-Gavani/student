/*This code is for getting the number of students from user
and marks of two subjects of each students and display the 
result if mathematics marks is >70 and algorithm marks is 
>50.*/
#include <iostream>
using namespace std;

 int main()
 {
 	int matrix[10][2];     //this matrix is used for getting the number of students marks from user.
  int n,i,j;
      cout<<"Enter the numbers of students whose Mathematics and Algorithms marks to be tested"<<endl;
      cin>>n;
      if(n<1||n>10)
      {
      cout<<"bad input"<<endl;
      cout<<"Check the input again"<<endl;
      return 0;
      }
      cout<<"Enter the marks"<<endl;
      
      for(i=0;i<n;i++)
      {
      	for(j=0;j<2;j++)
      	{
      		cin>>matrix[i][j];    //input from user
      		if(matrix[i][j] < 1 ||matrix [i][j]>100)
      		{
      			cout<<"nope,Marks is in between 0 to 100"<<endl;
      			return 0;
      		}
      	}//cout<<matrix[i][j];
      }
      for(i=0;i<n;i++)
      {
      	for(j=0;j<2;j++)
      	{   
      		if(matrix[i][j] > 70)
      		{
      			if(matrix[i][j]>50)
      			{
      				cout<<"Pass"<<endl;
      				break;
      			}
      			else
      			{
      				cout<<"Fail"<<endl;
      				break;
      			}
      		}
      		else
      		{
      			cout<<"Fail"<<endl;
      		}
      		break;
      	}
      }
 }

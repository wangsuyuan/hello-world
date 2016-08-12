// aa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	//FILE *pin1=fopen("D:\\CT\\ToJapan\\PulmonaryTextureClassification\\PulmonaryTextureClassification\\b\\lbpidx.txt","r");
	//FILE *pin2=fopen("D:\\CT\\ToJapan\\PulmonaryTextureClassification\\PulmonaryTextureClassification\\b\\lbpdistance.txt","r");
	//FILE *pin1=fopen("D:\\CT\\ToJapan\\PulmonaryTextureClassification\\PulmonaryTextureClassification\\b\\lbpidx.txt","r");
	//FILE *pin2=fopen("D:\\CT\\ToJapan\\PulmonaryTextureClassification\\PulmonaryTextureClassification\\b\\lbpdistance.txt","r");
	FILE *pin1=fopen("Input\\Encodeshapeidxresult1.txt","r");
	FILE *pin2=fopen("Input\\Encodeshapedistanceresult1.txt","r");
	
	vector<int>idx;
	vector<float>distance;
	vector<vector<int> >idxAll;
	vector<vector<float> >distanceAll;
	int i,j;int it;float ft;
	//int a[]={856,856,856,856,856,856,856,856,856,856};
	int a[]={1024,1024,1024,1024,1024,1024,1024,1024,1024,1024,1024};
	//int a[]={842,842,842,842,842,842,842,842,842,842};
	for(j=0;j<10;j++)
	{
		for(i=0;i<a[j];i++)
		{
			fscanf(pin1,"%d",&it);
			fscanf(pin2,"%f",&ft);
			idx.push_back(it);
			distance.push_back(ft);

		}
		idxAll.push_back(idx);
		distanceAll.push_back(distance);
		idx.clear();
		distance.clear();
	}

	
	FILE *pGroundTruth=fopen("Input\\groundTruth.txt","r");
	bool *GroundTruth=new bool[10240];
	for(i=0;i<10240;i++)
	{
		GroundTruth[i]=false;
	}
	int number[]={0,41, 41+15, 56+35,  91+38, 129+25, 154+90, 244+150, 394+43, 437+165, 602+207};
	for(i=0;i<10;i++)
	{
		for(j=number[i]+1;j<=number[i+1];j++)
		{
			int temp;
			fscanf(pGroundTruth,"%d",&temp);
			GroundTruth[temp+i*1024]=true;
		}
	}

	float threshold=3;//0.5

/*
		for(i=0;i<10;i++)
		{
		
		 vector<int>::iterator IntIter=idxAll[i].end()-1;
		 vector<float>::iterator FloatIter=distanceAll[i].end()-1;
		 while(!idxAll[i].empty()&&*FloatIter>threshold)
		 {
			 idxAll[i].pop_back();
			 distanceAll[i].pop_back();
			 IntIter=idxAll[i].end()-1;
		     FloatIter=distanceAll[i].end()-1;
		 }
		}*/

	//for(int t=1;t<=3;t++)
	//{
	//	float *result=new float[10];
	//	float *result2=new float[10];
	//	for(i=0;i<10;i++)
	//	{
	//		result[i]=0;result2[i]=0;
	//		vector<int>::iterator IntIter=idxAll[i].begin()+1;
	//		int record=0;
	//		while(IntIter!=idxAll[i].end())
	//		{
	//			if(GroundTruth[i*1024+(*IntIter)])
	//			{	//cout<<*IntIter<<endl;
	//				result[i]++;result2[i]++;
	//			}
	//			IntIter++;record++;
	//			if(record==10*t)
	//			break;
	//		}
	//		result[i]/=record;//idxAll[i].size();
	//		result2[i]/=number[i+1]-number[i];
	//		cout<<record;
	//	}
	//	FILE *fout=fopen("Output//lbpPrecision.txt","a");
	//	FILE *fout2=fopen("Output//lbpRecall.txt","a");
	//	FILE *fout3=fopen("Output//lbpF1.txt","a");
	//	for(i=0;i<10;i++)
	//	{
	//		fprintf(fout,"%f\t",result[i]);
	//		fprintf(fout2,"%f\t",result2[i]);
	//		fprintf(fout3,"%f\t",(2*result[i]*result2[i])/(result[i]+result2[i]));
	//	}
	//	fprintf(fout,"\n");
	//	fclose(fout);
	//	fprintf(fout2,"\n");
	//	fclose(fout2);
	//	fprintf(fout3,"\n");
	//	fclose(fout3);
	//	delete []result;
	//	delete []result2;
	//}
	//for(threshold=8;threshold>=5;threshold-=0.5)
	//for(threshold=4;threshold>=1;threshold-=0.5)
	for(threshold=0.6;threshold>0.2;threshold-=0.05)
	//for(threshold=1.6;threshold>0.07;threshold-=0.1)
	//for(threshold=8;threshold>0.8;threshold-=0.5)
	{
		
		for(i=0;i<10;i++)
		{
		
		 vector<int>::iterator IntIter=idxAll[i].end()-1;
		 vector<float>::iterator FloatIter=distanceAll[i].end()-1;
		 while(!idxAll[i].empty()&&*FloatIter>threshold)
		 {
			 idxAll[i].pop_back();
			 distanceAll[i].pop_back();
			 if(idxAll[i].size()>0)
			 { 
				 IntIter=idxAll[i].end()-1;
				 FloatIter=distanceAll[i].end()-1;
			 }
		 }
		}
		float *result=new float[10];
		float *result2=new float[10];
		for(i=0;i<10;i++)
		{
			result[i]=0;
			result2[i]=0;
			vector<int>::iterator IntIter=idxAll[i].begin();
			while(IntIter!=idxAll[i].end())
			{
				if(GroundTruth[i*1024+(*IntIter)])
				{	//cout<<*IntIter<<endl;
					result[i]++;
					result2[i]++;
				}
				IntIter++;
			}
			result[i]/=idxAll[i].size();
			result2[i]/=number[i+1]-number[i];
		}
		FILE *fout=fopen("Output\\EncodeshapePrecision.txt","a");
		FILE *fout2=fopen("Output\\EncodeshapeRecall.txt","a");
		FILE *fout3=fopen("Output\\EncodeshapeF1.txt","a");
		for(i=0;i<10;i++)
		{
			fprintf(fout,"%f\t",result[i]);
			fprintf(fout2,"%f\t",result2[i]);
			fprintf(fout3,"%f\t",(2*result[i]*result2[i])/(result[i]+result2[i]));
		}
		fprintf(fout,"\n");
		fclose(fout);
		fprintf(fout2,"\n");
		fclose(fout2);
		fprintf(fout3,"\n");
		fclose(fout3);
		delete []result;
		delete []result2;
	}

	delete []GroundTruth;


	

	/*FILE *pout1=fopen("idx.txt","w");
	FILE *pout2=fopen("distance.txt","w");
	FILE *pout3=fopen("number.txt","w");
	int sum=0;
	for(i=0;i<10;i++)
	{
		sum+=idxAll[i].size();
		  for(j=0;j<idxAll[i].size();j++)
		 {
			 fprintf(pout1,"%d\t",idxAll[i][j]);
			 fprintf(pout2,"%f\t",distanceAll[i][j]);
		 }
		 fprintf(pout1,"...\n");
		 fprintf(pout2,"\n");
		 fprintf(pout3,"%d\t",sum);
	 
	}
	fclose(pout1);
	fclose(pout2);
	fclose(pout3);*/
	return 0;
}



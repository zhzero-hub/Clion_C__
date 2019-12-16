//
// Created by haoha on 2019/11/30.
//

#include "PCA_Demension.h"
PCA_Demension::PCA_Demension(void){}
PCA_Demension::~PCA_Demension(void){}
/*函数名称：covariance函数功能：
 * 协方差求取输入：
 * vector<double> x ---- 输入参量x
 * double x_mean --- x的均值
 * vector<double> y ---- 输入参量y
 * double y_mean ---- y的均值输出：
 * double result --- 两列向量的协方差*/
int PCA_Demension::covariance(vector<double> x, double x_mean, vector<double> y, double y_mean, double & result)
{
    double sum_temp = 0;
    for(size_t i = 0 ; i < x.size(); ++i)
    {
        sum_temp = sum_temp + (x[i]-x_mean)*(y[i]-y_mean);
    }
    result = sum_temp/(x.size() - 1);
    return 1;
}
    /*函数名称：PCA_demension
     * 函数功能：PCA降维输入：vector<vector<double> > Feature_Data ---- 需要降维的数据，每一行是一个样本，每一列代表一个特征
     * int k --- 降到K维输出：vector<vector<double> > PCA_Features---中间变换特征矩阵
     * vector<vector<double> >  Final_Data -----最终降维处理得到的答案返回值: 1 --- 计算正确 ；0 --- 计算错误*/
nt PCA_Demension::PCA_demension(vector<vector<double> > Feature_Data, int k, vector<vector<double> > & PCA_Features,vector<vector<double> > & Final_Data){
        //对每一列的数据求取平均值
        vector<double> Mean_values(Feature_Data[0].size(),0);//初始化
        for(size_t j = 0;j < Feature_Data[0].size(); ++j)
        {
            double sum_temp = 0;
            for(size_t i = 0;i < Feature_Data.size(); ++i)
            {
                sum_temp = sum_temp + Feature_Data[i][j];
            }
            Mean_values[j] = sum_temp/Feature_Data.size();
        }
        //对于所有样例都减去对应的平均值,去均值处理
        for(size_t j = 0;j<Feature_Data[0].size(); ++j)
        {
            for(size_t i = 0;i<Feature_Data.size(); ++i)
            {
                Feature_Data[i][j] = Feature_Data[i][j] - Mean_values[j];
            }
        }
        //求取特征协方差矩阵
        // 在这之前，首先进行转置
        // 实现转置功能
        vector<vector<double> > trans;
        for(size_t i=0;i<Feature_Data[0].size();i++)
        {
            vector<double> temp;
            for(size_t j=0;j<Feature_Data.size();j++)
            {
                temp.push_back(Feature_Data[j][i]);
            }
            trans.push_back(temp);
            temp.clear();
        }
        //实现求取协方差矩阵
        vector<vector<double> > covariance_Matrix;
        for(size_t i = 0;i<Feature_Data[0].size();++i)
        {
            vector<double> temp;
            for(size_t j = 0;j<Feature_Data[0].size();++j)
            {
                double result = 0;
                covariance(trans[i],Mean_values[i],trans[j],Mean_values[j],result);
                temp.push_back(result);
            }
            covariance_Matrix.push_back(temp);
            temp.clear();
        }
        //求协方差矩阵的特征值和特征向量
        vector<vector<double> > pca_result;
        double dbEps = 0.001;
        int nJt = 1000;
        JacbiCor(covariance_Matrix,k,dbEps,nJt,pca_result);
        MatrixXd covariance_Matrix_temp(covariance_Matrix.size(),covariance_Matrix.size());
        for(size_t i = 0 ; i< covariance_Matrix.size(); ++i)
        {
            for(size_t j = 0 ; j< covariance_Matrix.size(); ++j)
            {
                covariance_Matrix_temp(i,j) = covariance_Matrix[i][j];
            }
        }
        EigenSolver<MatrixXd> es(covariance_Matrix_temp);
        MatrixXd V = es.pseudoEigenvectors();
        cout<<"特征向量V ： "<< endl<< V<<endl;
        MatrixXd D = es.pseudoEigenvalueMatrix();
        cout<<"特征值矩阵D："<<endl<<D<<endl;
        //进行排序
        std::map<double,int> mapEigen;
        int D_row = D.rows();
        int V_row = V.rows();
        double * pdbEigenValues = new double[D_row];
        double * pdbVecs = new double[(D_row)*(D_row)];
        for(size_t i =0; i < V_row; ++i)
        {
            for(size_t j =0; j < V_row; ++j)		{			pdbVecs[i*(V_row)+j] = V(j,i);		}	}	double *pdbTmpVec = new double[(D_row)*(D_row)];	for(size_t i = 0;i< D_row; ++i)	{		pdbEigenValues[i] = D(i,i);		mapEigen.insert(make_pair(pdbEigenValues[i],i));	} 	std::map<double,int>::reverse_iterator iter = mapEigen.rbegin();	for (int j = 0; iter != mapEigen.rend(),j < D_row; ++iter,++j)	{		for (int i = 0; i < D_row; i ++)		{			pdbTmpVec[j*D_row+i] = pdbVecs[i+ (iter->second)*D_row];		} 		//特征值重新排列		pdbEigenValues[j] = iter->first;	} 	memcpy(pdbVecs,pdbTmpVec,sizeof(double)*(D_row)*(D_row));	delete[] pdbTmpVec; 	//选择k个特征向量	for(size_t i = 0 ;i< k ;++i)	{		vector<double> temp;		for(size_t j = 0; j< D_row; ++j)		{			temp.push_back(pdbVecs[i*D_row+j]);//一行是一个向量		}		PCA_Features.push_back(temp);		temp.clear();	} 	delete[] pdbEigenValues;	delete[] pdbVecs;  	//还有矩阵乘法	//先对PCA_Features进行转置，看看情况	vector<vector<double> > trans_fature;	for(size_t i=0;i<PCA_Features[0].size();i++)	{		vector<double> temp;		for(size_t j=0;j<PCA_Features.size();j++)		{			temp.push_back(PCA_Features[j][i]);		}		trans_fature.push_back(temp);		temp.clear();	}	vector<vector<double> > Final_Data;	for(size_t i = 0;i<Feature_Data.size();++i)	{		vector<double> temp_v;		for(size_t k = 0; k < trans_fature[0].size(); ++k)		{			double temp_m = 0;			for(size_t j = 0;j<Feature_Data[0].size(); ++j)			{				temp_m = temp_m + Feature_Data[i][j]*trans_fature[j][k];			}			temp_v.push_back(temp_m);		}		Final_Data.push_back(temp_v);		temp_v.clear();	} 	return 1;}

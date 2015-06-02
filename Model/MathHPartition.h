#ifndef MATHHPARTITION_H_
#define MATHHPARTITION_H_
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "iostream"
#include "MathNormalize.h"
#include <vector>
#include "Windows.h"
using namespace std;

vector<IplImage*> hPartition(IplImage *img)
{
    //IplImage* img = cvLoadImage("doit.jpg",-1);
    int cal[1000];
    int n=img->height;
    int m=img->width;
    CvScalar s;
    vector<IplImage*> ans;
    bool pd;
    bool flag=0;
    //char ss[10]="test0.jpg";
    int mark;
    int i,j,sum,least,last;
    //cout<<n<< " wqweqwe "<<m<<endl;
    for ( i=0;i<n;i++)
        for ( j=0;j<m;j++)
        {
  //          cout<<i<<" "<<j<<endl;
            s =  cvGet2D(img,i,j);
            sum = (s.val[0]+s.val[1]+s.val[2])/img->nChannels;
            if (sum > 200)
            {
                s.val[0]=s.val[1]=s.val[2]=255;
                cvSet2D(img,i,j,s);
            }
            else
            {
                s.val[0]=s.val[1]=s.val[2]=0;
                cvSet2D(img,i,j,s);
            }
        } //
    //cvNamedWindow("original");
    //cvShowImage("original",img);
    for (i=0;i<n;i++)
    {
        least=0;
        s=cvGet2D(img,i,least);
        pd=false;
        while (s.val[0]==255||i==n-1) {

                                least++;
                                if (least>=m)
                                {
                                    if (flag==1)
                                {
                                    /*截图 抠图*/
                                    CvSize size= cvSize(m,i-mark+1);//区域大小
                                    cvSetImageROI(img,cvRect(0,mark,size.width, size.height));//设置源图像ROI
                                    IplImage* pDest = cvCreateImage(size,img->depth,img->nChannels);//创建目标图像
                                    //cout << "!!!" << (int)pDest << endl;
                                    cvCopy(img,pDest); //复制图像
                                   // cout<<"success!"<<endl;

                                   // cout<<"success"<<endl;
                                    //pDest=normlize(pDest);
                                    ans.push_back(pDest);
                                    cvResetImageROI(img);//源图像用完后，清空ROI
                                    //cvNamedWindow("before");
                                    //cvShowImage("before",pDest);
                                    //cvNamedWindow("hahaha");//保存目标图像
                                    //cvShowImage("hahaha",pDest);
                                    //cvSaveImage(ss,pDest);
                                    //cvReleaseImage(&pDest);
                                    //cout<<"get"<<endl;
                                    //cvWaitKey(0);
                                    //cvDestroyWindow("hahaha");
                                    //cvDestroyWindow("before");
                                    //cout<<j<<" "<<endl;
                                    flag=0;
                                  //  ss[4]+=1;
                                }
                                    cal[i]=0;
                                    //cout<<"0";
                                    pd=true;
                                    break;
                                }
                                s=cvGet2D(img,i,least);
                                }
        last=m-1;
        if (pd) continue;
        s=cvGet2D(img,i,last);
        while (s.val[0]==255) {last--; s=cvGet2D(img,i,last);}
        cal[i]=last-least;
        if (flag==0) {
                        flag=1;
                        mark=i;
                        }

        //cout<<cal[i]<<" ";
    }
    return ans;
}

#endif


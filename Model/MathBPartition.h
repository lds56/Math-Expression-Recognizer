/*
 * MathBPartition.h
 *
 *  Created on: 2014年7月13日
 *      Author: lds
 */

#ifndef MATHBPARTITION_H_
#define MATHBPARTITION_H_

#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "iostream"
//#include "MathNormalize.h"
#include <vector>
#include "Windows.h"
using namespace std;
using namespace cv;

/*
 * MathBPartition.h
 *
 *  Created on: 2014年7月13日
 *      Author: lds
 */
int tryx[8]={-1,-1,-1,0,0,1,1,1};
int tryy[8]={-1,0,1,-1,1,-1,0,1};
void dfs(IplImage* img,IplImage* pDest,int x,int y,int flag)
{
    CvScalar s;
    int i;

   //cout<<"dfs "<<endl;
    s=cvGet2D(img,x,y);
    if (flag==1) cvSet2D(pDest,x,y,s);
    s.val[0]=s.val[1]=s.val[2]=255;
    cvSet2D(img,x,y,s);
    for (i=0;i<8;i++)
    {
        if (x+tryx[i]<0 || x+tryx[i]>=img->height) continue;
        if (y+tryy[i]<0 || y+tryy[i]>=img->width) continue;
        s=cvGet2D(img,x+tryx[i],y+tryy[i]);
        if (s.val[0]==0) dfs(img,pDest,x+tryx[i],y+tryy[i],flag);
    }
}
void clearit(IplImage* img)
{
    CvScalar s;
    s.val[0]=s.val[1]=s.val[2]=255;
    for (int i=0;i<img->height;i++)
        for (int j=0;j<img->width;j++)
            cvSet2D(img,i,j,s);
}
vector<IplImage*> bPartition
(IplImage* img)
{
    //IplImage* img = cvLoadImage("doit.jpg",-1);
    int sum;
    int n=img->height;
    int m=img->width;
    vector<IplImage*> tol;
    tol.clear();
    CvScalar s;
    IplImage* pDest = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
    clearit(pDest);
    for (int  i=0;i<n;i++)
        for (int j=0;j<m;j++)
        {
            s =  cvGet2D(img,i,j);
            sum = (s.val[0]+s.val[1]+s.val[2])/(img->nChannels);
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
        }

	//namedWindow("dmage3", CV_WINDOW_AUTOSIZE);
	//cvShowImage("dmage3", img);
	//waitKey();
	//destroyWindow("dmage3");

    bool flag=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            {

        		//cout<<i<<" "<<j<<endl;
        		s=cvGet2D(img,i,j);
                if (s.val[0]==0)
                {
                                  //cout<<"?1?1"<<endl;

                	dfs(img,pDest,i,j,flag);
                    //pDest=normlize(pDest);
                    //cvNamedWindow("div");
                    //cvShowImage("div",pDest);
                    //cvWaitKey(0);
                    //cvDestroyWindow("div");
                    flag=1;
                }

            }

    for (int i=0;i<n;i++)
            for (int j=0;j<m;j++)
            {
            	//cout<<i<<" "<<j<<endl;
            	s=cvGet2D(pDest,i,j);
            	if (s.val[0]==0)
            		{
            	    tol.push_back(pDest);
            	    return tol;
            		}
            }
    return tol;
}

#endif /* MATHBPARTITION_H_ */

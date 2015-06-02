#ifndef NORMLIZE_H_INCLUDED
#define NORMLIZE_H_INCLUDED


#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include <iostream>
using namespace std;


int flag0=1;
int tola=0,tol=0;
void setpic(IplImage *p,int x,int y,int a)
{
     CvScalar s;
     if (a==0) tola++;
     tol++;
     s.val[0]=s.val[1]=s.val[2]=a;
     cvSet2D(p,x,y,s);
}
IplImage* normlize (IplImage* img)
{
    CvSize n;
    tola=0;
    tol=0;
    n.width=50;
    n.height=50;
  //  IplImage* img = cvLoadImage("doit.jpg",-1);
  //  IplImage* biimg = cvCreateImage(cvGetSize(img),img->depth,img->nChannels);
    IplImage* ans =cvCreateImage(n,img->depth,img->nChannels);
    CvScalar s;
    int sum=0;
    int MinHorizontal,MaxHorizontal,MinVertical,MaxVertical;
    //cout<<img->depth<<"!!!!"<<img->nChannels<<"!!"<< img->height<<" "<<img->width<<endl;
    MinHorizontal=999999999;
    MaxHorizontal=0;
    MinVertical=999999999;
    MaxVertical=0;
    short int map[500][500];
    for (int i=0;i<img->height;i++)
    {
        for (int j=0;j<img->width;j++)
        {
            s =  cvGet2D(img,i,j);
            //cout<<s.val[0]<<" "<<s.val[1]<<" "<<s.val[2]<<endl;
            sum = (s.val[0]+s.val[1]+s.val[2])/img->nChannels;
            if (sum > 128)
            {
                s.val[0]=s.val[1]=s.val[2]=255;
             //   cvSet2D(img,i,j,s);
             //   cout<<"0";
                map[i][j]=0;
            }
            else
            {
                if (j<MinVertical) MinVertical=j;
                if (j>MaxVertical) MaxVertical=j;
                if (i<MinHorizontal) MinHorizontal=i;
                if (i>MaxHorizontal) MaxHorizontal=i;
                s.val[0]=s.val[1]=s.val[2]=0;
            //    cvSet2D(img,i,j,s);
            //   cout<<"1";
                map[i][j]=1;
            }
        }
    //cout<<endl;
    }// two-value;
    //cout<<"-------------------------"<<endl;
   // cout<<MinHorizontal<<" "<<MaxHorizontal<<" "<<MinVertical<<" "<<MaxVertical<<endl;

    int Horizontal=MaxHorizontal-MinHorizontal;
    int Vertical=MaxVertical-MinVertical;
    //cout<<Horizontal<<" "<<Vertical<<endl;
    if (Horizontal>Vertical)

    {
        MaxVertical+=(Horizontal-Vertical)/2;
        MinVertical-=(Horizontal-Vertical)/2;
       // Vertical=Horizontal;
    }
        else
        {
            MaxHorizontal+=(Vertical-Horizontal)/2;
            MinHorizontal-=(Vertical-Horizontal)/2;
           // Horizontal=Vertical;
        }
   // cout<<"-------------------------"<<endl;
   // cout<<MinHorizontal<<" "<<MaxHorizontal<<" "<<MinVertical<<" "<<MaxVertical<<endl;
   // cout<<Horizontal<<" "<<Vertical<<endl;
    CvSize m;
    m.width=MaxVertical-MinVertical+1;
    m.height=MaxHorizontal-MinHorizontal+1;
    IplImage* tmp =cvCreateImage(m,img->depth,img->nChannels);
  //  cout<<cvGetSize(tmp).width<<" "<<cvGetSize(tmp).height<<endl;
    for (int i=MinHorizontal;i<=MaxHorizontal;i++)
    {
        //cout<<i<<":";
        for  (int j=MinVertical;j<=MaxVertical;j++)
             {
                if (i<0 || j<0|| i+1>=img->height || j+1>=img->width ) setpic(tmp,i-MinHorizontal,j-MinVertical,255);
                    else if (map[i][j]==0) setpic(tmp,i-MinHorizontal,j-MinVertical,255);
                        else setpic(tmp,i-MinHorizontal,j-MinVertical,0);
                //cout<<j<<" ";

             }
      //  cout<<endl;
    }
   // cout<<"!!!"<<1.0*tola/tol<<endl;
    if (1.0*tola/tol>=0.9) flag0=1;
    else                   flag0=0;
    if (flag0)
    {
    for (int i=0;i<50;i++)
        for (int j=0;j<50;j++)
            setpic(ans,i,j,255);
    for (int i=15;i<34;i++)
        for (int j=15;j<34;j++)
            setpic(ans,i,j,0);
    }
    else cvResize(tmp,ans,CV_INTER_AREA);
//-------------------------------------------------------------
 //   cvCopy(img,biimg);
   // cvSaveImage("combibi.JPG",ans);
  //  cvNamedWindow("imagebinary");
  //  cvShowImage("imagebinary",biimg);
    //cvNamedWindow("test");
    //cvShowImage("test",tmp);
   // cvNamedWindow("ans");
   // cvShowImage("ans",ans);
    //cvWaitKey(0);
   // cvDestroyWindow("imagebinary");
   // cvReleaseImage(&img);
    //cvReleaseImage(&biimg);
    //cvReleaseImage(&tmp);
   // cvReleaseImage(&ans);
    return ans;
}


#endif // NORMLIZE_H_INCLUDED

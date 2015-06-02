#ifndef MATHVPARTITION_H_
#define MATHVPARTITION_H_
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "iostream"
#include "MathNormalize.h"
#include <vector>
#include "Windows.h"
using namespace std;


using namespace std;
double getit(IplImage* img,int y,int x,int dy,int dx)
{
    int high=0;
    int low=100000;
    CvScalar s;
    int i,j;
    //cout<<x<<" "<<y<<" "<<dx<<" "<<dy<<endl;
    for ( i=x;i<x+dx;i++)
        for ( j=y;j<y+dy;j++)
        {
            //cout<<i<<" "<<j<<endl;
            s =  cvGet2D(img,i,j);
            if (s.val[0]==0)
                {
                if (i<low) low=i;
                if (i>high) high=i;
                }
        }
    //cout<<low<<" "<<high<<endl;
    return (low+high)/2;
}
vector<IplImage*> vPartition(IplImage *img)
{
    //IplImage* img = cvLoadImage("doit.jpg",-1);
    IplImage* cmp=cvLoadImage("cmp.jpg",-1);
    int cal[1000];
    int n=img->height;
    int m=img->width;
    //cout<<n<<" "<<m<<endl;
    CvScalar s;
    vector<IplImage*> ans;
    ans.clear();
    bool pd;
    bool flag=0;
    double average=0;
    int mark=0;
    int high=0;
    int low=100000;
    int i,j,sum,least,last;
    for ( i=0;i<n;i++)
        for ( j=0;j<m;j++)
        {
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
                if (i<low) low=i;
                if (i>high) high=i;
                cvSet2D(img,i,j,s);
            }
        } //
    average=(high+low)/2;
    //cout<<average<<endl;
    //cvNamedWindow("original");
   // cvShowImage("original",img);
    for (j=0;j<m;j++)
    {
        least=0;
        s=cvGet2D(img,least,j);
        pd=false;
        while (s.val[0]==255||j==m-1) {

                                least++;
                                if (least>=n)
                                {
                                    if (flag==1)
                                {
                                    CvSize size= cvSize(j-mark+1,n);//Ã¥Å’ÂºÃ¥Å¸Å¸Ã¥Â¤Â§Ã¥Â°Â
                                    if (getit(img,mark,0,j-mark+1,n)<average-(high-low)/7) ans.push_back(cmp);
                                    cvSetImageROI(img,cvRect(mark,0,size.width, size.height));//Ã¨Â®Â¾Ã§Â½Â®Ã¦ÂºÂÃ¥â€ºÂ¾Ã¥Æ’ÂROI
                                    IplImage* pDest = cvCreateImage(size,img->depth,img->nChannels);//Ã¥Ë†â€ºÃ¥Â»ÂºÃ§â€ºÂ®Ã¦Â â€¡Ã¥â€ºÂ¾Ã¥Æ’Â
                                    cvCopy(img,pDest);

                                    //cout<<"  !"<<endl;
                                    //cout << "!!" << (int)pDest << endl;
                                    //ans.push_back(pDest);//å¶æ•°ä½åŽŸå›¾
                                    //pDest=normlize(pDest);
                                    ans.push_back(pDest);//å¥‡æ•°ä½æ ‡å‡†åŒ–
                                    cvResetImageROI(img);//Ã¦ÂºÂÃ¥â€ºÂ¾Ã¥Æ’ÂÃ§â€Â¨Ã¥Â®Å’Ã¥ÂÅ½Ã¯Â¼Å’Ã¦Â¸â€¦Ã§Â©ÂºROI
                                    flag=0;
                                    //cout<<"  !"<<endl;
                                }
                                    cal[j]=0;
                                    pd=true;
                                    break;
                                }
                                s=cvGet2D(img,least,j);
                                }
        last=n-1;
        if (pd) continue;
        s=cvGet2D(img,last,j);
        while (s.val[0]==255) {last--; s=cvGet2D(img,last,j);}
        cal[j]=last-least;
        if (flag==0) {
                        flag=1;
                        mark=j;
                        }

        //cout<<cal[j]<<" ";
    }
    return ans;
}
#endif



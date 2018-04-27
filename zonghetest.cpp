#include <iostream>
#include <dmtx.h>
#include "zbar.h" 
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cv.h>  
#include <cxcore.h>  
#include <highgui.h>  

using namespace std;
using namespace cv;
using namespace zbar;

int main(int argc,char*argv[])      
{ 
	
	//����IplImageָ��  
  IplImage* pFrame = NULL;  
  
 //��ȡ����ͷ  
  CvCapture* pCapture = cvCreateCameraCapture(-1);
  cvSetCaptureProperty(pCapture , CV_CAP_PROP_FRAME_WIDTH , 1280);  
    cvSetCaptureProperty(pCapture , CV_CAP_PROP_FRAME_HEIGHT , 720);
   
  //��������  
  cvNamedWindow("��ǰ��Ƶ", 1);  
  //cvNamedWindow("��ȡ��ͼ��", 2); 
   cout<<"��ʾ��ǰ����ͷ�������Ƶ������ո����ȡ��ǰ��ʾͼ�񣬵��Esc������"<<endl;
  //��ʾ����  
  while(1)  
  {  
      pFrame=cvQueryFrame( pCapture );  
      if(!pFrame)break;  
      cvShowImage("��ǰ��Ƶ",pFrame);  
      char c=cvWaitKey(33);  

	  if(c==' ')
	  {
		 cvSaveImage("C:/Users/JunminLu/Desktop/zonghe/zonghe/zonghe/database/test2.jpg", pFrame, 0); 
		 cvShowImage("��ȡ��ͼ��", pFrame); 
	  }
      if(c==27)break;  
  }  
  //cvReleaseCapture(&pCapture);  
  //cvDestroyWindow("��ǰ��Ƶ"); 
  cvDestroyWindow("��ȡ��ͼ��"); 
	

    ImageScanner scanner;        
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);      
    //Mat image = imread("C:/Users/JunminLu/Desktop/zonghe/zonghe/zonghe/database/test.jpg");  
	//Mat image = imread("E:/����/QRcode/DPM Dataset Xin/12/12_0_ref_0.84.bmp");
	//Mat image = imread("C:/Users/JunminLu/Desktop/19/result2.bmp");
	//Mat image = imread("C:/Users/JunminLu/Desktop/19/compare/B.bmp");
	//Mat image = imread("C:/Users/JunminLu/Desktop/zonghe/zonghe/zonghe/database/8.jpg");
	Mat image = imread("C:/Users/JunminLu/Desktop/zonghe/zonghe/zonghe/database/test2.jpg");
	//Mat image = imread("E:/����/QRcode/middle result/test2.bmp");
      if(!image.data)  
        {  
           cout<<"��ȷ��ͼƬ"<<endl;  
           system("pause");  
           return 0;  
        }  
    Mat imageGray;        
    cvtColor(image,imageGray,CV_RGB2GRAY);        
    int width = imageGray.cols;        
    int height = imageGray.rows;        
    uchar *raw = (uchar *)imageGray.data;           
    Image imageZbar(width, height, "Y800", raw, width * height);          
    scanner.scan(imageZbar); //ɨ������      
    Image::SymbolIterator symbol = imageZbar.symbol_begin(); 	
    if(imageZbar.symbol_begin()==imageZbar.symbol_end())    
    {           
	    DmtxMessage *msg;
        DmtxRegion *reg;
        Mat src = image;
        if(!src.data)
		{
            cout<<"Load image failed!"<<endl;
            return 0;
        }
        DmtxImage *img;
        img = dmtxImageCreate(src.data, src.cols, src.rows, DmtxPack24bppRGB);
        DmtxDecode *dec = dmtxDecodeCreate(img, 1);
        reg = dmtxRegionFindNext(dec, NULL);
        if(reg != NULL) 
	    {
            msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
			 
            if(msg != NULL) 
			{
                cout<<"���ͣ�"<<endl<<"datamatrix format"<<endl<<"����:"<<endl<<msg->output<<endl;
                dmtxMessageDestroy(&msg);
            }
            dmtxRegionDestroy(&reg);
        }
		else
		{
			cout<<"Input image can not be recognized by Zbar and Libdmtx Methods !"<<endl;
		}
        dmtxDecodeDestroy(&dec);
        dmtxImageDestroy(&img);
		imshow("Source Image",image);
		waitKey();  
	    return 0;
    }    
    for(;symbol != imageZbar.symbol_end();++symbol)      
    {        
        cout<<"���ͣ�"<<endl<<symbol->get_type_name()<<endl<<endl;      
        cout<<"���ݣ�"<<endl<<symbol->get_data()<<endl<<endl;         
    }
	imshow("Source Image",image);
    waitKey();      
    imageZbar.set_data(NULL,0);  

	//cvReleaseCapture(&pCapture);  
    //cvDestroyWindow("��ǰ��Ƶ"); 
    return 0;   
	
}    


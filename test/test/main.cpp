//
//  main.cpp
//  test
//
//  Created by 徐亦燊 on 2020/2/28.
//  Copyright © 2020 徐亦燊. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

    cv::Mat binaryMat;
    cv::Mat labelMat;
    cv::Mat statsMat;
    cv::Mat centrMat;
    cv::Mat resultMat;
    cv::Mat srcMat = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.3.20/3.20first/1.png", 0);

    cv::threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);

    int nComp = cv::connectedComponentsWithStats(binaryMat,labelMat,statsMat,centrMat,8,CV_32S);

    for (int i = 0; i < nComp; i++)
    {

        cout << "connected Components NO. " << i << endl;
        cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
        cout << "width = " << statsMat.at<int>(i, 2)<< endl;
        cout << "height = " << statsMat.at<int>(i, 3) << endl;
        cout << endl;
    }


    cout << " number is " << nComp-1 << endl;


    for (int i = 1; i < nComp; i++)
    {
        Rect bndbox;
        bndbox.x=statsMat.at<int>(i,0);
        bndbox.y=statsMat.at<int>(i,1);
        bndbox.width=statsMat.at<int>(i,2);
        bndbox.height=statsMat.at<int>(i,3);
        rectangle(binaryMat,bndbox,CV_RGB(255,255,255),1,8,0);

    }


    imshow("binaryMat", binaryMat);
    imshow("frame", srcMat);
    waitKey(0);
    return 0;
}


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

    resultMat = cv::Mat::zeros(srcMat.size(), CV_8UC3);
    std::vector<cv::Vec3b> colors(nComp);

    colors[0] = cv::Vec3b(0, 0, 0);

    for (int n = 1; n < nComp; n++)
    {
        colors[n] = cv::Vec3b( 255,  255,  255);
    }
    for (int y = 0; y < srcMat.rows; y++)
    {
        for (int x = 0; x < srcMat.cols; x++)
        {
            int label = labelMat.at<int>(y, x);
            CV_Assert(0 <= label && label <= nComp);
            resultMat.at<cv::Vec3b>(y, x) = colors[label];
        }
    }

    for (int i = 1; i < nComp; i++)
    {
        char num[10];
        sprintf(num, "%d", i);

        Rect bndbox;
        bndbox.x=statsMat.at<int>(i,0);
        bndbox.y=statsMat.at<int>(i,1);
        bndbox.width=statsMat.at<int>(i,2);
        bndbox.height=statsMat.at<int>(i,3);
        rectangle(resultMat,bndbox,CV_RGB(255,255,255),1,8,0);

    }


    imshow("binaryMat", binaryMat);
    imshow("results", resultMat);
    imshow("frame", srcMat);
    waitKey(0);
    return 0;
}


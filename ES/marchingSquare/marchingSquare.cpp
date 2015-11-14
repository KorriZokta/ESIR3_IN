#include <iostream>

#include <stdlib.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
  
bool calcul(int iIm, int jIm, int tab[][3]){
  double poids=0;
  double cptPoids=0;
  double dist;
  for (int i = 0; i<3;i++){
    
    double X = (iIm-tab[i][0])*(iIm-tab[i][0]);
    double Y = (jIm-tab[i][1])*(jIm-tab[i][1]);
    dist = sqrt(X+Y);
    
    poids = tab[i][2]/dist;
    
    cptPoids=poids+cptPoids;
  }
  bool oui = false;
  if(cptPoids > 1.0){
      oui = true;
  }
  return oui;

}

int main ()
{
  
  int x=500;//rows
  int y=500;//collums

  int move = 0;
  
  namedWindow( "oui", WINDOW_AUTOSIZE );// Create a window for display.    
  while(1){
      move++;
      Mat img = Mat::zeros(x,y,CV_8U);//generate a pic filled with zeroes
  

  
  int tab[3][3];
  
  tab[0][0] = 223;
  tab[0][1] = 148+move;
  tab[0][2] = 50;
  
  tab[1][0] = 45+move;
  tab[1][1] = 430;
  tab[1][2] = 30;
  
  tab[2][0] = 450-move;
  tab[2][1] = 450-move;
  tab[2][2] = 20;
  /*img.data[img.channels()*(img.cols*(maParticuleX) + maParticuleY)] = 255;
  img.data[img.channels()*(img.cols*(maParticuleX+1) + maParticuleY)] = 255;
  img.data[img.channels()*(img.cols*(maParticuleX-1) + maParticuleY)] = 255;
  img.data[img.channels()*(img.cols*maParticuleX + maParticuleY-1)] = 255;
  img.data[img.channels()*(img.cols*maParticuleX + maParticuleY+1)] = 255;
  */
  
  
  //grid generator
  int size = 5;
  
  for (int i = 0; i<img.rows ; i=i+size){
    for (int j = 0; j<img.cols ; j=j+size){
      //img.data[img.channels()*(img.cols*i + j) + 0] = 128;
      //img.data[img.channels()*(img.cols*i + j) + 0] = 128;
     
      
      /*           a---b
       *           -----
       *           -----
       *           -----
       *           c---d
       * */
      int cpt=0;
      
      bool a = calcul(i,j,tab);
      if(a){
	cpt=cpt+1000;
      }else{
	cpt=cpt+2000;
      }
      bool b = calcul(i+size,j,tab);
      if(b){
	cpt=cpt+10;
      }else{
	cpt=cpt+20;
      }
      bool c = calcul(i,j+size,tab);
      if(c){
	cpt=cpt+100;
      }else{
	cpt=cpt+200;
      }
      bool d = calcul(i+size,j+size,tab);
      if(d){
	cpt=cpt+1;
      }else{
	cpt=cpt+2;
      }
      
      switch ( cpt )
      {
         case 1111:
	    for (int x = i; x<i+size;x++){
	      for (int y = j; y<j+size;y++){
		img.data[img.channels()*(img.cols*x + y) + 0] = 255;
	      }
	    }

	    
            break;
         case 1112:
	   for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)<(((size/2)+size-y))){
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		  
		}
	      }
	    }

            break;
         case 1121:
           for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)>(y+(size/2))){
		   
		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255; 
		}
	      }
	    }
 
            break;
         case 1122:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)<(size/2)){

		   img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		}
	      }
	    }

            break;
         case 1211:
	   for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((size/2)+x)>(y)){
		  
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		}
	      }
	    }
            
            break;
         case 1212:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((y<(size/2))){
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		  
		}
	      }
	    }

            break;
         case 1221:
	  
            
	    for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((x)>(((size/2)+size-y)))||(((size/2)-x)>(y))){
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		  
		}
	      }
	    }
            break;
         case 1222:
	   for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((size/2)-x)<(y)){

		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255; 
		}
	      }
	    }
	   
	    break;
         case 2111:
	    for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((size/2)-x)<(y)){
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		  
		}
	      }
	    }
          
            break;
         case 2112:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((x)>(y+(size/2)))||(((size/2)+x)<(y))){
		   img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		}
	      }
	    }
            	    
            break;
         case 2121:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((y<(size/2))){

		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}
	      }
	    }

            break;
         case 2122:
	   for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if(((size/2)+x)>(y)){
		  
		  
		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}
	      }
	    }
	    
            break;
         case 2211:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)<(size/2)){

		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}
	      }
	    }
            
            break;
         case 2212:
	  for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)>(y+(size/2))){
		   img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}else{
		}
	      }
	    }

            break;
         case 2221:
	   for (int x = 0; x<size;x++){
	      for (int y = 0; y<size;y++){
		if((x)<(((size/2)+size-y))){
		  
		}else{
		  img.data[img.channels()*(img.cols*(i+x) + (j+y)) + 0] = 255;
		}
	      }
	    }
           
            break;
         case 2222:

	   

            break;
         default:
            cout<<"smth wrong here";
      }  
	  
    }
  }
  

  
  imshow("oui",img);
  waitKey(10);
  }
  waitKey(0);
  return 0;

} 
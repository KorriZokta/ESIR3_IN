#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>
#include <visp/vpMatrix.h>
#include <visp/vpColVector.h>
#include <visp/vpHomogeneousMatrix.h>

using namespace std ;

vpColVector sceneToCamera(vpHomogeneousMatrix & a, vpColVector & b){
	return a*b;
}

int main()
{

	vpImage<unsigned char> Icamera(550,550,0);
	vpDisplayX d(Icamera) ;

	float aile = 0.5;

	vpHomogeneousMatrix cMs(0, 0, 1, 0, 0, 0);

	int nbPoints = 4;
	vpColVector sPoints[nbPoints];
	
	vpColVector sX1(4);
	sX1[0]=-aile;
	sX1[1]=aile;
	sX1[2]=0;
	sX1[3]=1;

	vpColVector sX2(4);
	sX2[0]=aile;
	sX2[1]=aile;
	sX2[2]=0;
	sX2[3]=1;

	vpColVector sX3(4);
	sX3[0]=aile;
	sX3[1]=-aile;
	sX3[2]=0;
	sX3[3]=1;

	vpColVector sX4(4);
	sX4[0]=-aile;
	sX4[1]=-aile;
	sX4[2]=0;
	sX4[3]=1;
	
	sPoints[0]=sX1;
	sPoints[1]=sX2;
	sPoints[2]=sX3;
	sPoints[3]=sX4;
	
	vpColVector cPoints[nbPoints];
	for (int i = 0; i <nbPoints;i++){
		cPoints[i]=sceneToCamera(cMs,sPoints[i]);
		cout<<cPoints[i]<<endl;
	}
	
	int px=500;
	int py=500;
	int u0=275;
	int v0=275;
  	vpDisplay::display(Icamera) ;

	for(int i = 0; i<nbPoints ;i++){

		vpDisplay::displayCross(Icamera,cPoints[i][0]*px+u0,cPoints[i][1]*py+v0,20,vpColor::red) ;
	}

  	vpDisplay::flush(Icamera) ;
  	vpDisplay::getClick(Icamera) ;

	return 0;
}


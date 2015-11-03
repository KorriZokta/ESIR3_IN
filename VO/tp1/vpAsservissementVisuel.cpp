#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>
#include <visp/vpMatrix.h>
#include <visp/vpColVector.h>
#include <visp/vpHomogeneousMatrix.h>

using namespace std;

vpColVector sceneToCamera(vpHomogeneousMatrix & a, vpColVector & b){
	return a*b;
}

int main()
{
	float aile = 0.5;
	
	/*Param Cam*/
	double px=500;
	double py=500;
	double u0=275;
	double v0=275;
	vpCameraParameters cam(px,py,u0,v0);
	vpMatrix k(3,3);
	k[0][0] = px;
	k[1][1] = py;
	k[0][2] = u0;
	k[1][2] = v0;
	k[2][2] = 1;
	//vpMatrix k = cam.get_K();
	
	/*Projection*/
	vpMatrix proj(3,4);
	proj[0][0]=1;
	proj[1][1]=1;
	proj[2][2]=1;
	
	
	
	/*Matrices Homogenes*/
	vpHomogeneousMatrix cMs(0.55,0.55,0, 0,0,0);
	vpHomogeneousMatrix obMs(0,0,1, 0,0,0);
	vpHomogeneousMatrix tMs(0,0,1, 0,0,0);
	vpHomogeneousMatrix obMc,obMt;
	obMc = obMs*cMs.inverse();
	obMt = obMs*tMs.inverse();
   
   /*Coord Scène(mètres)*/
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
	
	/*Coord Cam(mètres)*/
	vpColVector cPoints[nbPoints];
	for (int i = 0; i<nbPoints;i++){
		cPoints[i]=sceneToCamera(cMs,sPoints[i]);
	}
	
	/*Coord Obs(mètres)*/
	vpColVector obPoints[nbPoints];
	for (int i = 0; i<nbPoints;i++) {
	   obPoints[i]=sceneToCamera(obMs,sPoints[i]);
	}
	
	/*Coord Targ(mètres)*/
	vpColVector tPoints[nbPoints];
	for (int i = 0; i<nbPoints;i++) {
	   tPoints[i]=sceneToCamera(tMs,sPoints[i]);
	}
	
	/*Coord Cam+Obs+Targ proj(mètres)*/
	vpColVector cPointsProj[nbPoints];
	vpColVector obPointsProj[nbPoints];
	vpColVector tPointsProj[nbPoints];
	for(int i=0; i<nbPoints; i++) {
	   cPointsProj[i] = proj*cPoints[i];
	   obPointsProj[i] = proj*obPoints[i];
	   tPointsProj[i] = proj*tPoints[i];
	}
	
	/*Coord Cam+Obs+Targ proj(pixels)*/
	vpColVector cPointsPix[nbPoints];
	vpColVector obPointsPix[nbPoints];
	vpColVector tPointsPix[nbPoints];
	for(int i=0; i<nbPoints; i++) {
	   cPointsPix[i] = k*cPointsProj[i];
	   obPointsPix[i] = k*obPointsProj[i];
	   tPointsPix[i] = k*tPointsProj[i];
	}
	
	/*Init affichage*/
	vpImage<unsigned char> iCam(550,550,0);
	vpDisplayX displayCam;
	displayCam.init(iCam,0,0,"CamView");
	vpImage<unsigned char> iObs(550,550,0);
	vpDisplayX displayObs;
	displayObs.init(iObs,600,0,"ObsView");
 
  	/*Affichage Cam*/
  	vpDisplay::display(iCam);
	for(int i = 0; i<nbPoints ;i++){
		vpDisplay::displayCross(iCam,cPointsPix[i][0],cPointsPix[i][1],20,vpColor::red);
	}
	
	/*Affichage Obs*/
	vpDisplay::display(iObs);
	for(int i = 0; i<nbPoints; i++) {
	   vpDisplay::displayCross(iObs,obPointsPix[i][0],obPointsPix[i][1],20,vpColor::green);
	}
	vpDisplay::displayCamera(iObs,obMc,cam,0.5,vpColor::blue,0.5); 
	vpDisplay::displayCamera(iObs,obMt,cam,0.5,vpColor::red,0.5);

  	
  	
  	
  	vpDisplay::flush(iCam);
  	vpDisplay::flush(iObs);
  	vpDisplay::getClick(iObs);

	return 0;
}
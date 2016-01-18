#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>
#include <visp/vpMatrix.h>
#include <visp/vpColVector.h>
#include <visp/vpHomogeneousMatrix.h>
#include <visp/vpExponentialMap.h>

using namespace std;

vpColVector sceneToCamera(vpHomogeneousMatrix & a, vpColVector & b){
	return a*b;
}

vpColVector calculErreur (vpColVector & s, vpColVector & sEtoile){
	vpColVector e(8);
	e[0]=s[0]-sEtoile[0];
	e[1]=s[1]-sEtoile[1];
	e[2]=s[2]-sEtoile[2];
	e[3]=s[3]-sEtoile[3];
	e[4]=s[4]-sEtoile[4];
	e[5]=s[5]-sEtoile[5];
	e[6]=s[6]-sEtoile[6];
	e[7]=s[7]-sEtoile[7];
	return e;
}

vpMatrix calculDeL(vpColVector* cPoints, int nbPoints){
	vpMatrix L(nbPoints*2,6);
	for (int i = 0;i<nbPoints;i++){
		double x = cPoints[i][0];
		double y = cPoints[i][1];
		double Z = cPoints[i][2];
		L[2*i][0]=-1/Z;
		L[2*i][1]=0;
		L[2*i][2]=x/Z;
		L[2*i][3]=x*y;
		L[2*i][4]=-(1+(x*x));
		L[2*i][5]=y;
		L[2*i+1][0]=0;
		L[2*i+1][1]=-1/Z;
		L[2*i+1][2]=y/Z;
		L[2*i+1][3]=1+(y*y);
		L[2*i+1][4]=-x*y;
		L[2*i+1][5]=-x;
	}
	return L;
}

vpColVector calculDeS(vpColVector * cPoints, int nbPoints){
	vpColVector s(8);
	for (int i = 0; i < nbPoints;i++){
		double x = cPoints[i][0];
		double y = cPoints[i][1];
		double z = cPoints[i][2];
		s[2*i] = x/z;
		s[2*i+1] = y/z;
	}
	return s;
}

vpColVector calculVitesse(vpColVector & s, vpColVector & sEtoile, vpColVector* cPoints, int nbPoints) {
	vpColVector vect = calculErreur(s,sEtoile);
	vpMatrix L = calculDeL(cPoints,nbPoints);
	L = L.pseudoInverse();
	vpColVector v = -L*vect;
	return v;
}

int main()
{
	float l = 0.2;
	int dim = 3;
	
	/*Param Cam*/
	double px=500;
	double py=500;
	double u0=300;
	double v0=300;
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
	vpHomogeneousMatrix cMs(0,0,1, 0,0,vpMath::rad(90));
	vpHomogeneousMatrix obMs(0,0,2, 0,0,0);
	vpHomogeneousMatrix tMs(0,0,1, 0,0,0);
	vpHomogeneousMatrix obMc,obMt,tMc;
	obMc = obMs*cMs.inverse();
	obMt = obMs*tMs.inverse();	
   
   /*Coord Scène(mètres)*/
	int nbPoints = 4;
	vpColVector sPoints[nbPoints];
	
	vpColVector sX1(4);
	sX1[0]=-l;
	sX1[1]=l;
	sX1[2]=0;
	sX1[3]=1;
	
	vpColVector sX2(4);
	sX2[0]=l;
	sX2[1]=l;
	sX2[2]=0;
	sX2[3]=1;

	vpColVector sX3(4);
	sX3[0]=l;
	sX3[1]=-l;
	sX3[2]=0;
	sX3[3]=1;

	vpColVector sX4(4);
	sX4[0]=-l;
	sX4[1]=-l;
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
	vpImage<unsigned char> iCam(600,600,0);
	vpDisplayX displayCam;
	displayCam.init(iCam,0,0,"CamView");
	vpImage<unsigned char> iObs(600,600,0);
	vpDisplayX displayObs;
	displayObs.init(iObs,700,0,"ObsView");
 
  	/*Affichage Cam*/
  	vpDisplay::display(iCam);
	for(int i = 0; i<nbPoints ;i++){
		vpDisplay::displayCross(iCam,cPointsPix[i][0],cPointsPix[i][1],20,vpColor::red);
	}
	
	/*Affichage Obs*/
	vpDisplay::display(iObs);
	for(int i = 0; i<nbPoints; i++) {
	   vpDisplay::displayCross(iObs,obPointsPix[i][0],obPointsPix[i][1],20,vpColor::yellow);
	}
	vpDisplay::displayCamera(iObs,obMc,cam,0.5,vpColor::blue,0.5); 
	vpDisplay::displayCamera(iObs,obMt,cam,0.5,vpColor::yellow,0.5);
   
   vpDisplay::flush(iCam);
  	vpDisplay::flush(iObs);
  	vpDisplay::getClick(iObs);
    if(dim==2) {
   /*Asservissement 2D*/
   vpColVector sEtoile = calculDeS(tPoints, nbPoints);
	vpColVector s = calculDeS(cPoints, nbPoints);
	while ((s-sEtoile).euclideanNorm()>0.001){
		s = calculDeS(cPoints, nbPoints);
		vpColVector v = calculVitesse(s, sEtoile, cPoints, nbPoints);

		/*Modification de la position*/
		cMs = vpExponentialMap::direct(v,0.01).inverse()*cMs;
		obMc = obMs*cMs.inverse();
		/*Calcul nouvelles positions (NP)*/
		for (int i = 0; i<nbPoints;i++){
				cPoints[i]=sceneToCamera(cMs,sPoints[i]);
		}
		/*Projection NP*/
		for(int i=0; i<nbPoints; i++) {
	      cPointsProj[i] = proj*cPoints[i];
	   }
	   /*Pixels NP*/
	   for(int i=0; i<nbPoints; i++) {
	      cPointsPix[i] = k*cPointsProj[i];
	   }
	   /*Affichage Cam*/
  	   vpDisplay::display(iCam);
	   for(int i = 0; i<nbPoints ;i++){
	   	vpDisplay::displayCross(iCam,cPointsPix[i][0],cPointsPix[i][1],20,vpColor::red);
	}
		/*Affichage Obs*/
	vpDisplay::display(iObs);
	for(int i = 0; i<nbPoints; i++) {
	   vpDisplay::displayCross(iObs,obPointsPix[i][0],obPointsPix[i][1],20,vpColor::yellow);
	}
	vpDisplay::displayCamera(iObs,obMc,cam,0.5,vpColor::blue,0.5); 
	vpDisplay::displayCamera(iObs,obMt,cam,0.5,vpColor::yellow,0.5);
	  	
	  	
	  	vpDisplay::flush(iCam);
	  	vpDisplay::flush(iObs);
	}
	}
	
	if(dim==3) {
	   vpTranslationVector ttc;
	   vpRotationMatrix tRc;
	   vpThetaUVector thetaU;
	   double theta;
   	vpColVector u;
   	vpMatrix ux;
   	vpMatrix identity;
   	identity.eye(3);
   	tMc.extract(ttc);
   	tMc.extract(thetaU);
   	
   	while(1) {
   	   tMc = tMc*cMs.inverse();
      	tMc.extract(ttc);
      	tMc.extract(tRc);
      	tMc.extract(thetaU);
      	thetaU.extract(theta,u); 
      	ux = vpColVector::skew(u);
      	double sincardTheta = vpMath::sinc(theta);
      	double sincardThetaDemi = vpMath::sinc(theta/2.0);
   	
      	vpMatrix lOmega = identity+(theta/2.0)*ux+(1-sincardTheta/(sincardThetaDemi*sincardThetaDemi))*ux*ux.transpose();
      	vpMatrix matL(6,6);
      	matL.insert(tRc,0,0);
      	matL.insert(lOmega,3,3);
      	cout<<matL<<endl;
      	vpMatrix lPlus = matL.pseudoInverse();
      	vpColVector v;
      	vpMatrix e = tMs-cMs;
      	v = -lPlus*e;
      	
      	/*Modification de la position*/
		   cMs = vpExponentialMap::direct(v,0.01).inverse()*cMs;
		   obMc = obMs*cMs.inverse();
		   /*Calcul nouvelles positions (NP)*/
		   for (int i = 0; i<nbPoints;i++){
		   		cPoints[i]=sceneToCamera(cMs,sPoints[i]);
		   }
		   /*Projection NP*/
		   for(int i=0; i<nbPoints; i++) {
	         cPointsProj[i] = proj*cPoints[i];
	      }
	      /*Pixels NP*/
	      for(int i=0; i<nbPoints; i++) {
	         cPointsPix[i] = k*cPointsProj[i];
	      }
	      /*Affichage Cam*/
  	      vpDisplay::display(iCam);
	      for(int i = 0; i<nbPoints ;i++){
	      	vpDisplay::displayCross(iCam,cPointsPix[i][0],cPointsPix[i][1],20,vpColor::red);
	   }  
		   /*Affichage Obs*/
	      vpDisplay::display(iObs);
	      for(int i = 0; i<nbPoints; i++) {
	         vpDisplay::displayCross(iObs,obPointsPix[i][0],obPointsPix[i][1],20,vpColor::yellow);
	      }
	      vpDisplay::displayCamera(iObs,obMc,cam,0.5,vpColor::blue,0.5); 
	      vpDisplay::displayCamera(iObs,obMt,cam,0.5,vpColor::yellow,0.5);
	  	
	  	
	  	   vpDisplay::flush(iCam);
	  	   vpDisplay::flush(iObs);
      }
	}
  	
  	vpDisplay::flush(iCam);
  	vpDisplay::flush(iObs);
  	vpDisplay::getClick(iObs);

	return 0;
}
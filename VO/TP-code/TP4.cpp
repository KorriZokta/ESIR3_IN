#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>
#include <visp/vpKeyPointSurf.h>
#include <visp/vpHomography.h>
#include <array>
#define NBPOINTS 17

using namespace std ;

void magic(vpImagePoint * p1, vpImagePoint * p2) {
p1[0].set_u(117.5130997); p1[0].set_v(62.34123611); p2[0].set_u(202.841095); p2[0].set_v(36.29648209);
p1[1].set_u(84.06044006); p1[1].set_v(67.55551147); p2[1].set_u(169.5350189); p2[1].set_v(26.80556679);
p1[2].set_u(80.27194214); p1[2].set_v(111.0672302); p2[2].set_u(147.9641113); p2[2].set_v(64.5475769);
p1[3].set_u(342.6855164); p1[3].set_v(199.8661346); p2[3].set_u(63.4621048); p2[3].set_v(68.28819275);
p1[4].set_u(302.6676636); p1[4].set_v(226.6687317); p2[4].set_u(300.4017639); p2[4].set_v(263.6835022);
p1[5].set_u(101.5870972); p1[5].set_v(63.0242424); p2[5].set_u(187.8421478); p2[5].set_v(29.56011963);
p1[6].set_u(153.4119415); p1[6].set_v(91.05652618); p2[6].set_u(222.968277); p2[6].set_v(77.2434845);
p1[7].set_u(190.6780548); p1[7].set_v(110.7231598); p2[7].set_u(247.8312683); p2[7].set_v(110.4263763);
p1[8].set_u(302.8087463); p1[8].set_v(133.9337616); p2[8].set_u(339.9194641); p2[8].set_v(178.880661);
p1[9].set_u(162.7279968); p1[9].set_v(276.4970398); p2[9].set_u(152.7050171); p2[9].set_v(248.9367065);
p1[10].set_u(151.0850067); p1[10].set_v(36.12360764); p2[10].set_u(244.672287); p2[10].set_v(25.44586563);
p1[11].set_u(171.7740173); p1[11].set_v(53.67162704); p2[11].set_u(256.0083618); p2[11].set_v(49.99362183);
p1[12].set_u(116.7895355); p1[12].set_v(74.19098663); p2[12].set_u(196.8202972); p2[12].set_v(45.97808456);
p1[13].set_u(104.2023163); p1[13].set_v(83.85998535); p2[13].set_u(181.4200439); p2[13].set_v(50.26084518);
p1[14].set_u(84.71365356); p1[14].set_v(190.8507233); p2[14].set_u(300.4017639); p2[14].set_v(263.6835022);
p1[15].set_u(138.8526764); p1[15].set_v(273.5761719); p2[15].set_u(131.6974182); p2[15].set_v(236.8515778);
p1[16].set_u(167.2081451); p1[16].set_v(96.59983063); p2[16].set_u(233.1238556); p2[16].set_v(88.96112061);
}




// Calculer l'homographie aHb a partir des coordonnees des point p1 et p2
void DLT(unsigned int n,
	 vpImagePoint *p1,
	 vpImagePoint *p2,
	 vpMatrix &H12)
{
	  
	  // NBPTMIN points son necessaire ; remplace le 1e6 par ce nombre
	#define NBPTMIN 5
	  if(n<    NBPTMIN )
	  {
	    cout << "there must be at least " << NBPTMIN <<  " points in the both images\n" <<endl  ;
	    throw ;
	  }


		vpMatrix gamma(2*n,9);
	  for (int i=0;i<n;i++){
		//void vpMatrix::svd(vpColVector &w, vpMatrix &v)
		double x1=p1[i].get_u();	
		double y1=p1[i].get_v();
		
		double x2=p2[i].get_u();
		double y2=p2[i].get_v();

		double w2=1;
		double w1=1;
	
		gamma[2*i][0]=0;
		gamma[2*i][1]=0;
		gamma[2*i][2]=0;
		gamma[2*i][3]=-(w2*x1);
		gamma[2*i][4]=-(w2*y1);
		gamma[2*i][5]=-(w2*w1);
		gamma[2*i][6]=y2*x1;
		gamma[2*i][7]=y2*y1;
		gamma[2*i][8]=y2*w1;

		gamma[2*i+1][0]=w2*x1;
		gamma[2*i+1][1]=w2*y1;
		gamma[2*i+1][2]=w2*w1;
		gamma[2*i+1][3]=0;
		gamma[2*i+1][4]=0;
		gamma[2*i+1][5]=0;
		gamma[2*i+1][6]=-(x2*x1);
		gamma[2*i+1][7]=-(x2*y1);
		gamma[2*i+1][8]=-(x2*w1);

	  }

	std:cout<<gamma<<endl;

	vpMatrix d;
	vpColVector v;
	gamma.svd(v, d); 

	cout<<"matrice d"<<endl<<d<<endl<<"matrice v"<<endl<<v<<endl;


	double cp=50000000;
	int toast = 0;
	for (int cpt = 0;cpt<9;cpt++){
		double compare = v[cpt];
		if(compare<=cp){
			 toast = cpt ;
			cp = compare;
		}
	}

	cout<<toast<<endl;

	H12[0][0]=d[0][toast];
	H12[0][1]=d[1][toast];
	H12[0][2]=d[2][toast];
	H12[1][0]=d[3][toast];
	H12[1][1]=d[4][toast];
	H12[1][2]=d[5][toast];
	H12[2][0]=d[6][toast];
	H12[2][1]=d[7][toast];
	H12[2][2]=d[8][toast];

}

void Ransac(unsigned int n,
	 vpImagePoint *p1,
	 vpImagePoint *p2,
	vpImagePoint *vraip1,
	 vpImagePoint *vraip2,
	 vpMatrix &H12){
	
	int seuil = 10;
	int MonPetitCompteur=0;
	for (int i=0;i<n;i++){
		//On tire 4 points aléatoire et on les fait rentrer dans un tableau		
		int alea=0;
		int tabloDINT[n];
		  vpImagePoint p1New[n], p2New[n];
		while(alea<4){
			int randoom = rand()%18;			

			std::cout << "random : " << randoom <<std::endl;

			bool trouve = false;
			for (int h=0;h<n;h++){
				if(randoom==tabloDINT[h]){
					trouve = true;
				}
			}
			if(trouve==false){
				tabloDINT[alea]=randoom;
				alea++;
			}
		}
		 for (int iTest = 0; iTest < 4; iTest++){
			std::cout << "Index : " << tabloDINT[iTest] << std::endl;
		}

		for (int iRP = 0;iRP<4;iRP++){
			p1New[iRP]=p1[tabloDINT[iRP]];
			p2New[iRP]=p2[tabloDINT[iRP]];
		}

		//On calcule la DLT sur ces 4 points
		
		DLT(4,p1New, p2New, H12) ;
		bool testTrouve = false;
		for (int iTSM = 0 ;  iTSM<4 ; iTSM++){

			//A FAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIRE
			
			int testSeuil = p2New - p1New*H12;


			/////////////////////////////////////////////////////////////////////////////////////////////////////////
			if(testSeuil > seuil){
				testTrouve = true;;
			}
		}

		int compteur = 0;
		if(testTrouve == false){
			for (int iTT = 0 ; iTT <17 ; iTT++){


			//A FAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIRE

				int testVraiSeuil = p2New - p1New*H12;


			/////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(testVraiSeuil < seuil){
					compteur++;
				}
			} 
			
			if(compteur > MonPetitCompteur){
				vraip1 = p1New;
				vraip2 = p2New;
				MonPetitCompteur = compteur;
			}
		}
	}
	
}

int main()
{
  vpImage<unsigned char> I1(300,400,0);
  vpImage<unsigned char> I2(300,400,0);
  vpImage<vpRGBa> Iimage(876,1200);
  
 
  vpImageIo::read(Iimage,"../data/big-sleep.jpg") ;
  

  double L = 0.600 ;
  double l = 0.438;
  // Initialise the 3D coordinates of the Iimage corners
  vpColVector X[4];
  for (int i = 0; i < 4; i++) X[i].resize(3);
  // Top left corner
  X[0][0] = -L;
  X[0][1] = -l;
  X[0][2] = 0;
  
  // Top right corner
  X[1][0] = L;
  X[1][1] = -l;
  X[1][2] = 0;
  
  // Bottom right corner
  X[2][0] = L;
  X[2][1] = l;
  X[2][2] = 0;
  
  //Bottom left corner
  X[3][0] = -L;
  X[3][1] = l;
  X[3][2] = 0;
  


  vpImageSimulator sim;
  sim.init(Iimage, X);
  vpCameraParameters cam(800.0, 800.0, 200, 150);
  



  cam.printParameters() ;


  // I1g
  vpHomogeneousMatrix  c1gMo(0,0,2,  vpMath::rad(0),vpMath::rad(0),0) ;
  sim.setCameraPosition(c1gMo);
  sim.getImage(I1,cam);
  cout << "Image I1g " <<endl ;
  cout << c1gMo << endl ;

  // I1d
  vpHomogeneousMatrix c1dMo(0.1,0,2, 
			    vpMath::rad(0),vpMath::rad(0),vpMath::rad(25)) ; //0.1,0,2, vpMath::rad(0),vpMath::rad(0),0) ;
  sim.setCameraPosition(c1dMo);
  sim.getImage(I2,cam);  
  cout << "Image I1d " <<endl ;
  cout << c1dMo << endl ;
 
  vpHomogeneousMatrix cgMcd = c1gMo * c1dMo.inverse() ;
  vpMatrix K = cam.get_K() ;

  vpDisplayX dg(I1,10,10,"I1") ;
  vpDisplay::display(I1) ;
  vpDisplay::flush(I1) ;

  vpDisplayX dd(I2,450,10,"I2") ;
  vpDisplay::display(I2) ;
  vpDisplay::flush(I2) ;


  // Image resultat
int I1Width=I1.getWidth();
 int I1Height=I1.getHeight();
int I2Width=I2.getWidth();
 int I2Height=I2.getHeight();

  vpImage<unsigned char> I ;
  I.resize(I1Height, I1Width+I2Width) ;


 for (int i = 0; i < I1Height; i++){
	for (int j = 0; j < I1Width; j++){
		I[i][j] = I1[i][j];
	}
}
for (int i = 0; i < I2Height; i++){
	for (int j = 0; j < I2Width; j++){
		I[i][j+I1Width] = I2[i][j];
	}
}

vpDisplayX d(I,10,400,"I") ;
vpDisplay::display(I) ;
vpDisplay::flush(I) ;

unsigned int nb=NBPOINTS;
  vpImagePoint p1[nb], p2[nb];
	magic(p1, p2);


  if(nb >= 0){ // ... add paired points to vectPts
    
    for(unsigned int i=0; i<nb; i++)
      {
	//surf.getMatchedPoints(i, p1[i], p2[i]);
	char s[10] ;
	sprintf(s,"%d",i) ;
	cout << i <<"  "  << p1[i].get_u() <<"  " << p1[i].get_v() <<"  " ;
	cout <<  p2[i].get_u() <<"  " << p2[i].get_v() << endl;
	vpDisplay::displayCharString(I1,p1[i],s,vpColor::yellow) ;
	vpDisplay::displayCharString(I2,p2[i],s,vpColor::yellow) ;

	vpImagePoint p2_inline = vpImagePoint(p2[i].get_i(), p2[i].get_j() + I1.getWidth());
	vpDisplay::displayLine(I, p1[i], p2_inline, vpColor::red);
      }

  }
/*
/////////////////////////////////////////////////////////////////////////////////////////

  // Calculer l'homographie
  vpMatrix H21(3,3) ;
  DLT(nb,p1, p2, H21) ;

  cout << "Homographie H21 : " <<endl ; 
  cout << H21 << endl ;

	vpMatrix H12 = H21.inverseByLU();
  //Verification 
  double residue =0 ;
	for (int i=0 ; i < nb ; i++) 
    {
      // Connaissant le formule permettant le transfert des points p2 dans p1
      // Calculer les coordonnées des point p1 connaissant p2 et dHg
      vpImagePoint p1_calcule ;
      
      vpColVector x2(3) ;
      x2[0] = p2[i].get_u() ;
      x2[1] = p2[i].get_v() ;
      x2[2] = 1;
      
      vpColVector x1 = H12*x2;
      cout << x1.t() << endl ;
	
	x1 /=x1[2];      

	p1_calcule.set_u(x1[0]);
        p1_calcule.set_v(x1[1]); 
      
      cout<< p1_calcule <<endl;

      // en deduire l'erreur sur commise sur chaque point et 
      // afficher un cercle de rayon 10 fois cette erreur
      double r ;
      r = 2;
      cout << "point " <<i << "  " << r <<endl ;
      double rayon ;
      rayon = sqrt(r)*10 ; if (rayon < 10) rayon =10 ;
      vpDisplay::displayCircle(I1,p1_calcule,rayon,vpColor::green) ;
      
    }



/////////////////////////////////////////////////////////////////////////////////////////
*/


vpMatrix H12(3,3) ;
 
vpImagePoint vraip1[4], vraip2[4];
	
Ransac(4, p1, p2,vraip1, vraip2, H12);

vpDisplay::flush(I);
vpDisplay::flush(I1);
vpDisplay::flush(I2);
vpDisplay::getClick(I1);

  

  return 0;
}

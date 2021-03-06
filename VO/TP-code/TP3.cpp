#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>
#include <visp/vpDot.h>


using namespace std ;

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


int main()
{
  vpImage<unsigned char> I1;
  vpImage<unsigned char> I2;
  vpImage<vpRGBa> Iimage(876,1200);
  
 
  vpImageIo::read(I1,"../data/I1.pgm") ;
  vpImageIo::read(I2,"../data/I2originel.pgm") ;



  vpCameraParameters cam(800.0, 800.0, 200, 150);
  cam.printParameters() ;

  vpDisplayX d1(I1,10,10,"I1") ;
  vpDisplay::display(I1) ;
  vpDisplay::flush(I1) ;

  vpDisplayX d2(I2,450,10,"I2") ;
  vpDisplay::display(I2) ;
  vpDisplay::flush(I2) ;

  int nb = 5;
  vpImagePoint p1[nb], p2[nb];
  
  // clicker 5 point sur l'image I2 ; recuperer leur coordonnees
  for(unsigned int i=0; i<nb; i++)
    {
      vpDisplay::getClick(I1, p1[i]) ;
      vpDot d ;
      d.initTracking(I1,p1[i]) ;
      d.track(I1,p1[i]) ;
      char s[10] ;
      sprintf(s,"%d",i) ;
      vpDisplay::displayCross(I1,p1[i],10,vpColor::blue) ;
      vpDisplay::displayCharString(I1,p1[i],s,vpColor::red) ;
      vpDisplay::flush(I1) ;
    }
  
  // clicker 5 point sur l'image I1 ; recuperer leur coordonnees
  // faites attention a les clicker dans le meme ordre
  for(unsigned int i=0; i<nb; i++)
    {
      vpDisplay::getClick(I2, p2[i]) ;
      vpDot d ;
      d.initTracking(I2,p2[i]) ;
      d.track(I2,p2[i]) ;
      char s[10] ;
      sprintf(s,"%d",i) ;
      vpDisplay::displayCross(I2,p2[i],10,vpColor::green) ;
      vpDisplay::displayCharString(I2,p2[i],s,vpColor::red) ;
      vpDisplay::flush(I2) ;
    }
  

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
      // Calculer les coordonn�es des point p1 connaissant p2 et dHg
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


  vpDisplay::flush(I1) ;
  vpImage<vpRGBa> Ic ;
  vpDisplay::getImage(I1,Ic) ;
  vpImageIo::write(Ic,"resultat.jpg") ;

  vpDisplay::getClick(I1) ;

  vpDisplay::close(I2) ;
  vpDisplay::close(I1) ;


vpImage<unsigned char> Imos(1000,1000);
	for (int i=0; i<Imos.getHeight(); i++)
		for (int j=0; j<Imos.getWidth(); j++) {
			//on prend la premi�re luminance
			if (i<I1.getHeight() && j<I1.getWidth()) {
				Imos[i][j] = I1[i][j] / 2;
			}

			vpColVector x2(3);
			x2[0] = j;
			x2[1] = i;
			x2[2] = 1;

			vpColVector x3 = H21 * x2;

			x3 = x3/x3[2];
			int i2 = x3[1];
			int j2 = x3[0];

			//on fait la moyenne entre la premi�re luminance et la deuxi�me
			if (i2<I2.getHeight() && j2<I2.getWidth()){
				 Imos[i][j] += I2[i2][j2] / 2;
			}
	}

	vpDisplayX d3(Imos,0,0,"Imos") ;
	vpDisplay::display(Imos);
	vpDisplay::flush(Imos) ;
	vpDisplay::getClick(Imos) ;
	vpDisplay::close(Imos) ;
  

  return 0;
}

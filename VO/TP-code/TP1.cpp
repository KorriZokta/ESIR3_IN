#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>


using namespace std ;



int main()
{
  vpImage<unsigned char> Ig(300,400,0);
  vpImage<unsigned char> Id(300,400,0);
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
  vpHomogeneousMatrix  gMo(0,0,2,  vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;//position de l'objet, mais pas celle de camera
  sim.setCameraPosition(gMo);
  sim.getImage(Ig,cam);
  cout << "Image I1g " <<endl ;
  cout << "gMo " << endl ;
  cout << gMo << endl ;

  // I1d
  vpHomogeneousMatrix dMo(0,0,2, vpMath::rad(5),vpMath::rad(5),vpMath::rad(5)) ; //rotation pure
  //vpHomogeneousMatrix dMo(0.1,0,1.9, vpMath::rad(5),vpMath::rad(5),vpMath::rad(5)) ;
  //vpHomogeneousMatrix dMo(0.1,0,2, vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;
  //vpHomogeneousMatrix dMo(0.1,0,2.2, vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;
  //vpHomogeneousMatrix dMo(0,0,2.2, vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;
  //vpHomogeneousMatrix dMo(0,0.1,2, vpMath::rad(0),vpMath::rad(0),vpMath::rad(0)) ;

  sim.setCameraPosition(dMo);
  sim.getImage(Id,cam);  
  cout << "Image I1d " <<endl ;
  cout << "dMo " << endl ;
  cout << dMo << endl ;
 

  vpDisplayX dg(Ig,10,10,"Ig") ;
  vpDisplay::display(Ig) ;
  vpDisplay::flush(Ig) ;

  vpDisplayX dd(Id,410,10,"Id") ;
  vpDisplay::display(Id) ;
  vpDisplay::flush(Id) ;

  vpImagePoint pd ;//le point dans l'image droite

  vpHomogeneousMatrix gMd = gMo*dMo.inverse();
  vpMatrix K_inverse = cam.get_K_inverse();//K^-1
  vpMatrix K_inverse_transpose = K_inverse.transpose();//K^-T
  vpRotationMatrix gRd; gMd.extract(gRd);//1R2
  vpTranslationVector gTd; gMd.extract(gTd);
  vpMatrix gtd_x = gTd.skew();//[1t2]x
  vpMatrix Fundamental = K_inverse_transpose * gtd_x * gRd * K_inverse;//

  //inverse
  vpHomogeneousMatrix dMg = dMo*gMo.inverse();
  vpRotationMatrix dRg; dMg.extract(dRg);//2R1
  vpTranslationVector dTg; dMg.extract(dTg);
  vpMatrix dtg_x = dTg.skew();//[2t1]x
  vpMatrix Fundamental_inverse = K_inverse_transpose * dtg_x * dRg * K_inverse;//
  /*
  for (int i=0 ; i < 5 ; i++)
    {
      cout << "Click point number " << i << endl ;
      vpDisplay::getClick(Id, pd) ;   
      vpDisplay::displayCross(Id,pd,5,vpColor::red) ;
      
      // Calcul du lieu geometrique
      vpMatrix xd(3, 1); 
      xd[0][0] = pd.get_u();
      xd[1][0] = pd.get_v();
      xd[2][0] = 1;
      vpMatrix param = Fundamental * xd;
      

      int hauteur = Ig.getHeight();
      int largeur = Ig.getWidth();
      double a = param[0][0], b = param[1][0], c = param[2][0];
      cout << "a = "<<a<<"; " << "b = "<<b<<"; " << "c = "<<c<<"; " << endl;

      // j = u(horizontale) et i = v(verticale);
      int i1, j1, i2, j2;
      if(b != 0){
	      //selon a*u1 + b*v1 + c = 0, on fixe j1 = 0 pour trouver i1; on fixe j2 pour trouver i2;
	      i1 = -c/b; j1 = 0; i2 = (-c-a*(largeur-1))/b; j2 = largeur-1;
      }
      else {
	      //selon a*u1 + b*v1 + c = 0, on fixe i1 = 0 pour trouver j1; on fixe i2 pour trouver j2;
	      i1 = 0; j1 = -c/a; i2 = hauteur-1; j2 = -c/a;
      }
      
      
      cout << "i1 = "<<i1<<"; " << "j1 = "<<j1<<"; " <<endl;
      cout << "i2 = "<<i2<<"; " << "j2 = "<<j2<<"; " <<endl;

      // Affichage dans Ig
      vpDisplay::displayLine(Ig,i1,j1,i2,j2,vpColor::red,1) ;
      vpDisplay::flush(Id) ;
      vpDisplay::flush(Ig) ;
    }//fin boucle
*/

  for (int i=0 ; i < 5 ; i++)
    {
      cout << "Click point number " << i << endl ;
      vpDisplay::getClick(Ig, pd) ;
      vpDisplay::displayCross(Ig,pd,5,vpColor::red) ;
      // Calcul du lieu geometrique
      vpMatrix xg(3, 1); 
      xg[0][0] = pd.get_u();
      xg[1][0] = pd.get_v();
      xg[2][0] = 1;
      vpMatrix param = Fundamental_inverse * xg;
      
      int hauteur = Id.getHeight();
      int largeur = Id.getWidth();
      double a = param[0][0], b = param[1][0], c = param[2][0];
      cout << "a = "<<a<<"; " << "b = "<<b<<"; " << "c = "<<c<<"; " << endl;

      // j = u(horizontale) et i = v(verticale);
      //selon a*u1 + b*v1 + c = 0, on fixe j1 = 0 pour trouver i1; on fixe j2 pour trouver i2;
      int i1=-c/b, j1=0, i2=(-c-a*(largeur-1))/b, j2=largeur-1;
      
      cout << "i1 = "<<i1<<"; " << "j1 = "<<j1<<"; " <<endl;
      cout << "i2 = "<<i2<<"; " << "j2 = "<<j2<<"; " <<endl;

      // Affichage dans Ig
      //vpDisplay::displayLine(Ig,i1,j1,i2,j2,vpColor::red,1) ;
      vpDisplay::displayLine(Id,i1,j1,i2,j2,vpColor::red,1) ;
      vpDisplay::flush(Id) ;
      vpDisplay::flush(Ig) ;
    }//fin boucle

  // exemple de code pour sauvegarder une image avec les plan overlay
  vpImage<vpRGBa> Icol1 ;
  vpDisplay::getImage(Id,Icol1) ;
  vpImageIo::write(Icol1,"outputTP1/Id.jpg") ;
  vpImage<vpRGBa> Icol2 ;
  vpDisplay::getImage(Ig,Icol2) ;
  vpImageIo::write(Ig,"outputTP1/Ig.jpg") ;


  //vpDisplay::getClick(Id) ;
  //vpDisplay::getClick(Ig) ;
  cout << "OK " << endl ;

  vpDisplay::close(Id) ;
  vpDisplay::close(Ig) ;

  

  return 0;
}

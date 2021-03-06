#include <iostream>

#include <visp/vpDebug.h>
#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpImageSimulator.h>
#include <visp/vpDisplayX.h>


using namespace std ;


int main()
{
  vpImage<unsigned char> Iimage1(288,384);
  vpImage<unsigned char> Iimage2(288,384);
  vpImage<float> carte(288,384);
  vpImage<unsigned char> carte2(288,384);
  vpImageIo::read(Iimage1,"../data/scene_l.pgm") ;
  vpImageIo::read(Iimage2,"../data/scene_r.pgm") ;
  vpMatrix filtre(5,5);

	filtre[0][0] = 1;
	filtre[0][1] = 3;
	filtre[0][2] = 4;
	filtre[0][3] = 3;
	filtre[0][4] = 1;
	filtre[1][0] = 3;
	filtre[1][1] = 5;
	filtre[1][2] = 7;
	filtre[1][3] = 5;
	filtre[1][4] = 3;
	filtre[2][0] = 4;
	filtre[2][1] = 7;
	filtre[2][2] = 9;
	filtre[2][3] = 7;
	filtre[2][4] = 4;
	filtre[3][0] = 3;
	filtre[3][1] = 5;
	filtre[3][2] = 7;
	filtre[3][3] = 5;
	filtre[3][4] = 3;
	filtre[4][0] = 1;
	filtre[4][1] = 3;
	filtre[4][2] = 4;
	filtre[4][3] = 3;
	filtre[4][4] = 1;

/*
  for (int i=0;i<288;i++){
	for (int j=0;j<384;j++){

		float aMinimiser = 255;

		for (int k=0;k<384;k++){
			float now = abs(Iimage2[i][k]-Iimage1[i][j]);
			if(now<aMinimiser){
				aMinimiser = now;
				carte[i][j]=abs(k-j);
			}
		}
	}
  }
*/


for (int i=0;i<288;i++){
	for (int j=0;j<384;j++){

		float aMinimiser = 255*255;

		if(i==0 || j==0 || i == 287 || j==383 || i == 1 || j==1|| i == 286 || j==382){
 			carte[i][j]=0;
		}else{

			float now = 0.0;
			for (int k = 0 ; k<384 ; k++){
				float calc= 0.0;

				for (int y = 0; y<5; y++) {
					for (int z = 0; z<5;z++){

						calc = calc + ( filtre[y][z]* vpMath::sqr(Iimage2[i-2+y][k-2+z]-Iimage1[i-2+y][j-2+z]));
					}
				}

				now = calc/25;

				if(now<aMinimiser){
					aMinimiser = now;
					if(abs(k-j)>255){carte[i][j]=0;}else{
					carte[i][j]=abs(k-j);}
				}

			}
		}
	}
}



vpImageConvert::convert(carte,carte2);

  // exemple de code pour sauvegarder une image avec les plan overlay
  vpImage<vpRGBa> Icol ;
  vpDisplay::getImage(carte2,Icol) ;
  vpImageIo::write(Icol,"resultat.jpg") ;
  vpImageIo::write(carte2,"I1g.jpg") ;

  

  return 0;
}

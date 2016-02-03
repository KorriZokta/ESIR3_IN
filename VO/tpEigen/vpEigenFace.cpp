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


int main()
{
	
  	vpImage<unsigned char> Iimage(112,92);
  	
  	vpImage<double> IMoy(112,92);
  	vpImage<unsigned char> vpMoy(112,92);

	vpImage<unsigned char> Ivisage(112,92);
	vpImage<unsigned char> Icentree(112,92);	

	vpImage<double> Itemp(112,92);
	vpImage<unsigned char> Ieigen(112,92);


	int h = 92;
	int w = 112;
	int nb = 200;
	int size = h*w;
	vpMatrix mat (h*w,nb);

	int cpt = 0;
	for (int i =1;i<=40;i++){
		for (int j = 1;j<=5;j++){
			stringstream ss;
			ss << "att_faces/s";
			ss << i;
			ss <<"/";
			ss <<j;
			ss << ".pgm";
			string s = ss.str();
			
	  		vpImageIo::read(Iimage,s) ;
			
			for(int x=0;x<w;x++){
				for(int y=0;y<h;y++){
					mat[x*h+y][cpt] = Iimage(x,y)/255.0f;
				}
			}
			cpt++;
		}
	}
	
	vpColVector vpMoyCol(size);
	//Mise en pratique
	int m=nb;
	int n=h*w; 
	for (int i=0;i<n;i++){
		float t = 0;
		for (int j=0;j<m;j++){
			t = t+mat[i][j];
		}
		double tfinal=t/200.0f;
		//cout<<tfinal<<"\n";
		vpMoyCol[i]=tfinal; 
	}


	string s2="att_faces/s1/1.pgm";
	vpImageIo::read(Ivisage,s2) ;

	vpImage<double> ICtemp(112,92);
	
	//visage centre
	vpColVector IC = mat.getCol(0) - vpMoyCol;
	
	for (int i=0;i<w;i++){
		for (int j=0;j<h;j++){
			IMoy[i][j] = vpMoyCol[i*h+j];
		}
	} 
	

	for (int i=0;i<w;i++){
		for (int j=0;j<h;j++){
			ICtemp[i][j] = IC[i*h+j];
		}
	} 
	vpImageConvert::convert(ICtemp, Icentree);
	
	vpImageConvert::convert(IMoy,vpMoy);

	vpDisplayX d1(vpMoy,112,92) ;
	vpDisplay::setTitle(vpMoy, "vpMoy");
	vpDisplay::display(vpMoy);
	vpDisplay::flush(vpMoy);

	vpDisplayX d2(Ivisage,112,92) ;
	vpDisplay::setTitle(Ivisage, "Visage");
	vpDisplay::display(Ivisage);

	vpDisplayX d3(Icentree,112,92) ;
	vpDisplay::setTitle(Icentree, "Centree");
	vpDisplay::display(Icentree);


	//Analyse en composantes Principale

	vpMatrix A ;
	for (int cpt = 0 ; cpt < nb ; cpt++){
		vpColVector xTry=mat.getCol(cpt) - vpMoyCol;
		A.stack(xTry.t());	
	}

	vpDisplay::flush(Ivisage) ;
	vpDisplay::flush(Icentree) ;
	//Calcul des eigenfaces
	vpMatrix V;
	vpMatrix U=A.t();
	vpColVector S;
	//A devient U
	U.svd(S,V);

	for (int i=0;i<w;i++){
		for (int j=0;j<h;j++){
			Itemp[i][j] = U[i*h+j][0];
		}
	}

	/*for(int k=0;k<200;k++){
		for (int i=0;i<w;i++){
			for (int j=0;j<h;j++){
				Itemp[i][j] = U[i*h+j][k];
			}
		}
		vpImageConvert::convert(Itemp, Ieigen);
		
		vpDisplayX d4(Ieigen,112,92) ;
		vpDisplay::setTitle(Ieigen, "eigen");
		vpDisplay::display(Ieigen);
		vpDisplay::flush(Ieigen) ;
		vpDisplay::getClick(Ieigen);
	}*/
	vpImageConvert::convert(Itemp, Ieigen);
	vpDisplayX d4(Ieigen,112,92) ;
	vpDisplay::setTitle(Ieigen, "eigen");
	vpDisplay::display(Ieigen);	
	vpDisplay::flush(Ieigen) ;

	//Projection dans le sous-espace des visages
	//De la
	int vis =0;
	int K=200;
	vpColVector Wkf(K);	
	vpColVector Uk(size);
	vpRowVector Jsm(size);
	double Wk;

	Jsm = (mat.getCol(vis) - vpMoyCol).t();
		
	for (int cpt = 0 ; cpt<K ; cpt++){
		
		Uk = U.getCol(cpt);
		
		std::cout<<"JSM " <<Jsm.size()<<" UK "<<Uk.size() <<"cpt"<<std::endl;
		Wk=Jsm*Uk;
		Wkf[cpt]=Wk;
		//std::cout<<Wkf[cpt]<<" " <<cpt<<std::endl;
	}
	//a la c'est la merde
	//en dessous ca marche
	vpColVector Uk2(size);
	
	vpColVector Jp(size);
	
	Jp=vpMoyCol;
	
		
	for(int cpt =0;cpt<K;cpt++){
		Uk2 = U.getCol(cpt);
		
		Jp=Jp+(Uk2*Wkf[cpt]);
	}	

	vpImage<double> IRecTemp(112,92);
	vpImage<unsigned char> IRecons(112,92);
	for (int i=0;i<w;i++){
		for (int j=0;j<h;j++){
			IRecTemp[i][j] = Jp[i*h+j];
		}
	} 

	vpImageConvert::convert(IRecTemp, IRecons);

	vpDisplayX d5(IRecons,112,92) ;
	vpDisplay::setTitle(IRecons, "Recons");
	vpDisplay::display(IRecons);

	//Free
	
	vpDisplay::flush(Ieigen) ;
	vpDisplay::flush(IRecons) ;

	vpDisplay::getClick(IRecons);
	return 0;
}

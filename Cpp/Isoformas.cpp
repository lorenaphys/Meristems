#include <iostream>
#include <tclap/CmdLine.h>
#include <stdio.h>  // libreria basica para entrada y salida  
#include <stdlib.h> // libreria para el uso de rand()  
#include <time.h>   // libreria para el uso de time() 
#include <math.h>
#include <algorithm> // std::min_element, std::max_element


using namespace std;


	void lap(double H[60][40][40])
	{
		int i, j, k, Nx = 60, Ny = 40, Nz = 40;
		double laplacian[Nx][Ny][Nz];

		for(i = 0; i < Nx; i ++)
		{
			for(j = 0; j < Ny; j ++)
			{
				for(k = 0; k < Nz; k++)
				{
					laplacian[i][j][k] = 0.0;
				} 
			}
		}	
	
		for(i = 1; i < Nx-2; i ++)
		{
			for(j = 1; j < Ny-2; j ++)
			{
				for(k = 1; k < Nz-2; k++)
				{
					laplacian[i][j][k] = H[i-1][j][k]+ H[i+1][j][k] + H[i][j-1][k] \
					+ H[i][j+1][k] + H[i][j][k-1] + H[i][j][k+1] - 6.0*H[i][j][k];
				} 
			}
		}
	}


//TCLAP::CmdLine cmd("Command description message", ' ', "0.1");
//TCLAP::ValueArg<double> eps("eps","Parametro_eps", "Parametro de orden",false,0.1,"double",cmd);
//TCLAP::ValueArg<int> n("n","Contador_n", "Rompimiento de simetria",false,2,"int",cmd);
//TCLAP::ValueArg<double> afi("afi","Coeficiente_afi", "Coeficiente Afi",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> av("av","Coeficiente_av", "Coeficiente Av",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> duu("duu","Coeficiente_duu", "Coeficiente Duu",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> as("as","Coeficiente_as", "Coeficiente As",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> ab("ab","Coeficiente_ab", "Coeficiente Ab",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> af("af","Coeficiente_af", "Coeficiente Af",false,1.0,"double",cmd);
//TCLAP::ValueArg<int> nF("nF","Contador_nF", "Numero de iteraciones",false,200,"int",cmd);
//TCLAP::ValueArg<int> st("st","Contador_st", "Numero de iteraciones internas",false,200,"int",cmd);

int main(int argc, char* argv[])
{

int Nx = 60;
int Ny = 40;
int Nz = 40;
double R = 11.0;
//double Afi = afi.getValue();
//double Av = av.getValue();
//double Duu = duu.getValue();
//double As = as.getValue();
//double Ab = ab.getValue();
//double Af = af.getValue();
//int NF = nF.getValue();
//int step = st.getValue();
//double ep = eps.getValue();
//double ep1 = pow(ep,2);
//double dt = 1.0e-4; 
double fi[Nx][Ny][Nz];
double r[Nx][Ny][Nz];
double aa[Nz];
double bb,aux;
int R1,i,j,k;

	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			for(k = 0; k < Nz; k++)
			{
				fi[i][j][k]= 1.0;
				r[i][j][k] = sqrt(pow((double)(i)-((double)(Nx)/(double)(2)),2) + \
				pow((double)(j)-((double)(Ny)/(double)(2)),2) + pow((double)(k),2));
				if(r[i][j][k] >= R)
				{
					fi[i][j][k] = -1.0;
				} 
			}
		}
	}

	for(k = 0; k < Nz; k++)
	{
		aa[k] = fabs(fi[Nx/2][Ny/2][k]); 
	}

	bb = aa[0];
	R1 = 0;

	for(k = 0; k < Nz; k++)
	{
		aux = min(bb,aa[k]);
		if(aux == aa[k])
		{
			R1 = k;
		}
		bb = aux;
	}	

	lap(fi);

	//for(i = 0; i < Nx; i++)
	//{
		//for(j = 0; j < Ny; j++)
		//{
			//for(k = 0; k < Nz; k++)
			//{
				//cout<< lapfi[i][j][k] << endl; 
			//}
		//}
	//}
	
	//printf ("\n%d\n",R1);

}

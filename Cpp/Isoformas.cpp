#include <iostream>
#include <tclap/CmdLine.h>
#include <stdio.h>  // libreria basica para entrada y salida  
#include <stdlib.h> // libreria para el uso de rand()  
#include <time.h>   // libreria para el uso de time() 
#include <math.h>
#include <algorithm> // std::min_element, std::max_element


using namespace std;

typedef double array_type[60][40][40];

	void copia(array_type &ent, array_type &sal)
	{
		int i,j,k, Nx = 60, Ny = 40, Nz = 40;
		for(i = 0; i < Nx; i++)
		{
			for(j = 0; j < Ny; j++)
			{
				for(k = 0; k < Nz; k++)
				{
					ent[i][j][k] = sal[i][j][k];
				}
			}
		}
	}

	void  lap(array_type &H2, array_type &H)
	{

		array_type laplacian = {0.0};
		
	
		int i, j, k, Nx = 60, Ny = 40, Nz = 40;

		for(i = 1; i < Nx-2; i ++)
		{
			for(j = 1; j < Ny-2; j ++)
			{
				for(k = 1; k < Nz-2; k++)
				{
					laplacian[i][j][k] = H[i-1][j][k] + H[i+1][j][k] + H[i][j-1][k] + H[i][j+1][k] + H[i][j][k-1] + H[i][j][k+1] - 6.0 * H[i][j][k];
				} 
			}

		}
		
		copia(H2,laplacian);
	}
	


TCLAP::CmdLine cmd("Command description message", ' ', "0.1");
TCLAP::ValueArg<double> eps("e","Parametro_eps", "Parametro de orden",false,0.1,"double",cmd);
//TCLAP::ValueArg<int> n("n","Contador_n", "Rompimiento de simetria",false,2,"int",cmd);
TCLAP::ValueArg<double> afi("","Coeficiente_afi", "Coeficiente Afi",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> av("av","Coeficiente_av", "Coeficiente Av",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> duu("duu","Coeficiente_duu", "Coeficiente Duu",false,1.0,"double",cmd);
//TCLAP::ValueArg<double> as("as","Coeficiente_as", "Coeficiente As",false,1.0,"double",cmd);
TCLAP::ValueArg<double> ab("","Coeficiente_ab", "Coeficiente Ab",false,1.0,"double",cmd);
TCLAP::ValueArg<double> af("","Coeficiente_af", "Coeficiente Af",false,1.0,"double",cmd);
TCLAP::ValueArg<int> nF("","Contador_nF", "Numero de iteraciones",false,200,"int",cmd);
TCLAP::ValueArg<int> st("","Contador_st", "Numero de iteraciones internas",false,200,"int",cmd);

int main(int argc, char* argv[])
{

int Nx = 60;
int Ny = 40;
int Nz = 40;
double R = 11.0;
double dt = 1e-4;
double Afi = afi.getValue();
//double Av = av.getValue();
//double Duu = duu.getValue();
//double As = as.getValue();
double Ab = ab.getValue();
double Af = af.getValue();
int NF = nF.getValue();
int step = st.getValue();
double ep = eps.getValue();
double ep1 = pow(ep,2);
//double dt = 1.0e-4; 
array_type fi, r;
double aa[Nz];
double bb,aux;
double beta = 1.0, sigma = -5.5, sifiu = 1e-4;
double u1 = 0.0, u2 = 0.0, u3 = 0.0;
int R1,i,j,k;

	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			for(k = 0; k < Nz; k++)
			{
				fi[i][j][k]= 1.0;
				r[i][j][k] = sqrt(pow((double)(i)-((double)(Nx)/2),2) + \
				pow((double)(j)-((double)(Ny)/2),2) + pow((double)(k),2));
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
		if(bb <= aa[k])
		{
			R1 = k;
		}
		else
		{
			bb = aa[k];
		}

	}
	
	array_type u;
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			for(k = 0; k < Nz; k++)
			{
				u[i][j][k] = exp(-(pow(double(i)-double(Nx)/2,2.0) + pow(double(j)-double(Ny)/2,2.0) + pow(double(k)- double(R1)+8.0,2.0))/100);
			}
		}
	}

array_type lapfi, lapu, mu, F,lapmu, Fs, Ft, F2, E, lapE, fi1;
int i1,j1;

	for(i1 = 0; i < NF; i++)
	{
		for(j1 = 0; j < step; j++)
		{
			//laplaciano de fi
			lap(lapfi,fi);
			
			//laplaciano de u
			lap(lapu,u);
			
			//definicion de mu
			for(i = 0; i < Nx; i++)
			{
				for(j = 0; j < Ny; j++)
				{
					for(k = 0; k < Nz; k++)
					{
						mu[i][j][k] = (pow(fi[i][j][k],2)-1)*(fi[i][j][k] - ep*beta*pow(u[i][j][k],2)) - ep1*lapfi[i][j][k];
					}
				}
			}
			
			//laplaciano de mu
			lap(lapmu,mu);
			
			//definicion de F
			for(i = 0; i < Nx; i++)
			{
				for(j = 0; j < Ny; j++)
				{
					for(k = 0; k < Nz; k++)
					{
						F[i][j][k] = 2*Afi*mu[i][j][k]*(3*pow(fi[i][j][k],2)-2*ep*beta*pow(u[i][j][k],2)-1)-2*Afi*ep1*lapmu[i][j][k];
					}
				}
			}
			
			//definiendo Fs
			for(i = 0; i < Nx; i++)
			{
				for(j = 0; j < Ny; j++)
				{
					for(k = 0; k < Nz; k++)
					{
						Fs[i][j][k] = sigma*lapfi[i][j][k];
					}
				}
			}
			
			//definiendo Ft
			for(i = 0; i < Nx; i++)
			{
				for(j = 0; j < Ny; j++)
				{
					for(k = 0; k < Nz; k++)
					{
						Ft[i][j][k] = -sifiu*lapu[i][j][k];
					}
				}
			}
			
			//definiendo F2
			for(i = 0; i < Nx; i++)
			{
				for(j = 0; j < Ny; j++)
				{
					for(k = 0; k < Nz; k++)
					{
						F2[i][j][k] = 4*Ab*fi[i][j][k]*(pow(fi[i][j][k],2)-1)*pow(u[i][j][k]-u1,2)*pow(u[i][j][k]-u2,2)+2*Af*fi[i][j][k]*pow(u[i][j][k]-u3,2);
					}
				}
			}
			
			//definiendo la energia
			//for(i = 0; i < Nx; i++)
			//{
				//for(j = 0; j < Ny; j++)
				//{
					//for(k = 0; k < Nz; k++)
					//{
						//E[i][j][k] = F[i][j][k] - Fs[i][j][k] + Ft[i][j][k] + F2[i][j][k];
					//}
				//}
			//}
			
			//laplaciano de E
			//lap(lapE,E);
			
			//integracion de fi con el metodo de Euler
			//copia(fi1,fi);
			//for(i = 0; i < Nx; i++)
			//{
				//for(j = 0; j < Ny; j++)
				//{
					//for(k = 0; k < Nz; k++)
					//{
						//fi[i][j][k] = fi[i][j][k] + dt*lapE[i][j][k];
					//}
				//}
			//}

		}
	}

	for(k = 0; k < Nz; k++)
	{
		cout << fi[Nx/2][Ny/2][k] << endl;
	}

}

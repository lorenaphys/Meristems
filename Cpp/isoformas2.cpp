#include <iostream>
//#include <tclap/CmdLine.h>
#include <stdio.h>  // libreria basica para entrada y salida  
#include <stdlib.h> // libreria para el uso de rand()  
#include <time.h>   // libreria para el uso de time() 
#include <math.h>
#include <algorithm> // std::min_element, std::max_element
#include <itpp/itbase.h>

using namespace std;
using namespace itpp;

//void lap(vec H(60*40*40), vec H2(60*40*40))
//{
	//int i, j, k, Nx = 60, Ny = 40, Nz = 40, n = Nx*Ny*Nz;
	//vec laplacian(n);
	//for(i = 1; i < Nx-2; i++)
	//{
		//for(j = 1; j < Ny-2; j++)
		//{
			//for(k = 1; k < Nz-2; k++)
			//{
				
			//}
		//}
	//}
//}

int main(int argc, char* argv[])
{
	int Nx = 60, Ny = 40, Nz = 40;
	int n = Nx*Ny*Nz;
	vec fi(n), r(n);
	fi.ones();
	int i, j, k, a = 0;
	for(i = 0; i < Nx; i++)
	{
		for(j = 0; j < Ny; j++)
		{
			for(k = 0; k < Nz; k++)
			{
				a = (i-1)*Ny*Nz + (j-1)*Nz + k -1;
				r(a) = sqrt(pow((double)i-Nx/2,2) + pow((double)j-Ny/2,2) + pow((double)k,2));
				if(r(a) >= 11.0)
				{
					fi(a) = -1;
				}
			}
		}
	}
	
	for(i = 0; i < n; i++)
	{
		cout << fi(i) << endl;
	}
}


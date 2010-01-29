// heisenberg.hpp
// 2D and 3D Heisenberg model 
// Questions/comments to gruberja@gmail.com (Jason Gruber)

#ifndef HEISENBERG_UPDATE
#define HEISENBERG_UPDATE
#include"MMSP.hpp"
#include<cmath>

namespace MMSP{

void update(grid<2,vector<double> >& grid, int steps)
{
	double J = 1.0;

	const double kT = 0.50;
	int nx = xlength(grid);
	int ny = ylength(grid);
	int n = nx*ny;

	for (int step=0; step<steps; step++) {
		for (int h=0; h<n; h++) {
			int x = x0(grid)+rand()%nx;
			int y = y0(grid)+rand()%ny;
			vector<double>& s1 = grid[x][y];

			vector<double> s2;
			resize(s2,3);
			double psi = 2.0*acos(-1.0)*double(rand())/double(RAND_MAX);
			double theta = acos(1.0-2.0*double(rand())/double(RAND_MAX));
			s2[0] = cos(psi)*sin(theta);
			s2[1] = sin(psi)*sin(theta);
			s2[2] = cos(theta);
			
			double sum = -1.0;
			for (int i=-1; i<=1; i++)
				for (int j=-1; j<=1; j++) {
					vector<double>& s = grid[x+i][y+j];
					sum += s[0]*(s1[0]-s2[0])+s[1]*(s1[1]-s2[1])+s[2]*(s1[2]-s2[2]);
				}
			double dE = -J*sum;

			double r = double(rand())/double(RAND_MAX);
			if (dE<=0.0) grid[x][y] = s2;
			else if (r<exp(-dE/kT)) grid[x][y] = s2;

			if (h%(ny)==0) ghostswap(grid);
		}
	}
}

void update(grid<3,vector<double> >& grid, int steps)
{
	double J = 1.0;

	const double kT = 0.75;
	int nx = xlength(grid);
	int ny = ylength(grid);
	int nz = zlength(grid);
	int n = nx*ny*nz;

	for (int step=0; step<steps; step++) {
		for (int h=0; h<n; h++) {
			int x = x0(grid)+rand()%nx;
			int y = y0(grid)+rand()%ny;
			int z = z0(grid)+rand()%nz;
			vector<double>& s1 = grid[x][y][z];

			vector<double> s2;
			resize(s2,3);
			double psi = 2.0*acos(-1.0)*double(rand())/double(RAND_MAX);
			double theta = acos(1.0-2.0*double(rand())/double(RAND_MAX));
			s2[0] = cos(psi)*sin(theta);
			s2[1] = sin(psi)*sin(theta);
			s2[2] = cos(theta);
			
			double sum = -1.0;
			for (int i=-1; i<=1; i++)
				for (int j=-1; j<=1; j++)
					for (int k=-1; k<=1; k++) {
						vector<double>& s = grid[x+i][y+j][z+k];
						sum += s[0]*(s1[0]-s2[0])+s[1]*(s1[1]-s2[1])+s[2]*(s1[2]-s2[2]);
					}
			double dE = -J*sum;

			double r = double(rand())/double(RAND_MAX);
			if (dE<=0.0) grid[x][y][z] = s2;
			else if (r<exp(-dE/kT)) grid[x][y][z] = s2;

			if (h%(ny*nz)==0) ghostswap(grid);
		}
	}
}

} // namespace MMSP

#endif

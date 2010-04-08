// cahn-hilliard.hpp
// Algorithms for 2D and 3D Cahn-Hilliard model
// Questions/comments to gruberja@gmail.com (Jason Gruber)

#ifndef CAHNHILLIARD_UPDATE
#define CAHNHILLIARD_UPDATE
#include"MMSP.hpp"
#include<cmath>

namespace MMSP{

void generate(int dim, const char* filename)
{
	if (dim==2) {
		MMSP::grid<2,double> grid(1,0,128,0,128);

		for (int i=0; i<nodes(grid); i++) {
			vector<int> x = position(grid,i);
			grid(x) = 1.0-2.0*double(rand())/double(RAND_MAX);
		}

		output(grid,filename);
	}

	if (dim==3) {
		MMSP::grid<3,double> grid(1,0,64,0,64,0,64);

		for (int i=0; i<nodes(grid); i++) {
			vector<int> x = position(grid,i);
			grid(x) = 1.0-2.0*double(rand())/double(RAND_MAX);
		}

		MMSP::output(grid,filename);
	}
}

template <int dim, typename T> void update(MMSP::grid<dim,T>& grid, int steps)
{
	MMSP::grid<dim,T> update(grid);
	MMSP::grid<dim,T> temp(grid);

	double r = 1.0;
	double u = 1.0;
	double K = 1.0;
	double M = 1.0;
	double dt = 0.01;

	for (int step=0; step<steps; step++) {
		for (int i=0; i<nodes(grid); i++) {
			vector<int> x = position(grid,i);
			temp(x) = -r*grid(x)+u*pow(grid(x),3)-K*laplacian(grid,x);
		}
		ghostswap(temp);

		for (int i=0; i<nodes(grid); i++) {
			vector<int> x = position(grid,i);
			update(x) = grid(x)+dt*M*laplacian(temp,x);
		}
		swap(grid,update);
		ghostswap(grid);
	}
}

} // namespace MMSP

#endif

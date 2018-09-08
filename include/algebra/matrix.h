#ifndef CYAN_MATRIX_H
#define CYAN_MATRIX_H

typedef struct {

	int rows ;
	int cols ;
	double* mat ;

} matrix_t ;

// TODO constructors / destructors

int matrix_add   ( matrix_t*, matrix_t*, matrix_t* ) ;
int matrix_prod  ( matrix_t*, matrix_t*, matrix_t* ) ;
void matrix_eprod ( double, matrix_t*, matrix_t* ) ;

int matrix_add_   ( matrix_t*, matrix_t* ) ;
int matrix_prod_  ( matrix_t*, matrix_t* ) ;
void matrix_eprod ( double, matrix_t*, matrix_t* ) ;

// TODO eigenvalues
// TODO eigenvectors
// TODO SVD decomposition
// TODO LU decomposition

#endif

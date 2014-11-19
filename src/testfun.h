#include <math.h>

static int IntegrandTest(const int *ndim, const double xx[], const int *ncomp,
		double ff[], void *userdata) {

#define x xx[0]
#define y xx[1]
#define z xx[2]
#define a xx[3]
#define t xx[4]
#define v xx[5]
#define n xx[6]
#define q xx[7]
#define u xx[8]
//#define f ff[0]

//	ff[0] = 1/(3.75 - cos(M_PI*x) - cos(M_PI*y) - cos(M_PI*z));
	ff[0] = sin(x)*cos(y)*exp(z);

	return 0;
}

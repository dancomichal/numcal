#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <cuba.h>
#include <numcal_config.h>

#include "testfun.h"
#include "3loop_fun12.h"
#include "3loop_fun33.h"

//#define NDIM 10
#define NCOMP 1
#define USERDATA NULL
#define NVEC 1
//#define EPSREL 1e-7
//#define EPSABS 1e-7
#define LAST 4
#define MINEVAL 0
//#define MAXEVAL 1000000000

#define NSTART 100
#define NINCREASE 10000
#define NBATCH 1000
#define GRIDNO 0
#define STATEFILE NULL
#define SPIN NULL

#define NNEW 1000
#define FLATNESS 25.

#define KEY1 47
#define KEY2 1
#define KEY3 1
#define MAXPASS 5
#define BORDER 0.
#define MAXCHISQ 10.
#define MINDEVIATION .25
#define NGIVEN 0
//#define LDXGIVEN NDIM
#define NEXTRA 0

#define KEY 0


/* The current integrand */
integrand_t gIntergand = 0;

/* The name of this program. */
const char* program_name;

void help(FILE *stream, int exit_code) {

	fprintf(stream, "\n%s %d.%d.%d\n\n", program_name,
			numcal_VERSION_MAJOR, numcal_VERSION_MINOR ,numcal_VERSION_PATCH);
	fprintf(stream, "Usage options\n");
	fprintf(stream, "  -h --help          Display this information\n"
	        "  -v --verbose <num> Verbose level (default 0)\n"
			"  -f --fun <id>      Function id (default -1)\n"
			"  -s --seed <num>    Seed (default 0)\n"
			"  -c --calc <id>     Calculation method :\n"
			"                       0 : Vegas (default)\n"
			"                       1 : Suave\n"
			"                       2 : Divonne\n"
	        "                       3 : Cuhre\n"
			"  --ndim <num>       Num dimensions (default 10)\n"
			"  --maxeval <num>    Maxeal (default 1000000000)\n"
			"  --epsrel <num>     Epsrel (default 1e-7)\n"
			"  --epsabs <num>     Epsabs (default 1e-7)\n"
			"\n");

	exit(exit_code);
}

void SetIntegrand(int id) {
	switch (id) {
	case 1:
		gIntergand = (integrand_t) IntegrandTest;
		break;
	case 12:
		gIntergand = (integrand_t) Integrand_3loop_fun12;
		break;
	case 33:
		gIntergand = (integrand_t) Integrand_3loop_fun33;
		break;
	default:
		printf("Error : Integrand id=%d was not found !!!\n", id);
		help (stderr, 3);
		break;
	}
}

int main(int argc, char **argv) {

	int next_option;

	/* A string listing valid short options letters. */
	const char * const short_options = "hf:s:c:v:100";
	/* An array describing valid long options. */
	const struct option long_options[] = {
			{ "help", 0, NULL, 'h' },
			{ "fun" , 1, NULL, 'f' },
			{ "seed", 1, NULL, 's' },
			{ "calc", 1, NULL, 'c' },
			{ "verbose", 1, NULL, 'v' },
			{ "ndim", 1, NULL, 1000 },
			{ "maxeval", 1, NULL, 1001 },
			{ "epsrel", 1, NULL, 1002 },
			{ "epsabs", 1, NULL, 1003 },
			{ NULL, 0, NULL, 0 } };

	/* Setting program name */
	program_name = argv[0];

	int seed = 0;
	int fun_id = -1;
	int calc = 0;
	int verbose = 0;

	int ndim = 10;
	long int maxeval = 1e9;
	double epsrel = 1e-7;
	double epsabs = 1e-7;

	int ldxfiven = ndim;
	do {
		next_option = getopt_long(argc, argv, short_options, long_options,
				NULL);
		switch (next_option) {
		case 'h':
			help(stdout, 0);
			break;
		case 'f':
			fun_id = atoi(optarg);
			break;
		case 's':
			seed = atoi(optarg);
			break;
		case 'c':
			calc = atoi(optarg);
			break;
		case 'v':
			verbose = atoi(optarg);
			break;
		case 1000:
			ndim = atoi(optarg);
			ldxfiven = ndim;
			break;
		case 1001:
			maxeval = atol(optarg);
			break;
		case 1002:
			epsrel = atof(optarg);
			break;
		case 1003:
			epsabs = atof(optarg);
			break;
		case '?':
			/* The user specified an invalid option. */
			/* Print usage information to standard error, and exit with exit
			 code one (indicating abnormal termination). */
			help(stderr, 1);
			break;
		case -1:
			break;
			/* Done with options.
			 */
		default:
			/* Something else: unexpected.*/
			abort();

		}
	} while (next_option != -1);

	int comp, nregions, neval, fail;
	double integral[NCOMP], error[NCOMP], prob[NCOMP];

	if (verbose > 1) {
		printf("*** numcal parameters **********\n");
		printf("* fun     = %d\n", fun_id);
		printf("* seed    = %d\n", seed);
		printf("* calc    = %d\n", calc);
		printf("* ndim    = %d\n", ndim);
		printf("* maxeval = %ld\n", maxeval);
		printf("* epsrel  = %e\n", epsrel);
		printf("* epsabs  = %e\n", epsabs);
		printf("********************************\n");
	}


	SetIntegrand(fun_id);

	switch (calc) {
	case 0:
		printf("-------------------- Vegas test --------------------\n");
		Vegas(ndim, NCOMP, gIntergand, USERDATA, NVEC,
		epsrel, epsabs, verbose, seed,
		MINEVAL, maxeval, NSTART, NINCREASE, NBATCH,
		GRIDNO, STATEFILE, SPIN, &neval, &fail, integral, error, prob);
		printf("VEGAS RESULT:\tneval %d\tfail %d\n", neval, fail);
		for (comp = 0; comp < NCOMP; ++comp)
			printf("VEGAS RESULT:\t%.8f +- %.8f\tp = %.3f\n", integral[comp],
					error[comp], prob[comp]);
		break;
	case 1:
		printf("-------------------- Suave test --------------------\n");
		Suave(ndim, NCOMP, gIntergand, USERDATA, NVEC,
		epsrel, epsabs, verbose | LAST, seed,
		MINEVAL, maxeval, NNEW, FLATNESS,
		STATEFILE, SPIN, &nregions, &neval, &fail, integral, error, prob);

		printf("SUAVE RESULT:\tnregions %d\tneval %d\tfail %d\n", nregions,
				neval, fail);
		for (comp = 0; comp < NCOMP; ++comp)
			printf("SUAVE RESULT:\t%.8f +- %.8f\tp = %.3f\n", integral[comp],
					error[comp], prob[comp]);
		break;
	case 2:

		printf("\n------------------- Divonne test -------------------\n");

		Divonne(ndim, NCOMP, gIntergand, USERDATA, NVEC,
		epsrel, epsabs, verbose, seed,
		MINEVAL, maxeval, KEY1, KEY2, KEY3, MAXPASS,
		BORDER, MAXCHISQ, MINDEVIATION,
		NGIVEN, ldxfiven, NULL, NEXTRA, NULL,
		STATEFILE, SPIN, &nregions, &neval, &fail, integral, error, prob);

		printf("DIVONNE RESULT:\tnregions %d\tneval %d\tfail %d\n", nregions,
				neval, fail);
		for (comp = 0; comp < NCOMP; ++comp)
			printf("DIVONNE RESULT:\t%.8f +- %.8f\tp = %.3f\n", integral[comp],
					error[comp], prob[comp]);
		break;
	case 3:
		printf("\n-------------------- Cuhre test --------------------\n");

		Cuhre(ndim, NCOMP, gIntergand, USERDATA, NVEC,
		epsrel, epsabs, verbose | LAST,
		MINEVAL, maxeval, KEY,
		STATEFILE, SPIN, &nregions, &neval, &fail, integral, error, prob);

		printf("CUHRE RESULT:\tnregions %d\tneval %d\tfail %d\n", nregions,
				neval, fail);
		for (comp = 0; comp < NCOMP; ++comp)
			printf("CUHRE RESULT:\t%.8f +- %.8f\tp = %.3f\n", integral[comp],
					error[comp], prob[comp]);
		break;
	default:
		help(stderr, 2);
	}

	return EXIT_SUCCESS;
}

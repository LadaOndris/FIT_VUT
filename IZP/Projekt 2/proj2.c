#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <errno.h>

#define EPS 0.0000001    // the precision required in mypow function
#define SQRT_EPS 0.001   // the precision needed for sqrt function 

int perform_log(int argc, char *argv[], bool is_mylog);
int perform_pow(int argc, char *argv[], bool is_mypow);
int perform_mylog(int argc, char *argv[]);
int perform_mypow(int argc, char *argv[]);
double mylog(double x);
double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double mypow(double x, double y);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);
double general_pow(double x, double y, unsigned int n, double (*log_func)(double, unsigned int));
void calc_and_print_log(double x, unsigned int n, bool is_mylog);
void calc_and_print_pow(double x, double y, unsigned int n, bool is_mypow);
double check_log_input(double x);
double check_pow_input(double x, double y);

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Too few arguments.\n");
		return 1;
	}

	if (strcmp(argv[1], "--log") == 0) {
		return perform_log(argc, argv, false);
	} 
	else if (strcmp(argv[1], "--pow") == 0) {
		return perform_pow(argc, argv, false);
	}
	else if (strcmp(argv[1], "--mylog") == 0) {
		return perform_log(argc, argv, true);
	}
	else if (strcmp(argv[1], "--mypow") == 0) {
		return perform_pow(argc, argv, true);
	}
	else {
		printf("Unknown argument: %s\n", argv[1]);
		return 0;
	}
}

/*	Checks that the number passed is a positive number.
 *	Prints error message if it isn't and returns 1;
 */
int check_is_positive(double number, char *num_str, bool can_be_zero) {
	if (number < 0 || (!can_be_zero && number == 0)) {
		fprintf(stderr, "Negative number \"%s\" is not allowed.\n", num_str);
		return 1;
	}
	return 0;
}

/*
 * Parses arguments, performs the log operation.
 * Returns 1 if an error occurs, otherwise 0.
 */
int perform_log(int argc, char *argv[], bool is_mylog) {
	// Check number of arguments
	if ((is_mylog && argc != 3) || (!is_mylog && argc != 4)) {
		fprintf(stderr, "Argument count is invalid: missing or redundant arguments.\n");
		return 1;
	}
	// Parse arguments 
	char *end_ptr_x, *end_ptr_n = "";
	double x = strtod(argv[2], &end_ptr_x);
	int n = 1;
	if (!is_mylog) {
		n = strtol(argv[3], &end_ptr_n, 10);
	}
	// Check that parsing numbers finished successfully.
	if (errno == ERANGE) {
		fprintf(stderr, "Number si too big.\n");
		return 1;
	}
	if (*end_ptr_x != '\0' || *end_ptr_n != '\0') {
		fprintf(stderr, "Wrong argument.\n");
		return 1;
	}
	if (check_is_positive(n, argv[3], false)) {
		return 1;
	}

	calc_and_print_log(x, n, is_mylog);
	return 0;
}

/*
 * Parses arguments, performs the pow operation.
 * Returns 1 if an error occurs, otherwise 0.
 */
int perform_pow(int argc, char *argv[], bool is_mypow) {
	// Check number of arguments
	if ((is_mypow && argc != 4) || (!is_mypow && argc != 5)) {
		fprintf(stderr, "Argument count is invalid: missing or redundant arguments.\n");
		return 1;
	}
	// Parse arguments
	char *end_ptr_x, *end_ptr_y, *end_ptr_n = "";
	double x = strtod(argv[2], &end_ptr_x);
	double y = strtod(argv[3], &end_ptr_y);
	int n = 1;
	if (!is_mypow) {
		n = strtol(argv[4], &end_ptr_n, 10);
	}
	// Check that parsing numbers finished successfully.
	if (errno == ERANGE) {
		fprintf(stderr, "Number si too big.\n");
		return 1;
	}
	if (*end_ptr_x != '\0' || *end_ptr_y != '\0' || *end_ptr_n != '\0') {
		fprintf(stderr, "Wrong argument.\n");
		return 1;
	}
	if (check_is_positive(n, argv[4], false)) {
		return 1;
	}
	calc_and_print_pow(x, y, n, is_mypow);
	return 0;
}

void calc_and_print_log(double x, unsigned int n, bool is_mylog) {
	if (is_mylog) {
		printf("mylog(%g) = %.7e\n", x, mylog(x));
	}
	else {
		printf("       log(%g) = %.12g\n", x, log(x));
		printf(" cfrac_log(%g) = %.12g\n", x, cfrac_log(x, n));
		printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n));
	}
}


void calc_and_print_pow(double x, double y, unsigned int n, bool is_mypow) {
	if (is_mypow) {
		printf("mypow(%g, %g) = %.7e\n", x, y, mypow(x, y));
	}
	else {
		printf("         pow(%g,%g) = %.12g\n", x, y, pow(x, y));
		printf("  taylor_pow(%g,%g) = %.12g\n", x, y, taylor_pow(x, y, n));
		printf("taylorcf_pow(%g,%g) = %.12g\n", x, y, taylorcf_pow(x, y, n));
	}
}

/*
 * Calculates natural logarithm using taylor's series of 'x' with 'n' iterations.
 */
double taylor_log(double x, unsigned int n) {
	double return_code = check_log_input(x);
	if (return_code != 0)
		return return_code;
	double numerator = x > 1 ? (x - 1) / x : 1 - x;
	int sign = x > 1 ? 1 : -1;
	double power_of_numerator = numerator;
	double result = 0;

	for (unsigned int i = 1; i <= n; i++) {
		result += sign * power_of_numerator / i;
		power_of_numerator *= numerator;
	}
	return result;
}

double fa(double x, unsigned int n) {
	return n == 1 ? (2 * x) : ((n - 1) * (n - 1) * x * x);
}

/*
 * Calculates natural logarithm using continuous fractions 
 * of 'x' using 'n' iterations.
 */
double cfrac_log(double x, unsigned int n) {
	double return_code = check_log_input(x);
	if (return_code != 0)
		return return_code;
	double z = (x - 1) / (x + 1);
	double cf = 0;
	while (n >= 1) {
		cf = fa(z, n) / ((2 * n - 1) - cf);
		n--;
	}
	return cf;
}

/*
 * Calculates power of x to the y using n iterations and taylor's series.
 */
double taylor_pow(double x, double y, unsigned int n) {
	return general_pow(x, y, n, &taylor_log);
}

/*
 * Calculates power of x to the y using n iterations and continuous fractions.
 */
double taylorcf_pow(double x, double y, unsigned int n) {
	return general_pow(x, y, n, &cfrac_log);
}

/*
 * Calculates power of to y given the logarithm function.
 */
double general_pow(double x, double y, unsigned int n, double (*log_func)(double, unsigned int)) {
	double return_code = check_pow_input(x, y);
	if (return_code != -1)
		return return_code;
	
	double result = 1;
	double x_positive = x < 0 ? -x : x; 
	double ylnx = y * log_func(x_positive, n);
	double term = 1;

	for (unsigned int i = 2; i <= n; i++) {
		term *= ylnx / (i - 1);
		result += term;
	}
	return x < 0 && (int)y % 2 ? -result : result;
}

/*
 * Calculates square root of x using a series.
 */
double mysqrt(double x) {
	double y0;
	double y = 1;
	do  {
		y0 = y;
		y = 0.5 * (x / y + y);
	} while (fabs(y - y0) > SQRT_EPS);
	return y;
}

/*
 * Rounds num up.
 */
int myceil(float num) {
	int inum = (int)num;
	if (num == (float)inum) {
		return inum;
	}
	return inum + 1;
}

/*
 * Determins the number of needed iterations given the number 'z' for 
 * calculating the logarithm.
 */
int get_iters(double z) {
	double iters_prediction = 5 * mysqrt(z) - 0.14; 
	return  myceil(iters_prediction);
}

/*
 * Calculates logarithm of x.
 */
double mylog(double x) {
	double return_code = check_log_input(x);
	if (return_code != 0)
		return return_code;
	double z = x < 1 ? 1 / x : x;
	int iters = get_iters(z);
	double result = cfrac_log(z, iters);
	return z != x ? -result : result;	
}

/*
 * Checks the difference of results. Takes into account only significant digits.
 * If the difference is smaller than EPS, returns 1. Returns 0 if not.
 * Numbers such as 0.0011 and 0.0002 are changed to 1.1 and 0.2 and then they are compared.
 */
double check_pow_condition(double result, double result2) {
	double multiplier = 1;
	while ((result < 1 && result > 0) || (result > -1 && result < 0)) {
		multiplier *= 10;
		result *= 10;
	}
	while (result >= 10 || result <= -10) {
		multiplier /= 10;
		result /= 10;
	}
	result2 *= multiplier;
	return fabs(result - result2) > EPS;
}

/*
 * Calculates power of x to the y.
 */
double mypow(double x, double y) {
	double return_code = check_pow_input(x, y);
	if (return_code != -1)
		return return_code;
	double result = 1;
	double last_result = 1;
	double ylnx = y * mylog(x);
	double term = 1;
	unsigned int i = 2;

	do {
		last_result = result;
		term *= ylnx / (i - 1);
		result += term;
		i++;
	} while (check_pow_condition(result, last_result));
	return result;
}

/*
 * Checks an 'x' argument of the log functions.
 * Returns 0 if the argument is correct and special value if otherwise.
 */
double check_log_input(double x) {
	if (x < 0) {
		return NAN;
	}
	if (x == 0)
		return -INFINITY;
	if (isinf(x))
		return INFINITY;
	return 0;
}

/*
 * Checks 'x' and 'y' arguments of the pow functions.
 * Returns -1 if arguments are correct and special values if otherwise.
 */
double check_pow_input(double x, double y) {
	if (y == 0)
		return 1;
	if (x < 0) {
		if (y - (int)y) { // if y is fractional
			return -NAN;
		}	
	} 
	if (x == -INFINITY) {
		if (y < 0) {
			return (int)y % 2 ? 0 : -0;
		}
		else {
			return (int)y % 2 ? -INFINITY : INFINITY;
		}
	}
	if (x == 0) {
		if (y > 0)
			return 0;
	}
	if (x == INFINITY) {
		if (y < 0)
			return 0;
	}
	return -1;
}

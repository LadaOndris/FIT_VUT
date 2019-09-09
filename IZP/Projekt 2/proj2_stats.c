#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define EPS 0.0000001
#define SQRT_EPS 0.001

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
double general_pow(double y, unsigned int n, double ln);
void calc_and_print_log(double x, unsigned int n, bool is_mylog);
void calc_and_print_pow(double x, double y, unsigned int n, bool is_mypow);
//void calc_and_print_mylog(double x, double y);
//void calc_and_print_mypow(double x, double y);

void test_mylog();
int get_iters_needed(double number); 
void print_a_and_b(double number1, double number2); 
int get_iters(double x); 

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

void make_stats_of_cfrac() {
	printf("%5s %5s %5s %20s %20s %20s\n", "num", "cfra", "tayl", "cfrac_result", "taylor_result", "log_result");
//	FILE *fw = fopen("data0_1", "w");
	for (double i = 1; i <= 1000; i+= 20) {
		double log_res = log(i);
		
		int cfrac_iters = 0;
		double cfrac_res;
		do {
			cfrac_iters++;
			cfrac_res = cfrac_log(i, cfrac_iters);
		} while (fabs(cfrac_res - log_res) > EPS);
		
		int taylor_iters = 0;
		double taylor_res;
		do {
			taylor_iters++;
			taylor_res = taylor_log(i, taylor_iters);
		} while (fabs(taylor_res - log_res) > EPS);

		printf("%5g %5d %5d %20.12g %20.12g %20.12g\n", i, cfrac_iters, taylor_iters, cfrac_res, taylor_res, log_res);
//		fprintf(fw, "%5g;%5d;%5d\n", i, cfrac_iters, taylor_iters);
			
	}
//	fclose(fw);
}

void make_statistics(int n) {
	for (double i = 1000000; i <= 1000100; i++) {
		double log_res = log(i);
		double taylor = taylor_log(i, n);
		double cfrac = cfrac_log(i, n);

		char more_precise[10];
		if (fabs(taylor - log_res) > fabs(cfrac - log_res)) {
			strcpy(more_precise, "cfrac");
		} else if (fabs(taylor - log_res) < fabs(cfrac - log_res)) {
			strcpy(more_precise, "taylor");
		} else {
			strcpy(more_precise, "same");
		}

		printf("%.5g %20.12g %20.12g %20.12g %s\n", i, log_res, taylor, cfrac, more_precise);
	}
}

/*	Checks that the number passed is a positive number.
 *	Prints error message if it isn't and returns 1;
 *
 */
int check_is_positive(double number, char *num_str) {
	if (number <= 0) {
		fprintf(stderr, "Negative number \"%s\" is not allowed.\n", num_str);
		return 1;
	}
	return 0;
}

int perform_log(int argc, char *argv[], bool is_mylog) {
	if ((is_mylog && argc != 3) || (!is_mylog && argc != 4)) {
		fprintf(stderr, "Argument count is invalid: missing or redundant arguments.\n");
		return 1;
	}
	char *end_ptr_x, *end_ptr_n = "";
	double x = strtod(argv[2], &end_ptr_x);
	int n = 1;
	if (!is_mylog) {
		n = strtol(argv[3], &end_ptr_n, 10);
	}

	if (*end_ptr_x != '\0' || *end_ptr_n != '\0') {
		fprintf(stderr, "An argument is not a number.\n");
		return 1;
	}
	if (check_is_positive(x, argv[2]) || check_is_positive(n, argv[3])) {
		return 1;
	}
	make_stats_of_cfrac();
	calc_and_print_log(x, n, is_mylog);
	return 0;
}

int perform_pow(int argc, char *argv[], bool is_mypow) {
	if ((is_mypow && argc != 4) || (!is_mypow && argc != 5)) {
		fprintf(stderr, "Argument count is invalid: missing or redundant arguments.\n");
		return 1;
	}
	char *end_ptr_x, *end_ptr_y, *end_ptr_n = "";
	double x = strtod(argv[2], &end_ptr_x);
	double y = strtod(argv[3], &end_ptr_y);
	int n = 1;
	if (!is_mypow) {
		n = strtol(argv[4], &end_ptr_n, 10);
	}
	if (*end_ptr_x != '\0' || *end_ptr_y != '\0' || *end_ptr_n != '\0') {
		fprintf(stderr, "An argument is not a number.\n");
		return 1;
	}
	if (check_is_positive(x, argv[2]) || check_is_positive(n, argv[4])) {
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

double taylor_log(double x, unsigned int n) {
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

double cfrac_log(double x, unsigned int n) {
	double z = (x - 1) / (x + 1);
	double cf = 0;
	while (n >= 1) {
		cf = fa(z, n) / ((2 * n - 1) - cf);
		n--;
	}
	return cf;
}

double taylor_pow(double x, double y, unsigned int n) {
	return general_pow(y, n, taylor_log(x, n));
}

double taylorcf_pow(double x, double y, unsigned int n) {
	return general_pow(y, n, cfrac_log(x, n));
}

double general_pow(double y, unsigned int n, double ln) {
	double result = 1;
	double ylnx = y * ln;
	double term = 1;

	for (unsigned int i = 2; i <= n; i++) {
		term *= ylnx / (i - 1);
		result += term;
	}
	return result;
}

double mysqrt(double x) {
	double y0;
	double y = 1;
	do  {
		y0 = y;
		y = 0.5 * (x / y + y);
	} while (fabs(y - y0) > SQRT_EPS);
	return y;
}

int myceil(float num) {
	int inum = (int)num;
	if (num == (float)inum) {
		return inum;
	}
	return inum + 1;
}

double mylog(double x) {
	double z = x < 1 ? 1 / x : x;
	int iters = get_iters(z);
	double result = cfrac_log(z, iters);
	return z != x ? -result : result;	
}

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

double mypow(double x, double y) {
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

void test_mylog() {
	char mylog_resf[20], log_resf[20];
	int fucked_up = 0;
	//for (double i = 0.5; i < 1; i+=0.005) {
//	for (double i = 0.005; i <= 0.5; i+=0.005) {
//	for (int i = 2; i <= 200; i+=2) {
//
	for (int i = 1; i < 5000; i++) {
		sprintf(mylog_resf, "%.7e", mylog(i));
		sprintf(log_resf, "%.7e", log(i));
		if (strcmp(mylog_resf, log_resf) != 0) {
			printf(" Number: %d, Iters needed: %d, iters provided: %d, Mylog: %.7e Log: %.7e\n", i, get_iters_needed(i), get_iters(i), mylog(i), log(i));
			fucked_up++;
		}
//		if (i % 1000 == 0) {
//			printf("%d\n", i);
//		}	
	}

	printf("Total of fucked_up bitches: %d.\n", fucked_up);
}

int get_iters(double z) {
	double iters_prediction;
	if (z > 1) {
		iters_prediction = 5 * mysqrt(z) - 0.14;
	} 
	else if (z < 0.5) {
		iters_prediction = 4.5 / mysqrt(z);
	}	
	else {
		iters_prediction = 9.33 / mysqrt(z) - 7.57; 
	}
	return  myceil(iters_prediction);
}

int get_iters_needed(double number) {
	int iters_needed = 0;
	char cfrac_log_resf[20], log_resf[20];
	do{
		iters_needed++;
		sprintf(cfrac_log_resf, "%.7e", cfrac_log(number, iters_needed));
		sprintf(log_resf, "%.7e", log(number));
		//printf("%s %s\n", cfrac_log_resf, log_resf);
	} while (strcmp(cfrac_log_resf, log_resf) != 0);
	return iters_needed;		
}

void print_a_and_b(double number1, double number2) {
	double iters1 = get_iters_needed(number1);
	double iters2 = get_iters_needed(number2);

	printf("Iters1: %f, iters2: %f\n", iters1, iters2);

	double a = (iters1 - iters2) / (sqrt(number1) - sqrt(number2));
	double b = iters2 - a * sqrt(number2);

	printf("a: %.4g, b: %.4g\n", a, b);
} 






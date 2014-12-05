#ifndef errors_h
#define errors_h

#define VAR_SYSCALL_READ 	378
#define VAR_SYSCALL_WRITE 	379
#define ACT_ERRORS		0xFC0
#define NUM_ITER		0xFE0

void enable_errors(int x) {
	unsigned long long int err_status;
	err_status = x;
	syscall(VAR_SYSCALL_WRITE, ACT_ERRORS, &err_status);
}

void disable_errors() {
	unsigned long long int err_status;
	err_status = 0;
	syscall(VAR_SYSCALL_WRITE, ACT_ERRORS, &err_status);
}

unsigned int read_iterations() {
	unsigned long long int num_iter;
	syscall(VAR_SYSCALL_READ, NUM_ITER, &num_iter);
	return num_iter;
}

void clear_iterations() {
	unsigned long long int clear_iter;
	clear_iter = 0;
	syscall(VAR_SYSCALL_WRITE, NUM_ITER, &clear_iter);
}
#endif

/*
 * energy.h
 *
 *  Created on: Jan 14, 2013
 *      Author: salma
 */

#ifndef ENERGY_H_
#define ENERGY_H_

#define VAR_SYSCALL_READ 	378

#define TOTAL_CYCLES		0x500
#define TOTAL_ACT_ENERGY	0x540
#define TOTAL_SLP_ENERGY	0x580

typedef struct
{
	unsigned long long delta_cycles;
	unsigned long long delta_dyn;
	unsigned long long delta_slp;

} statistics;

typedef struct
{
	unsigned long long cycles;
	unsigned long long dyn;
	unsigned long long slp;
} data;

statistics st;
data prev;
data curr;

void start_cycle(){
	int r;
	r = syscall(VAR_SYSCALL_READ, TOTAL_ACT_ENERGY, &prev.dyn);
	r = syscall(VAR_SYSCALL_READ, TOTAL_SLP_ENERGY, &prev.slp);
	r = syscall(VAR_SYSCALL_READ, TOTAL_CYCLES, &prev.cycles);
}
void end_cycle(){
	int r;
	r = syscall(VAR_SYSCALL_READ, TOTAL_ACT_ENERGY, &curr.dyn);
	r = syscall(VAR_SYSCALL_READ, TOTAL_SLP_ENERGY, &curr.slp);
	r = syscall(VAR_SYSCALL_READ, TOTAL_CYCLES, &curr.cycles);
}
statistics get_energy(){

	st.delta_cycles = curr.cycles - prev.cycles;
	st.delta_dyn = curr.dyn - prev.dyn;
	st.delta_slp = curr.slp - prev.slp;

	return st;
}



//int get_energy() {
//	int nreg = 10;
//
//    unsigned int i, j;
//    unsigned long long int tempv = 0;
//	unsigned long long int v[nreg];
//	unsigned long long int prev[nreg];
//    int r;
//
//    int offset;
//
//    int interval = 1000000;
//
//    unsigned long long int cycles, prev_cycles, dyn, prev_dyn, slp, prev_slp;
//
//
//
//	r = syscall(VAR_SYSCALL, TOTAL_ACT_ENERGY, &dyn);
//	r = syscall(VAR_SYSCALL, TOTAL_SLP_ENERGY, &slp);
//	r = syscall(VAR_SYSCALL, TOTAL_CYCLES, &cycles);
//
//
// while (1) {
//
//        usleep(interval);
//
//		prev_cycles = cycles;
//		prev_dyn = dyn;
//		prev_slp = slp;
//
//		r = syscall(VAR_SYSCALL, TOTAL_ACT_ENERGY, &dyn);
//		r = syscall(VAR_SYSCALL, TOTAL_SLP_ENERGY, &slp);
//		r = syscall(VAR_SYSCALL, TOTAL_CYCLES, &cycles);
//
//		delta_cycles = cycles - prev_cycles;
//		delta_dyn = dyn - prev_dyn;
//		delta_slp = slp - prev_slp;
//
//		printf("dyn=%llu, slp=%llu, cycles=%llu\n", delta_dyn, delta_slp, delta_cycles);
//
//	}
//
//
//
//
//}



#endif /* ENERGY_H_ */

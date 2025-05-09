#include <interrupt.h>
#include <mpu.h>
#include <mpu_perms.h>
#include <printk.h>
#include <sysctrl.h>
#include <stacks.h>
#include <task.h>
extern unsigned int __ro_section_start[] __attribute__((weak)); //read only start
extern unsigned int __ro_section_end[] __attribute__((weak)); //ro end
extern unsigned int __data_start[] __attribute__((weak));//data start
extern unsigned int __periph_base[] __attribute__((weak)); //periph base

void mpu_setup_user(struct task_struct* proc) {
#if 1
//#	warning "Graduate students must implement this function"
//#	warning "otherwise change the 1 above to a 0"
#endif
	MPU.ctrl = 0; /* disable the MPU */
	/* set the region for the task being scheduled */
	mpu_set_region(0, proc->text_start, MPU_ATTRIB_UCODE);

	mpu_set_region(1, proc->data_start, MPU_ATTRIB_UDATA);

	/* start with .text then .data */
	/* enable the MPU again */
	 MPU.ctrl = (1u << 0);
}

void mpu_setup_supervisor(void) {
	/* supervisor has access to all of flash */
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	MPU.ctrl = 0; /* disable the MPU */
	/* set the region for the .text section of the supervisor to be all of the
	 * supervisor flash */
	

	mpu_set_region(0, __ro_section_start, MPU_ATTRIB_SCODE);

	/* the supervisor should have access to all of SRAM */
	mpu_set_region(1, __data_start, MPU_ATTRIB_SDATA);

	/* yes, technically we could do some SMEP/SMAP thing here, but that is
	 * overkill for this assignment :) */
	MPU.ctrl = (1u << 0);

}

void mpu_setup_periph(void) {
#if 0
#	warning "Graduate students must implement this function"
#	warning "otherwise change the 1 above to a 0"
#endif
	MPU.ctrl = 0; /* disable the MPU */

    mpu_set_region(2, &__periph_base, ATTRIB_PERIPH_AREA2);
	MPU.ctrl = (1u << 0);
/* all peripheral space should be only accessible to the supervisor */
}


void mpu_fault_enable(void) {
	SYSCTRL.shcsr |= MEMFAULTENA;
}

ISR(mpu_fault) {
	int pid = current->ppid;
	printk(	"\n\r[!] MPU access violation in pid %d\n\r"
			"    Relaunching task\n\r", pid);
	create_task(get_task_header(pid-1), pid-1);
	return_to_user(get_current_sp());
}

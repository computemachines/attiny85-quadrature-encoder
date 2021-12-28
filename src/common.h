#ifndef __COMMON_H__
#define __COMMON_H__

#define nop() __asm__ __volatile__("nop")

#ifdef __DEBUG__
#define BREAK() __asm__ __volatile__("break")
#else
#define BREAK()
#endif

#define STR_IMPL_(x) #x     //stringify argument
#define STR(x) STR_IMPL_(x) //indirection to expand argument macros

#define PULSE(PBn) __asm__ __volatile__("sbi %0," STR(PBn) "\n\t cbi %0," STR(PBn) "\n\t" ::"I"(_SFR_IO_ADDR(PORTB)))
#define TOGGLE(PBn) __asm__ __volatile__("sbi %0," STR(PBn)::"I"(_SFR_IO_ADDR(PINB)))
#define SET_IO(PBn) __asm__ __volatile__("sbi %0," STR(PBn) :: "I"(_SFR_IO_ADDR(PORTB)))
#define CLEAR_IO(PBn) __asm__ __volatile__("cbi %0," STR(PBn) :: "I"(_SFR_IO_ADDR(PORTB)))

#define SBI(bit, reg) __asm__ __volatile__("sbi %0," STR(bit) :: "I"(_SFR_IO_ADDR(reg)))
#define CBI(bit, reg) __asm__ __volatile__("cbi %0," STR(bit) :: "I"(_SFR_IO_ADDR(reg)))
#endif // __COMMON_H__

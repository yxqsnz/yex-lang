#ifndef YEX_H
typedef double yex_num_t;
typedef yex_num_t* yex_num_ptr_t;
typedef void* yex_args_t[];
typedef char*  yex_string_t;
yex_num_ptr_t yex_num(double);
yex_string_t yex_init_str(const char*);
#define YEX_H
#endif


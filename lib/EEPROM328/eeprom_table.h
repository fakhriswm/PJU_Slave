
#define uint8_len	1
#define uint16_len 	2
#define uint32_len	4
#define uint64_len	8

#define ee_size	512
#define null_terminator	1

#define ee_control           0
#define ee_control_len      uint8_len
#define ee_dimmer           ee_control + ee_control_len
#define ee_dimmer_len       uint8_len


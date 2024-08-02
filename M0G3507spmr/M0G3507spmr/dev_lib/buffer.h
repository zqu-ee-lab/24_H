/*
 * @Author: JAR_CHOW
 * @Date: 2024-05-14 20:47:46
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-01 06:57:21
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\buffer.h
 * @Description: 
 * 
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef buffer__
#define buffer__

#include <stdint.h>
#include <stdlib.h>

#define BUFF_MALLOC malloc
#define BUFF_FREE free

#define IS_FULL 1 + 0xFF
#define IS_EMPTY 2 + 0xFF

#define BUFFER_SIZE_U0 32
#define BUFFER_SIZE_U1 32
#define BUFFER_SIZE_U2 108
#define BUFFER_SIZE_U3 32
#define BUFFER_SIZE_U4 32
#define BUFFER_SIZE_U5 30

struct Buff
{
    uint8_t* Data;
    int size;
    void *head_p;
    void *end_p;
    void *write_p;
    void *read_p;
    int buffer_used;
};


// extern struct Buff BUFF;
extern struct Buff U3_buffer, U2_buffer, U0_buffer, U1_buffer;
void Iinitial_BUFF(struct Buff *BUFF, uint8_t size_);
void Write_BUFF_P(uint8_t num, struct Buff *BUFF);
void Write_BUFF(uint8_t *P, struct Buff *BUFF);
int Read_BUFF(struct Buff *BUFF);
uint8_t Find_Char(struct Buff *BUFF, char *p);
int BUFF_pop_by_Protocol(struct Buff *BUFF, const char* head, int head_len, void* data, int data_len);
int BUFF_pop_with_check_by_Protocol(struct Buff *BUFF, const char *head, int head_len, void *data, int data_size, int big_endian, int data_len);
int BUFF_find(struct Buff *BUFF, const char *ch, int len);
#endif

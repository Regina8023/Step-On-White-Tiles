#ifndef __MAIN_H__
#define __MAIN_H__

#define DATA_MEAN 5
#define SAME_LENGTH 50
#include "pixy.h"
#include "CMSIS/a2fxxxm3.h"
#include <time.h>
//width of column
#define width 96
//width of column line
#define col_width 5
#define res_width 640
#define res_length 480
#define longest_delay 500
#define heart_num 5
//0..9: col_width 10..19: col1 20..29: col2
static volatile int* col_addr1 = (int *) 0x40050000;
//0..9: col3 10..19: col4 20..29: col5
static volatile int* col_addr2 = (int *) 0x40050004;
//0..9: length of column: 480
static volatile int* col_addr3 = (int *) 0x40050038;

static volatile int* num_addr0 = (int *) 0x4005001c;
static volatile int* num_addr1 = (int *) 0x40050020;
static volatile int* num_addr2 = (int *) 0x40050028;
static int number[10] = {0x0f99999f, 0x04444444, 0x0f11f88f, 0x0f11f11f, 0x0aaaaf22, 0x0f88f11f, 0x0f88f99f, 0x0f111111, 0x0f99f99f, 0x0f99f11f};
int speed = -3;
sq_info sq[8];
bool dead = false;
typedef struct {
	volatile int* addr;
	int alive;
}health_info;

health_info health[5];
int get_col_pos(int i) {
	return (res_width / 2 + (i - 3) * width + 64);
}

void define_column() {
	//define five column lines
	*col_addr1 = ((col_width) | (get_col_pos(1) << 10) | (get_col_pos(2) << 20));
	*col_addr2 = (get_col_pos(3) | (get_col_pos(4) << 10) | (get_col_pos(5) << 20));
	*col_addr3 = res_length;
}
void sq_init() {
	int i;
	volatile int *addr[8] = {(int *)0x40050008, (int *)0x4005000c, (int *)0x40050010, (int *)0x40050014, (int *)0x40050018, (int *)0x4005002c, (int *)0x40050030, (int *)0x40050034};
	for (i = 0; i < 8; i++) {
		sq[i].length = 0;
		sq[i].actual_length = 0;
		sq[i].addr = addr[i];
		*sq[i].addr = 0;
		sq[i].left_on = 0;
		sq[i].right_on = 0;
		sq[i].delay = (rand() % longest_delay) + 1;
        }
}

void health_init() {
	volatile int *addr[5] = {(int *)0x4005003c, (int *)0x40050040, (int *)0x40050044, (int *)0x40050048, (int *)0x4005004c};
	int i;
	for (i = 0; i < heart_num; i++) {
		health[i].addr = addr[i];
		*addr[i] = 1;
		health[i].alive = 1;
	}
}

bool overlap(int k) {
	int i;
	for (i = 0; i < sq_num; i++)
		if (i != k && !sq[i].delay && sq[i].col == sq[k].col) {
			if (sq[i].top_y + sq[i].length > sq[k].top_y - 10)
				return true;
		}
	//not overlap with anyone
	return false;
}

void random_mode(int k) {
	volatile int *addr = sq[k].addr;
	int actual_length = sq[k].actual_length;
	int top_x = sq[k].top_x;
	int top_y = sq[k].top_y;
	int length = sq[k].length;
	if (sq[k].delay) {
		//square doesn't exist
		sq[k].delay--;
		if (!sq[k].delay) {
			//generate new square
			sq[k].actual_length = 50 + rand() % 100;
			length = 1;
			sq[k].col = (rand() % 4) + 1;
			top_x = get_col_pos(sq[k].col);
			top_y = res_length - 2;
			if (overlap(k))
				sq[k].delay = 10;
		}
	} else if (length < actual_length) {
		if (top_y == 0) {
			//at the bottom
			length += speed;
			if (length < 0) {
				if (sq[k].left_on == 0 && sq[k].right_on == 0) {
//					//miss tbe tile
					int i;
					bool found = false;
					for (i = heart_num - 1; i >= 0; i--)
						if (health[i].alive) {
							health[i].alive = 0;
							found = true;
							break;
						}
				}
				length = 0;
				sq[k].left_on = 0;
				sq[k].right_on = 0;
				sq[k].actual_length = 0;
				sq[k].delay = (rand() % longest_delay) + 1;
			}
		} else {
			//at the top
			top_y += speed;
			length -= speed;
		}
	} else {
		top_y += speed;
		if (top_y < 0) {
			length += top_y;
			top_y = 0;
		}
	}

	sq[k].top_x = top_x;
	sq[k].top_y = top_y;
	sq[k].length = length;
	*addr = (top_x | (top_y << 10) | (length << 20) | (sq[k].left_on << 30) | (sq[k].right_on << 31));
}

void set_score(int x) {
	*num_addr0 = number[x % 10];
	int y = x / 10;
	*num_addr1 = number[y % 10];
	*num_addr2 = number[y / 10];
}

void delay(int x) {
	int i;
	for (i = 0; i < x; i++);
}
void set_health() {
	int i;
	for (i = 0; i < heart_num; i++)
		*health[i].addr = health[i].alive;
}

void vga_init() {
	define_column();
	sq_init();
	dead = false;
	health_init();
    score = 0;
    set_score(score);
    set_health();
}



#endif

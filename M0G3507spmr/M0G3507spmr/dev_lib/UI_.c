/*
 * @Author: JAR_CHOW
 * @Date: 2024-05-06 18:52:10
 * @LastEditors: JAR_CHOW
 * @LastEditTime: 2024-08-02 10:58:59
 * @FilePath: \keilc:\Users\mrchow\Desktop\vscode_repo\M0G3507spmr\M0G3507spmr\dev_lib\UI_.c
 * @Description:
 *
 * Copyright (c) 2024 by jar_chou@qq.com, All Rights Reserved.
 */

#include "UI_.h"
#include "OLED.h"
#include "oled_buffer.h"
#include "string.h"
#include "oled_draw.h"
#include "APP_include.h"

/**
 * @brief the struct of the UI page
 * @param name the name of the page
 * @param last_page the previous page of the current page
 * @param item_list the list of the items of the page
 * @param item_num the number of the items of the page
 */
struct Page_UI_t
{
	char *name;
	struct Page_UI_t *last_page;
	struct Item_UI_t *item_list;
	int item_num;
} *current_page;

int current_item_index = 0;

/**
 * @brief the struct of the UI item
 * @param name the name of the item
 * @param func the callback function of the item
 * @param next_page the next page of the item
 * @param next the next item of the current item
 * @param prev the previous item of the current item
 */
struct Item_UI_t
{
	char *name;
	void (*func)(void);
	struct Page_UI_t *next_page;
	struct Item_UI_t *next;
	struct Item_UI_t *prev;
} *current_item;

/**
 * @brief initialize the UI
 * @param void
 * @return void
 * @note this function will return the UI the previous page, and the current item is the first item of the page
 */
void UI_back(void)
{
	if (current_page->last_page != NULL)
	{
		current_page = current_page->last_page;
		current_item = current_page->item_list;
		current_item_index = 0;
		UI_updata();
	}
}

/**
 * @brief move the cursor to the next item
 * @param void
 * @return void
 * @note this function will move the cursor to the next item, and only redraw the cursor
 */
void UI_next(void)
{
	// switch the cursor
	if (current_item->next != NULL)
	{
		DrawChar(current_item_index, 0, ' ');
		current_item = current_item->next;
		current_item_index++;
		DrawChar(current_item_index, 0, '>');
	}
}

/**
 * @brief switch to the previous item
 * @param void
 * @return void
 * @note this function will switch the cursor to the previous item, and only redraw the cursor
 */
void UI_prev(void)
{
	// switch the cursor
	if (current_item->prev != NULL)
	{
		DrawChar(current_item_index, 0, ' ');
		current_item = current_item->prev;
		current_item_index--;
		DrawChar(current_item_index, 0, '>');
	}
}

/**
 * @brief enter the UI item
 * @param void
 * @return void
 * @note this function will call the function which its callback function is, and switch to the next page if the item has next page
 */
void UI_enter(void)
{
	if (current_item->func != NULL)
	{
		current_item->func();
	}
	if (current_item->next_page != NULL)
	{
		current_page = current_item->next_page;
		current_item = current_page->item_list;
		current_item_index = 0;
		UI_updata();
	}
}

/**
 * @brief update the UI display
 * @param void
 * @return void
 * @note this function clear the screen buffer and redraw the UI
 */
void UI_updata(void)
{
	ClearScreenBuffer(0x00);
	// first column is the item that is selected
	DrawChar(current_item_index, 0, '>');
	DrawString(current_item_index, 2, current_page->item_list[current_item_index].name);
	// third column is the item that is not selected
	for (int i = 0; i < current_page->item_num; i++)
	{
		if (i != current_item_index)
		{
			DrawString(i, 2, current_page->item_list[i].name);
		}
	}
}

// the following is the custom coder space

/// @brief test function
struct Page_UI_t page1;
struct Page_UI_t page2;
struct Page_UI_t page3;

#include "my_task.h"
#include "APP_include.h"
#include "DEV_Grayscale.h"

void task_one_init(void)
{
	if (NULL != task)
	{
		return;
	}
	// task_one_init
	not_on_drak_line_flag = 1;
	task1_index = 0;
	task = task1;
}

void task_two_init(void)
{
	if (NULL != task)
	{
		return;
	}
	// task_two_init
	not_on_drak_line_flag = 1;
	task2_index = 0;
	task = task2;
}

void task_three_init(void)
{
	// task_three_init
	if (NULL != task)
	{
		return;
	}
	task3_index = 0;
	Aim_Angle = SPECIAL_ANGLE;
	task = task3;
}

void task_four_init(void)
{
	// task_four_init
	if (NULL != task)
	{
		return;
	}
	Aim_Angle = SPECIAL_ANGLE;
	task4_index = 0;
	task = task4;
}

void task_five_init(void)
{
	// turn off led1
	if (NULL != task)
	{
		return;
	}
	Aim_Angle = SPECIAL_ANGLE;
	task = task5;
	task5_index = 0;
}

void angle_tuning_init(void)
{
	// turn on led1
	if (NULL != task)
	{
		return;
	}
	task = turn_angle_tuning;
}

void test1(void)
{
	// 3 pages
	// first page
	page1.name = "page1";
	page1.last_page = NULL;
	page1.item_num = 2;
	page1.item_list = (struct Item_UI_t *)malloc(sizeof(struct Item_UI_t) * 2);

	page1.item_list[0].name = "choose_task";
	page1.item_list[0].func = NULL;
	page1.item_list[0].next_page = &page2;
	page1.item_list[0].next = &page1.item_list[1];
	page1.item_list[0].prev = NULL;

	page1.item_list[1].name = "PID_TUNING";
	page1.item_list[1].func = NULL;
	page1.item_list[1].next_page = &page3;
	page1.item_list[1].next = NULL;
	page1.item_list[1].prev = &page1.item_list[0];

	// second page
	page2.name = "page2";
	page2.last_page = &page1;
	page2.item_num = 4;
	page2.item_list = (struct Item_UI_t *)malloc(sizeof(struct Item_UI_t) * 4);

	page2.item_list[0].name = "task_one";
	page2.item_list[0].func = task_one_init;
	page2.item_list[0].next_page = NULL;
	page2.item_list[0].next = &page2.item_list[1];
	page2.item_list[0].prev = NULL;

	page2.item_list[1].name = "task_two";
	page2.item_list[1].func = task_two_init;
	page2.item_list[1].next_page = NULL;
	page2.item_list[1].next = &page2.item_list[2];
	page2.item_list[1].prev = &page2.item_list[0];

	page2.item_list[2].name = "task_three";
	page2.item_list[2].func = task_three_init;
	page2.item_list[2].next_page = NULL;
	page2.item_list[2].next = &page2.item_list[3];
	page2.item_list[2].prev = &page2.item_list[1];

	page2.item_list[3].name = "task_four";
	page2.item_list[3].func = task_four_init;
	page2.item_list[3].next_page = NULL;
	page2.item_list[3].next = NULL;
	page2.item_list[3].prev = &page2.item_list[2];

	// third page
	page3.name = "page3";
	page3.last_page = &page1;
	page3.item_num = 2;
	page3.item_list = (struct Item_UI_t *)malloc(sizeof(struct Item_UI_t) * 2);

	page3.item_list[0].name = "angle_tuning";
	page3.item_list[0].func = angle_tuning_init;
	page3.item_list[0].next_page = NULL;
	page3.item_list[0].next = &page3.item_list[1];
	page3.item_list[0].prev = NULL;

	page3.item_list[1].name = "task_five";
	page3.item_list[1].func = task_five_init;
	page3.item_list[1].next_page = NULL;
	page3.item_list[1].next = NULL;
	page3.item_list[1].prev = &page3.item_list[0];

	current_page = &page1;
	current_item = &page1.item_list[0];
}

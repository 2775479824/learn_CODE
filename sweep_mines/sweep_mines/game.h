#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define EASY_COUNT 10

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2


//函数声明

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set);

//打印棋盘
void DisplayBoard(char board[ROWS][COLS],int row, int col);

//布置雷
void SetMines(char board[ROWS][COLS], int row, int col);

//排查雷
void FindMines(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);
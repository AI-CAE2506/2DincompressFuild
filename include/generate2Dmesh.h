#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream> // ファイル操作に必要
#include <sstream> // std::ostringstream を使うために必要

#include "input.h"

struct CellInfo{
    double cellCenter_x;
    double cellCenter_y;
    double cellArea;
    int neighborIndex_N;
    int neighborIndex_E;
    int neighborIndex_S;
    int neighborIndex_W;
};

std::vector<CellInfo> generate2Dmesh(SimulationParameters input_param);

std::vector<double> calcPostionCenter(double mesh_size, int num_cells);

void printCellInfo(std::vector<CellInfo>& cells);

#include "generate2Dmesh.h"

std::vector<CellInfo> generate2Dmesh(SimulationParameters input_param){

    std::vector<CellInfo> cells;
    
    double meshSize_x = input_param.size_x / input_param.num_cells_x;
    double meshSize_y = input_param.size_y / input_param.num_cells_y;
    
    std::vector<double> position_node_center_x = calcPostionCenter(meshSize_x, input_param.num_cells_x);
    std::vector<double> position_node_center_y = calcPostionCenter(meshSize_y, input_param.num_cells_y);

    // 1次元化したインデックス
    int idx = 0;
    struct CellInfo cellTemporary;

    for (int i = 0; i < input_param.num_cells_x; i++){
        for (int j = 0; j < input_param.num_cells_y; j++){
            
            idx = i + j * input_param.num_cells_x; // 1次元化したインデックス

            cellTemporary.cellCenter_x = position_node_center_x[i];
            cellTemporary.cellCenter_y = position_node_center_y[j];
            cellTemporary.cellArea = meshSize_x * meshSize_y;
            
            // x方向の場合分け
            if (i == 0){
                cellTemporary.neighborIndex_W = -1; // x方向の左境界はWest=3
                cellTemporary.neighborIndex_E = idx + 1; // x方向の右indexはEast=1。常にidx+1
            
                if (j == 0){
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = -1; // y方向の下境界はSouth=2
                }

                else if (j == input_param.num_cells_y-1){
                    cellTemporary.neighborIndex_N = -1; // y方向の上境界はNorth=0
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y;
                }
                else{
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y; 
                }
            }

            else if (i == input_param.num_cells_x-1){
                cellTemporary.neighborIndex_W = idx - 1; //  x方向の左はWest=3。常にidx-1
                cellTemporary.neighborIndex_E = -1; // x方向の右境界はEast = 1
            
                if (j == 0){
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = -1; // y方向の下境界はSouth=2
                }

                else if (j == input_param.num_cells_y-1){
                    cellTemporary.neighborIndex_N = -1; // y方向の上境界はNorth=0
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y;
                }
                else{
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y; 
                }
            }   

            else {
                cellTemporary.neighborIndex_W = idx - 1; // x方向の左はWest=3。常にidx-1
                cellTemporary.neighborIndex_E = idx + 1; // x方向の右はEast=1。常にidx+1
            
                if (j == 0){
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = -1; // y方向の下境界はSouth=2
                }

                else if (j == input_param.num_cells_y-1){
                    cellTemporary.neighborIndex_N = -1; // y方向の上境界はNorth=0
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y;
                }
                else{
                    cellTemporary.neighborIndex_N = idx + input_param.num_cells_y; 
                    cellTemporary.neighborIndex_S = idx - input_param.num_cells_y; 
                }
            
            }

            cells.push_back(cellTemporary); // 構造体ベクトルに追加
        
        }
    }

    return cells;
    
    
}

std::vector<double> calcPostionCenter(double mesh_size, int num_cells){
    std::vector<double> position_node_center;

    // ノード中心の座標を計算して、position_node_centerに追加する。
    for( int i = 0; i < num_cells; i++) {
        if( i == 0){
            position_node_center.push_back(mesh_size/2);
        }
        // else if(i==num_cells){
        //     position_node_center.push_back(position_node_center[i-1]+mesh_size/2);
        // }
        else{
            position_node_center.push_back(position_node_center[i-1]+mesh_size);
        }
    }

    return position_node_center;

}


void printCellInfo(std::vector<CellInfo>& cells){

    std::string fileName = "inputReview.csv";

    std::ofstream outputFile;

    outputFile.open(fileName);
    if (!outputFile.is_open()) {
        std::cerr << "ファイルが開けません: " << fileName << std::endl;
        return ;
    }
    outputFile << std::fixed;
    outputFile << std::setprecision(3);
    // ヘッダー情報の出力。単一文字列として。
    outputFile << "cellCenter_x,cellCenter_y,cellArea,neighborIndex_N,neighborIndex_E,neighborIndex_S,neighborIndex_W\n";
    

    std::cout << std::fixed;
    std::cout << std::setprecision(3);

    // データ行の出力。ostringstreamの機能を使う。
    // 読み取り専用の参照渡しで構造体をループする。
    for(const auto& cell : cells){
        std::ostringstream oss;
        oss << cell.cellCenter_x << ","
            << cell.cellCenter_y << ","
            << cell.cellArea << ","
            << cell.neighborIndex_N << ","
            << cell.neighborIndex_E << ","
            << cell.neighborIndex_S << ","
            << cell.neighborIndex_W;

        outputFile << oss.str() << "\n";
        
    }

    outputFile.close();
    std::cout << "データの出力に成功しました。" << std::endl;

}

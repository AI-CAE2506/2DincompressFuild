#include "main.h"

int main(){
    std::string inputFileName = "./input.json";
    
    // インプットファイルから入力データを読み込む
    SimulationParameters input_params = readParametersFromJson(inputFileName);    

    // メッシュ情報の生成
    std::vector<CellInfo> cells = generate2Dmesh(input_params);

    // メッシュ情報の出力
    printCellInfo(cells);

    return 0;
}


#include "input.h"

// JSONファイルからパラメータを読み込む関数
SimulationParameters readParametersFromJson(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Error: Could not open JSON file: " + filename);
    }

    json data;
    ifs >> data; // ファイルの内容をJSONオブジェクトにパース

    SimulationParameters params;
    // JSONオブジェクトから値を取得
    // .at() を使うとキーが存在しない場合に例外が発生するので、安全です
    params.size_x = data.at("size_x").get<double>();
    params.size_y = data.at("size_y").get<double>();
    params.num_cells_x = data.at("num_cells_x").get<int>();
    params.num_cells_y = data.at("num_cells_y").get<int>();
    params.output_csv_filename = data.at("output_csv_filename").get<std::string>();

    return params;
}
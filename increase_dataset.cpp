#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <random>

Eigen::MatrixXd import_data(){
    std::string path = "labelled_data.csv";
    Eigen::MatrixXd data_set(19,5);
    std::string line;
    std::ifstream file(path);
    int row = 0;

    if (!file.is_open()){
        std::cerr << "file not open"; 
    }

    while (std::getline(file,line)){
        line += ','; 
        //std::cout << line;
        std::string tok = "";
        int col = 0;
        for (char c : line){
            if (c == ','){
                data_set(row,col) = std::stod(tok);
                col += 1;
                tok = "";
            } else {
                tok += c;
            }
        }
        row += 1;
    }

    return data_set;






} 


Eigen::MatrixXd create_more_data(std::function<Eigen::MatrixXd()> func){
    Eigen::MatrixXd me = func();
    Eigen::MatrixXd new_out(100,5);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> bathnbed(1,5);
    std::uniform_int_distribution<int> house(300,500);
    std::uniform_int_distribution<int> land(520,800);
    std::uniform_real_distribution<double> noise(1,1.5);

    for (int r = 0; r < me.rows(); r++){
        for (int c = 0; c < me.cols(); c++){
            new_out(r,c) = me(r,c);
        }
    }

    for (int r = me.rows(); r < 100; r++){
        std::vector<int> values = {bathnbed(gen),bathnbed(gen),land(gen),house(gen)};
        std::vector<int> weights = {15000,55000,800,850}; 
        double catcher = 0.0; 
        for (int c = 0; c < me.cols() -1; c++){
                catcher += values[c] * noise(gen) * weights[c]; 
                if (c != me.cols() - 1){
                    new_out(r,c) = values[c];
                } else {
                    new_out(r,c) = catcher;
                }
        }
        new_out(r,4) = catcher;

    }

    return new_out;
}


int main(){
    Eigen::MatrixXd more_data = create_more_data(import_data);
    //std::cout << more_data;
    std::stringstream mee;

    for (int r = 0; r < more_data.rows(); r++){
        for (int c = 0; c < more_data.cols(); c++){
            mee << std::to_string(more_data(r,c)) + ",";
        }   
        mee << "\n";
    }

    std::cout << mee.str();
    std::ofstream output_file("final_dataset.csv");
    output_file << mee.str();
    output_file.close();     
    

    return 0;
}

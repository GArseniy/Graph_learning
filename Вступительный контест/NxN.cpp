#include <iostream>
#include <string>


int main(){
    int n;
    int k;
    std::cin >> n >> k;
    int table[n*n] = {0};
    std::string request = "";
    for (int request_it=0; request_it < k; ++request_it){
        std::cin >> request;
        if (request == "ADD"){
            int x;
            int y;
            std::cin >> x >> y;
            ++table[x*n + y];
        }
        else if (request == "GET"){
            int x1, x2, y1, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            if (x1 >= x2){
                int tmp;
                tmp = x1;
                x1 = x2;
                x2 = tmp;
            }
            if (y1 >= y2){
                int tmp;
                tmp = y1;
                y1 = y2;
                y2 = tmp;
            }
            int sum = 0;
            for (int i=y1; i <= y2; ++i){ ///< +/- 1?
                for (int j=x1; j <= x2; ++j){
                    sum += table[i*n + j];
                }
            }
            std::cout << sum << std::endl;
        }
    }
    return 0;
}

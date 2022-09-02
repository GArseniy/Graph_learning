#include <iostream>


int main(){
    int N;
    int M;
    std::cin >> N >> M;
    int arr[N] = {0};
    for (int command_it=0; command_it < M; ++command_it){
        int request_type;
        std::cin >> request_type;
        if (request_type == 1){
            int L, R, S;
            std::cin >> L >> R >> S;
            for (int i=L; i < R; ++i)
                arr[i] += S;
        }
        else{
            int sum = 0;
            int L, R;
            std::cin >> L >> R;
            for (int i=L; i < R; ++i)
                sum += arr[i];
            std::cout << sum << std::endl;
        }
    }
    return 0;
}

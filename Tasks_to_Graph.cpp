/// Tasks


bool task_1(){
    AdjacencyMatrix_type AM = init_AM("cin");
    return (not(is_oriented_AM(AM)) and not(is_self_loop_in_AM(AM)));
}
bool task_2(){
    return is_self_loop_in_AM(init_AM("cin"));
}
int task_3(){
    return init_AM("cin").EdgesCount / 2;
}
int task_4(){
    return init_AM("cin").EdgesCount;
}
char* task_5(){
    return get_string_EL(make_EL_from_AM(init_AM("cin")));
}
char* task_6(){
    return get_string_AM(make_AM_from_EL(init_EL("cin")));
}
char* task_7(){
    return get_string_EL(make_EL_from_AM(init_AM("cin")));
}
char* task_8(){
    return get_string_AM(make_AM_from_EL(init_EL("cin")));
}
char* task_9(){
    return get_string_AL(reverse_oriented_AL(init_AL("cin")));
}
bool task_10(){
    return is_parallel_oriented_edges_EL(init_EL("cin"));
}
bool task_11(){
    return is_parallel_oriented_edges_EL(init_EL("cin"));
}
AdjacencyMatrix_type task_12(){
    AdjacencyMatrix_type AM = init_AM("cin");
    get_vertexes_degree_AM(AM);
    return AM;
}


/// Main


int main(void){
    task_12();
    return 0;
}

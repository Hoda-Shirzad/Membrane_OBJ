//
//  ECM.hpp
//  Mem
//
//  Created by Ali Farnudi on 18/08/2018.
//  Copyright © 2018 Ali Farnudi. All rights reserved.
//

#ifndef ECM_hpp
#define ECM_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "General_functions.hpp"

using namespace std;

class ECM {
private:
    
    int ECM_num_of_Nodes=0;
    int ECM_num_of_Triangle_Pairs=0;
    int ECM_num_of_Node_Pairs=0;
    int ECM_num_of_Triangles=0;
    
    
    double interaction_range=1.0;
    double epsilon=1.0;
    double sigma=10;
    
    
    vector<vector<double> >ECM_Node_Velocity;
    vector<vector<int> > ECM_Node_Pair_list;
    
    void read_ECM_input(string input_file);
    void read_gmesh_file (string gmesh_file);
    void ECM_Normal_direction_Identifier(double x, double y, double z);
    void ECM_Node_Pair_Identifier(void);
    
public:
    vector<vector<double> >ECM_Node_Force;
    vector<vector<double> >ECM_Node_Position;
    vector<vector<int> > ECM_triangle_list;
    
    
    string output_file_neme;
    
    
    ECM(string ECM_mesh_file_name, double x, double y, double z)
    {
//        read_ECM_input(input_file_name);
        read_gmesh_file(ECM_mesh_file_name);
        output_file_neme=ECM_mesh_file_name ;// it is for generating trajectory file. it can be modifyed to have date and time in it.this modification can be done in main.
        cout<<"\n\nECM class initiated"<<endl;
        ECM_Normal_direction_Identifier(x, y, z);
        ECM_Node_Pair_Identifier();
        
//        ECM_Triangle_Pair_and_Edges_Identifier();
        
        
        
    }
    int return_num_of_nodes(void){
        return ECM_num_of_Nodes;
    }
    int return_num_of_triangles(void){
        return ECM_num_of_Triangles;
    }
    double return_interaction_range(void){
        return interaction_range;
    }
    void set_interaction_range(double range){
        interaction_range=range;
    }
    double return_epsilon(void){
        return epsilon;
    }
    double return_sigma(void){
        return sigma;
    }
};

#endif /* ECM_hpp */

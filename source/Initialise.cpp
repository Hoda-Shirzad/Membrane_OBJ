//
//  Initialise.cpp
//  Membrae
//
//  Created by Ali Farnudi on 14/10/2018.
//  Copyright © 2018 Ali Farnudi. All rights reserved.
//

#include "Membrane.h"


void Membrane::initialise(string input_file_name , string Mesh_file_name){
    read_membrabe_input(input_file_name);
    read_gmesh_file(Mesh_file_name);
    output_file_neme=Mesh_file_name ;// it is for generating trajectory file. it can be modifyed to have date and time in it.this modification can be done in main.
    cout<<"Membrane class initiated"<<endl;
    Normal_direction_Identifier();
    Triangle_pair_counter();
    if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2)
    {cout<<"error! some triangles have less or more neighbour than 3"<<endl;}
    Triangle_Pair_and_Node_Bonds_Identifier();
}
void Membrane::initialise(string Mesh_file_name){
    read_gmesh_file(Mesh_file_name);
    output_file_neme=Mesh_file_name;
    cout<<"Membrane class initiated"<<endl;
    Normal_direction_Identifier();
    Triangle_pair_counter();
    if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2)
    {cout<<"error! some triangles have less or more neighbour than 3"<<endl;}
    Triangle_Pair_and_Node_Bonds_Identifier();
    cout<< "Average node distance is   "<<Average_Node_Distance()<<endl;
}
void Membrane::initialise(string Mesh_file_name, double x, double y, double z){
    cout<<"Initialising the Membrane Class..."<<endl;
    read_gmesh_file(Mesh_file_name);
    output_file_neme=Mesh_file_name;
    Radius= sqrt((Node_Position[0][0]-x)*(Node_Position[0][0]-x) + (Node_Position[0][1]-y)*(Node_Position[0][1]-y) + (Node_Position[0][2]-z)*(Node_Position[0][2]-z));
    cout<<"\n\nRadius="<<Radius<<endl;
    cout<<"\n\n# of Nodes="<<Num_of_Nodes<<endl;
    cout<<"# of triangles="<<Num_of_Triangles<<endl;
    Normal_direction_Identifier(x, y, z);
    Triangle_pair_counter();
    cout<<"# of triangle pairs="<<Num_of_Triangle_Pairs<<endl;
    if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2){
        cout<<"Warning! some triangles have less or more neighbour than 3"<<endl;
        
    }
    //        Triangle_Pair_and_Node_Bonds_Identifier();
    Node_Bonds_identifier();
    Node_neighbour_list_constructor();
    Triangle_pair_identifier();
    check();
    cout<<"\n\nMembrane class initiated.\n";
    //        cout<< "Average node distance is   "<<Average_Membrane_Node_Distance()<<endl;
}

#ifndef MEMBRANE_H
#define MEMBRANE_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "General_functions.hpp"

using namespace std;

class Membrane
{
    
public: //these are using in monte carlo flip function. for defining them as private variables, we have tow ways: defining monte_carlo_flip as a member of this class or writing some functions to make them accessible out of membrane class.
    
    double Node_Mass=1.0;//  also use in MD loop and should not be private unless we write some functions to get it outside the class
    double Total_Potential_Energy;
	double Radius=0;
    
    
    int membrane_counter;
    int Num_of_Node_Pairs; //??? (This variable should be defined and explained)
    int Num_of_Triangle_Pairs;
    
    
    string output_file_neme;
    
    
    vector<vector<double> >Node_Position;
    vector<vector<int> > Triangle_list;
    vector<vector<int> > Triangle_pair_list;
    //vector<vector<int> > Membrane_Node_Pair_list;
    vector<vector<int> > Node_Bond_list;// this variable is  the same as Membrane_Node_pair_list. I think  the name "Membrane_Edges" is less confusing. and also we fill it in a different way.
    vector<vector<int> > Triangle_Pair_Nodes;
    vector<vector<double> > Node_Velocity;// also update in MD loop and should not be private unless we write some functions to get it outside the class
    vector<vector<double> > Node_Force;// also update in MD loop and should not be private unless we write some functions to get it outside the class
    vector<vector<int> > Node_neighbour_list;
    
    
    void Triangle_Pair_and_Node_Bonds_Identifier(); //I guess this will use in MD loop and thus it should define as a public membere of class.
    //int Membrane_num_of_Node_Pair_Counter();// Hoda: no need to this function after modifying Membrane_Triangle_Pair_and_Edges_Identifier
    //void Membrane_num_of_Node_Pair_Counter_2();//Hoda: no need to this function after modifying Membrane_Triangle_Pair_and_Edges_Identifier
    void Elastic_Force_Calculator(double theta_0);
    void MD_Evolution_beginning ();
    void MD_Evolution_end ();
    void ConstantSurfaceForceLocalTriangles ();
    void Node_neighbour_list_constructor();
    void export_for_resume(char* buffer, int MD_step);
    void initialise(string input_file_name , string Mesh_file_name);
    void initialise(string Mesh_file_name);
    void initialise(string Mesh_file_name, double x, double y, double z);
    void import(string import_file_name);
    
//private: (if we define these constants as private members of the class, we can't put them in the final report)
    
    
    
    int **Normal_direction; //??? (These 2 elements should be defined and explained)
    int spring_model=2;
    
    double Total_Kinetic_Energy;
    double Total_potential_Energy=0.0;
    double Spring_coefficient=10.0; // streching constant
    double Bending_coefficient=10.0; // bending constant
    double Damping_coefficient=0.0; // Viscosity of the Mmmbrane. It is applied in Force calculation for the Membrane Node pairs. I have commented out these parts in the 'Membrane_Force_Calculator' because I think the current code does not need it (some energy consuming array calculations were invloved).
    double K_surfaceConstant_local=100.0;
    double Spring_force_cutt_off=10000.0;
    double ShiftinXdirection=0.0; //???
    double ShiftinZdirection=0.0; //???
    double Downward_speed=0.0; //???
    //bool =0;
    double com[3]; //center of mass
    double Min_node_pair_length, Max_node_pair_length, Average_node_pair_length;
    
    
    
    bool on_or_off_Spring_force_cutt_off=0; //??? I add it myself because virus should not have cut off
    
    
    private:
    /*variables*/
    int Num_of_Nodes;
    /*constants*/
    //This is the number of nodes on the membrane (Both the outer membrane and the Nucleus). This is the first number that appears in the 'membrane' file (once opend with a text editor)
    int Num_of_Triangles; //This is the number of triangles on the membrane (Both the outer membrane and the Nucleus). This is the number that appears in the 'membrane' file after the node position list is finished and before Gmesh lists the nodes that make a triangle.
    
    
    double Average_Node_Distance();
    void read_gmesh_file (string gmesh_file);
    void read_membrabe_input(string input_file);
    void Triangle_pair_counter ();
    void Normal_direction_Identifier();
    void Normal_direction_Identifier(double x, double y, double z);
    
    void potential_1 (void);
    void potential_2 (void);
    void Node_Bonds_identifier(void);
    void Triangle_pair_identifier(void);
    void Bending_potetial(void);
//    void Bending_potetial_2(void);
    void Bending_potetial_2(double theta_0);
    void check(void);
    
    
public:
    
//    Membrane(string input_file_name , string Mesh_file_name)
//    {
//        read_membrabe_input(input_file_name);
//        read_gmesh_file(Mesh_file_name);
//        output_file_neme=Mesh_file_name ;// it is for generating trajectory file. it can be modifyed to have date and time in it.this modification can be done in main.
//        cout<<"Membrane class initiated"<<endl;
//        Normal_direction_Identifier();
//        Triangle_pair_counter();
//        if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2)
//        {cout<<"error! some triangles have less or more neighbour than 3"<<endl;}
//        Triangle_Pair_and_Node_Bonds_Identifier();
//
//    }
//
//    Membrane(string Mesh_file_name)
//    {
//        read_gmesh_file(Mesh_file_name);
//        output_file_neme=Mesh_file_name;
//        cout<<"Membrane class initiated"<<endl;
//        Normal_direction_Identifier();
//        Triangle_pair_counter();
//        if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2)
//        {cout<<"error! some triangles have less or more neighbour than 3"<<endl;}
//        Triangle_Pair_and_Node_Bonds_Identifier();
//        cout<< "Average node distance is   "<<Average_Node_Distance()<<endl;
//    }
//
//    Membrane(string Mesh_file_name, double x, double y, double z)
//    {
//        cout<<"Initialising the Membrane Class..."<<endl;
//        read_gmesh_file(Mesh_file_name);
//        output_file_neme=Mesh_file_name;
//        Radius= sqrt((Node_Position[0][0]-x)*(Node_Position[0][0]-x) + (Node_Position[0][1]-y)*(Node_Position[0][1]-y) + (Node_Position[0][2]-z)*(Node_Position[0][2]-z));
//        cout<<"\n\nRadius="<<Radius<<endl;
//        cout<<"\n\n# of Nodes="<<Num_of_Nodes<<endl;
//        cout<<"# of triangles="<<Num_of_Triangles<<endl;
//        Normal_direction_Identifier(x, y, z);
//        Triangle_pair_counter();
//        cout<<"# of triangle pairs="<<Num_of_Triangle_Pairs<<endl;
//        if (Num_of_Triangle_Pairs != 3*(Triangle_list.size())/2){
//            cout<<"Warning! some triangles have less or more neighbour than 3"<<endl;
//
//        }
////        Triangle_Pair_and_Node_Bonds_Identifier();
//        Node_Bonds_identifier();
//        Node_neighbour_list_constructor();
//        Triangle_pair_identifier();
//        check();
//        cout<<"\n\nMembrane class initiated.\n";
////        cout<< "Average node distance is   "<<Average_Membrane_Node_Distance()<<endl;
//    }
//    Membrane(string import_file_name, bool resume)
//    {
//        cout<<"Importing the Membrane from the resume file:"<<endl;
//        cout<<import_file_name<<endl<<endl;
//        ifstream read_resume_file;
//
//        read_resume_file.open(import_file_name.c_str());
//        int temp;
//        read_resume_file>>temp;
//        cout<<"Resuming the MD from step "<<temp<<endl;
//
//        read_resume_file>>Num_of_Nodes;
//        cout<<"Number of Nodes: "<<Num_of_Nodes<<endl;
//        for (int i=0; i<Num_of_Nodes; i++) {
//            read_resume_file>>Node_Position[i][0]>>Node_Position[i][1]>>Node_Position[i][2];
//            read_resume_file>>Node_Velocity[i][0]>>Node_Velocity[i][1]>>Node_Velocity[i][2];
//            Node_Force[i][0]=0;
//            Node_Force[i][1]=0;
//            Node_Force[i][2]=0;
//        }
//        cout<<"Coordinates and velocities loaded"<<endl;
//        cout<<"Node forces set to zero"<<endl;
//
//        read_resume_file>>Num_of_Triangles;
//        cout<<"Number of Triangles: "<<Num_of_Triangles<<endl;
//        for (int i=0; i<Num_of_Triangles; i++) {
//            read_resume_file>>Triangle_list[i][0]>>Triangle_list[i][1]>>Triangle_list[i][2];
//        }
//
//        read_resume_file>>Num_of_Node_Pairs;
//        cout<<"Number of Node Pairs: "<<Num_of_Node_Pairs<<endl;
//        for (int i=0; i<Num_of_Node_Pairs; i++) {
//            read_resume_file>>Node_Bond_list[i][0]>>Node_Bond_list[i][1];
//        }
//        //In the import function we should call the neighbour list constructor
//        read_resume_file>>Num_of_Triangle_Pairs;
//        cout<<"Number of Triangle Pairs: "<<Num_of_Triangle_Pairs<<endl;
//        for (int i=0; i<Num_of_Triangle_Pairs; i++) {
//            read_resume_file>>Triangle_pair_list[i][0]>>Triangle_pair_list[i][1];
//            read_resume_file>>Triangle_Pair_Nodes[i][0]>>Triangle_Pair_Nodes[i][1]>>Triangle_Pair_Nodes[i][2]>>Triangle_Pair_Nodes[i][3];
//        }
//
//        Node_neighbour_list_constructor();
//        read_resume_file>>Max_node_pair_length>>Min_node_pair_length>>Average_node_pair_length;
//        cout<<"Spring coefficients:"<<endl;
//        cout<<"Max="<<Max_node_pair_length<<"\tmin="<<Min_node_pair_length<<"\tAverage="<<Average_node_pair_length<<endl;
//        cout<<"\n\nMembrane class initiated.\n";
//        //        cout<< "Average node distance is   "<<Average_Membrane_Node_Distance()<<endl;
//    }
    
    
    
    int return_num_of_nodes(void){
        return Num_of_Nodes;
    }
    void shift_position (double x, double y, double z){
        for (int i=0; i<Num_of_Nodes; i++) {
            Node_Position[i][0]+=x;
            Node_Position[i][1]+=y;
            Node_Position[i][2]+=z;
        }
    }
    void shift_velocity (double vx, double vy, double vz){
        for (int i=0; i<Num_of_Nodes; i++) {
            Node_Velocity[i][0]+=vx;
            Node_Velocity[i][1]+=vy;
            Node_Velocity[i][2]+=vz;
        }
    }
    int return_num_of_triangle(){
        return Num_of_Triangles;
    }
    void calculate_average_force(void){
        double average_force_x=0, average_force_y=0, average_force_z=0;
        for(int j=0 ; j<Num_of_Nodes ; j++){
            average_force_x+=Node_Force[j][0];
            average_force_y+=Node_Force[j][1];
            average_force_z+=Node_Force[j][2];
            
        }
        cout<<"\n\naverage_force_x="<<average_force_x/Num_of_Nodes<<"\naverage_force_y="<<average_force_y/Num_of_Nodes<<"\naverage_force_z="<<average_force_z/Num_of_Nodes<<endl;
    }
};

#endif // MEMBRANE_H


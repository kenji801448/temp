#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#define INPUT_FILE_PATH "input"
#define OUTPUT_FILE_PATH "output"

typedef struct node* node_link;
struct node {

    double data;
    node_link next;
};

typedef struct h_node* h_node_link;
struct h_node {

    int n;
    double sum, avg, sd;
    node_link data; //for data array
    h_node_link next;

    void init() {
        //clean the buffer with empty stream
        this->buffer = std::stringstream();
        //reset sum
        this->sum = 0;
    }

    void calculate() {
        //recalculate
        init();

        //deal with summation
        for (node_link current = this->data; current; current = current->next) {
            this->sum += current->data;
        }

        this->avg = this->sum/this->n;

        //deal with standard deviation
        for (node_link current = this->data; current; current = current->next) {
            this->sd += pow(current->data - this->avg, 2);
        }
        this->sd /= this->n - 1;
        this->sd = sqrt(this->sd);
    }

    std::string toString() {

        std::stringstream buffer;

        buffer << "data:";
        //push data into string stream
        for (node_link current = this->data; current; current = current->next) {
            buffer << " " << current->data;
        }
        buffer << std::endl;

        buffer << "sum = " << this->sum << std::endl;
        buffer << "avg = " << this->avg << std::endl;
        buffer << "sd = " << this->sd << std::endl << std::endl;
        return buffer.str();
    }
};

int main() {
    //ifstream for input stream
    std::ifstream fi;
    fi.open(INPUT_FILE_PATH);

    //define file head as h_node
    h_node_link file_head = new h_node();
    fi >> file_head->n;

    h_node_link column_tail = file_head;

    //two dimensional linked list construction
    for (int i = 0; i < file_head->n; i++) {
        //the head node of each row
        h_node_link new_head_node = new h_node();
        fi >> new_head_node->n;

        //the tail node of row list
        node_link row_tail;

        for (int j = 0; j < new_head_node->n; j++) {
            node_link new_node = new node();
            fi >> new_node->data;
            if (j == 0) {
                new_head_node->data = new_node;
            } else {
                row_tail->next = new_node;
            }
            row_tail = new_node;
        }
        new_head_node->calculate();

        column_tail->next = new_head_node;
        column_tail = new_head_node;
    }
    //close input file stream
    fi.close();

    //ofstream for output stream
    std::ofstream fo;
    fo.open(OUTPUT_FILE_PATH);

    //output entire two dimensional linked list
    int counter = 0;
    for (h_node_link current = file_head->next; current; current = current->next) {
        fo << "[" << ++counter << "]\n";
        fo << current->toString();
    }

    //close output file stream
    fo.close();
}

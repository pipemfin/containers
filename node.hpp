//
// Created by Johnna Jerrod on 5/8/22.
//

#ifndef NODE_HPP
#define NODE_HPP


struct node {
    value_type      data;
    bool            isRed;
    node            *left;
    node            *right;
    node            *parent;
    node()
};


#endif //CONTAINERS_NODE_HPP

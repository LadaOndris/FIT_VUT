//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Ladislav Ondris <xondri07@stud.fit.vutbr.cz>
// $Date:       $2019-02-19
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Ladislav Ondris
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include <utility>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class NonEmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
    
    virtual void SetUp() {
        for(int i = 0; i < valuesCount; ++i)
            tree.InsertNode(values[i]);
    }
    
    int valuesCount = 14;
    int values[14] = { 10, 85, 15, 70, -20, -60, 30, 50, 65, -80, -90, 40, 5, 55 };
};

class EmptyTree: public ::testing::Test
{
protected:
    BinaryTree tree;
};


class TreeAxioms: public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
        
        for(int i = 0; i < 14; ++i)
            tree.InsertNode(values[i]);
    }
    
    BinaryTree tree;
};

// Testing an empty tree

TEST_F(EmptyTree, InsertNode_InsertExistingNode)
{
    ASSERT_TRUE(tree.GetRoot() == NULL);
    
    // check nodes count before inserting nodes
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 0);

    // add new node
    std::pair<bool, BinaryTree::Node_t *> pair = tree.InsertNode(0);
    EXPECT_TRUE(pair.first);
    EXPECT_TRUE(pair.second != NULL);

    // check nodes count
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 1);

    // add an already existing node
    std::pair<bool, BinaryTree::Node_t *> pair2 = tree.InsertNode(0);
    EXPECT_FALSE(pair2.first);
    EXPECT_EQ(pair.second, pair2.second);

    // check nodes count
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 1);

    ASSERT_EQ(tree.GetRoot()->key, 0);
}

TEST_F(EmptyTree, InsertNode_Insert4NonExistingNodes)
{
    // insert first node
    std::pair<bool, BinaryTree::Node_t *> pair = tree.InsertNode(1);
    
    // Check state of the first node
    EXPECT_EQ(tree.GetRoot()->key, 1);
    EXPECT_TRUE(tree.GetRoot()->pParent == NULL);
    EXPECT_TRUE(tree.GetRoot()->pLeft != NULL);
    EXPECT_TRUE(tree.GetRoot()->pRight != NULL);
    EXPECT_EQ(tree.GetRoot()->color, BinaryTree::Color_t::BLACK);
    
    // Check state of the left leaf
    EXPECT_TRUE(tree.GetRoot()->pLeft->pParent == tree.GetRoot());
    EXPECT_TRUE(tree.GetRoot()->pLeft->pLeft == NULL);
    EXPECT_TRUE(tree.GetRoot()->pLeft->pRight == NULL);
    EXPECT_EQ(tree.GetRoot()->pLeft->color, BinaryTree::Color_t::BLACK);
    
    // Check state of the right leaf
    EXPECT_TRUE(tree.GetRoot()->pRight->pParent == tree.GetRoot());
    EXPECT_TRUE(tree.GetRoot()->pRight->pLeft == NULL);
    EXPECT_TRUE(tree.GetRoot()->pRight->pRight == NULL);
    EXPECT_EQ(tree.GetRoot()->pRight->color, BinaryTree::Color_t::BLACK);

    // insert second node
    std::pair<bool, BinaryTree::Node_t *> pair2 = tree.InsertNode(5);
    
    // Check state of the second node
    EXPECT_EQ(pair2.second->key, 5);
    EXPECT_TRUE(pair2.second->pParent == tree.GetRoot());
    EXPECT_TRUE(pair2.second->pLeft != NULL);
    EXPECT_TRUE(pair2.second->pRight != NULL);
    EXPECT_EQ(pair2.second->color, BinaryTree::Color_t::RED);
    
    // check state of the root after adding the second node
    EXPECT_EQ(tree.GetRoot()->pRight->key, 5);
    
    // add another nodes
    std::pair<bool, BinaryTree::Node_t *> pair3 = tree.InsertNode(2);
    std::pair<bool, BinaryTree::Node_t *> pair4 = tree.InsertNode(7);
    EXPECT_TRUE(pair.first);
    EXPECT_TRUE(pair2.first);
    EXPECT_TRUE(pair3.first);
    EXPECT_TRUE(pair4.first);
    
    // check nodes count
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 4);
    
    // check root state
    EXPECT_EQ(tree.GetRoot()->key, 2);
    EXPECT_TRUE(tree.GetRoot()->pParent == NULL);
    ASSERT_TRUE(tree.GetRoot()->pLeft != NULL);
    EXPECT_EQ(tree.GetRoot()->pLeft->key, 1);
    ASSERT_TRUE(tree.GetRoot()->pRight != NULL);
    EXPECT_EQ(tree.GetRoot()->pRight->key, 5);
    EXPECT_EQ(tree.GetRoot()->color, BinaryTree::Color_t::BLACK);
}

TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(546));
    EXPECT_FALSE(tree.DeleteNode(1));
    EXPECT_FALSE(tree.DeleteNode(0));
    EXPECT_FALSE(tree.DeleteNode(-1));
    EXPECT_FALSE(tree.DeleteNode(-546));
}

TEST_F(EmptyTree, FindNode)
{
    EXPECT_TRUE(tree.FindNode(0) == NULL);
    EXPECT_TRUE(tree.FindNode(-10) == NULL);
    EXPECT_TRUE(tree.FindNode(7) == NULL);
}


// Testing a non empty tree

TEST_F(NonEmptyTree, InsertNode_InsertExistingNode)
{
    // try to insert existing node
    std::pair<bool, BinaryTree::Node_t *> pair = tree.InsertNode(10);
    EXPECT_FALSE(pair.first);
    EXPECT_TRUE(pair.second != NULL);

    // check nodes count
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 14);
}

TEST_F(NonEmptyTree, InsertNode_InsertNonExistingNode)
{
    // insert non existing node
    std::pair<bool, BinaryTree::Node_t *> pair = tree.InsertNode(25);
    EXPECT_TRUE(pair.first);
    EXPECT_TRUE(pair.second != NULL);
    
    // check nodes count
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 15);
}

TEST_F(NonEmptyTree, DeleteNode)
{
    // delete non existing node
    EXPECT_FALSE(tree.DeleteNode(0));
    
    // delete all nodes
    for(int i = 0; i < valuesCount; ++i) {
        EXPECT_TRUE(tree.DeleteNode(values[i]));
    }
    
    // delete already deleted node
    EXPECT_FALSE(tree.DeleteNode(10));
    
    // check nodes count
    std::vector<BinaryTree::Node_t *> nodes;
    tree.GetNonLeafNodes(nodes);
    EXPECT_EQ(nodes.size(), 0);
    
    EXPECT_TRUE(tree.GetRoot() == NULL);
}

TEST_F(NonEmptyTree, FindNode)
{
    // find non existing node
    BinaryTree::Node_t *node = tree.FindNode(0);
    EXPECT_TRUE(node == NULL);

    // find existing node
    node = tree.FindNode(50);
    EXPECT_TRUE(node != NULL);
}


// Testing axioms

// All leaf nodes should be black.
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    int leafCount = leafNodes.size();
    for (int i = 0; i < leafCount; i++) {
        EXPECT_EQ(leafNodes[i]->color, BinaryTree::Color_t::BLACK);
    }
    
}

// If a node is red, then both of his children are black.
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> nonLeafNodes;
    tree.GetNonLeafNodes(nonLeafNodes);
    
    for (BinaryTree::Node_t *node : nonLeafNodes) {
        if (node->color == BinaryTree::Color_t::RED) {
            EXPECT_EQ(node->pLeft->color, BinaryTree::Color_t::BLACK);
            EXPECT_EQ(node->pRight->color, BinaryTree::Color_t::BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3)
{
    int last_black_nodes_count = -1;
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    
    // iterate through all leaf nodes
    for (BinaryTree::Node_t *node : leafNodes) {
        // count the number of black nodes in path to the root
        int black_nodes_count = 0;
        BinaryTree::Node_t *current_node = node->pParent;
        while (current_node != tree.GetRoot()) {
            if (current_node->color == BinaryTree::Color_t::BLACK) {
                black_nodes_count++;
            }
            current_node = current_node->pParent;
        }
        if (last_black_nodes_count == -1) {
            last_black_nodes_count = black_nodes_count;
        }
        else {
            ASSERT_EQ(last_black_nodes_count, black_nodes_count);
        }
    }
}

/*** Konec souboru black_box_tests.cpp ***/

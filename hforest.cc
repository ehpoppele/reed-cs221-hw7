/*
 * HForest: a class to represent a collection of HTrees, each with an
 * associated value (inverse priority).
 * Implemented using the STL's make_heap.
 */

#include <algorithm>
#include "hforest.hh"
#include <algorithm>
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
// Comparator function for std::*_heap
static bool compare_trees(HForest::tree_t t1, HForest::tree_t t2)
{
    return t1->get_value() > t2->get_value();
}
static bool min_tree(HForest::tree_t t1, HForest::tree_t t2) {
    // if(t1 -> get_value() == t2 -> get_value()) {
    //     return t1 -> get_key() < t2 -> get_key();
    // }
    return t1 -> get_value() < t2 -> get_value();
}
//////////////////////////////////////////////////////////////////////////////
// Add a single tree to the forest:
void
HForest::add_tree(tree_t tree)
{
    trees_.push_back(tree);
    std::push_heap(trees_.begin(), trees_.end(), min_tree);
}

//////////////////////////////////////////////////////////////////////////////
// Return the tree with the highest frequency count (and remove it from forest)
HForest::tree_t
HForest::pop_top()
{
    if (trees_.empty()) {
        return nullptr;
    }
    std::pop_heap(trees_.begin(), trees_.end(), compare_trees);
    auto ret = trees_.back();
    trees_.pop_back();
    return ret;
}
HForest::tree_t HForest::get_min() {
    if (trees_.empty()) {
        return nullptr;
    }
    std::pop_heap(trees_.begin(), trees_.end(), min_tree);
    auto ret = trees_.back();
    trees_.pop_back();

    // make sure that the min is actually removed from the trees
    // std::find takes the endpoints of the part to search and the thing to search for
    // it requires <algorithm>
    // returns last if no match is found
    if(std::find(trees_.begin(), trees_.end(), ret) != trees_.end()) {
        assert(false);
    }


    return ret;
    // if (trees_.empty()) {
    // return nullptr;
    // }
    // std::make_heap(trees_.begin(), trees_.end(), min_tree);
    // auto ret = trees_.back();
    // trees_.pop_back();
    // std::make_heap(trees_.begin(), trees_.end(), compare_trees);
    // return ret;

    // std::sort(trees_.begin(), trees_.end());

    // std::sort(trees_.begin(), trees_.end(), min_tree);
    //
    // // sorts trees in ascending order using <
    // std::reverse(trees_.begin(), trees_.end());
    // //reverses the order
    // //trees_ is now in descending order - smallest is at the back
    // auto ret = trees_.back();
    // trees_.pop_back();
    // assert(ret != nullptr);
    // return ret;
}
//////////////////////////////////////////////////////////////////////////////
// allows direct access to trees for testing purposes
// will be removed before release
std::vector<HTree::tree_ptr_t> HForest::get_trees() {
    return HForest::trees_;
}

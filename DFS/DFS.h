//===_____ DFS.h - Depth First Search on a Control Flow Graph ___c++_____===//
//
//          Compilers Laboratoy at Federal University of Minas Gerais
//
//===____________________________________________________________________===//
/// Author: Roberto Rosmaninho
/// Last change: 07/11/19
///
/// This file contains the declaration of Depth First Control class which give
/// us the DFS on a CFG of a given function.
//===____________________________________________________________________===//

#ifndef DFS_H
#define DFS_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"

#include <map>
#include <stack>
#include <queue>

using namespace llvm;

class DepthFirstSearch : public FunctionPass{
  private:
    unsigned _vertices;
    std::stack<BasicBlock*> _list;
    std::map<BasicBlock*, bool> _visited;
    std::queue<BasicBlock*> _path;

  public:
    void reset_visited(Function &F);
    bool has_visited(BasicBlock* BB);
    void addBasicBlock(BasicBlock* BB);
    std::queue<BasicBlock*> get_DFS(); //return the DFS

    void dump(); //Print the names of basicblocks on DFS path
    void clear();

    static char ID;
    DepthFirstSearch() : FunctionPass(ID){}
    void getAnalysisUsage(AnalysisUsage &AU) const;
    virtual bool runOnFunction(Function &F);
};
#endif

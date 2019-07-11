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

#include "DFS.h"

void DepthFirstSearch::getAnalysisUsage(AnalysisUsage &AU) const{
  AU.setPreservesAll();
}


void DepthFirstSearch::reset_visited(Function &F){
  for(BasicBlock &BB : F)
    _visited.insert(std::pair<BasicBlock*, bool>(&BB, false));
}

bool DepthFirstSearch::has_visited(BasicBlock* BB){
 auto it = _visited.find(BB);
 return it->second;
}

void DepthFirstSearch::addBasicBlock(BasicBlock* BB){
  if(!has_visited(BB)){
    _list.push(BB);
    _path.push(BB);
    _visited[BB] = true;
  }
}

void DepthFirstSearch::clear(){
  while(!_list.empty())
    _list.pop();
  while(!_path.empty())
    _path.pop();
  _visited.erase (_visited.begin(), _visited.end()); 
}

void DepthFirstSearch::dump(){
  std::queue<BasicBlock*> aux = _path;
  errs() << "Printing The Path of DFS:\n";
  for(unsigned i = 0; i < _path.size(); i++){
    BasicBlock* BB = aux.front();
    errs() << BB->getName() << "\n";
    aux.pop();
  }
}

std::queue<BasicBlock*> DepthFirstSearch::get_DFS(){
  return this->_path;
}

bool DepthFirstSearch::runOnFunction(Function &F){
  BasicBlock* BB = &F.getEntryBlock();
  this->reset_visited(F);
  this->addBasicBlock(BB); 

  do{
    BB = _list.top();
    _list.pop();
    Instruction* I = BB->getTerminator();
    if(!isa<ReturnInst>(I)){
      for(unsigned i = 0; i < I->getNumOperands(); i++){
        Value *v = I->getOperand(i);
        if(BasicBlock* Sucessor = dyn_cast<BasicBlock>(v)){
          this->addBasicBlock(Sucessor); 
        }
      }
    }
  }while(!_list.empty());
  
  this->dump();
  this->clear();
  return false;
}

char DepthFirstSearch::ID = 0;
static RegisterPass<DepthFirstSearch> X("DFS", 
"Depth First Search on the Control Flow Graph of the Function", false, false);

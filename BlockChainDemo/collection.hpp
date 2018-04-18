//
// Created by Jaken on 2018/1/8.
//

#ifndef BLOCKCHAINDEMO_COLLECTION_HPP
#define BLOCKCHAINDEMO_COLLECTION_HPP

#include "block.pb.h"

class tx_collect{
public:
    tx_collect():tx_set(),pre_tx(){
    }

    const std::vector<transaction> &GetForMiner(){
        if(tx_set.empty()&&pre_tx.empty())
            return pre_tx;

        pre_tx.clear();
        pre_tx.reserve(BLOCKSIZE);

        for(auto iter=tx_set.begin();iter!=tx_set.end();++iter)
        {
            if(pre_tx.size()==BLOCKSIZE)
                break;
            else
                pre_tx.push_back(*iter);

            tx_set.erase(iter);
        }

        return pre_tx;
    }

    void insert_block(const block &uselessblock){

        auto txs_size = uselessblock.txs().size();
        for(int i=0;i<txs_size;++i)
            tx_set.insert(uselessblock.txs(i));
    }

    void insert_tx(transaction & tx){
        tx_set.insert(tx);
    }




private:
    enum {BLOCKSIZE = 2000};

    std::vector<transaction> pre_tx;

    std::set<transaction> tx_set;

};





#endif //BLOCKCHAINDEMO_COLLECTION_HPP

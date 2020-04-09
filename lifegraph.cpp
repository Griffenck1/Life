#include "lifegraph.h"

/**
LifeGraph's constructor is empty as no parameters need to be set upon initailization
*/
LifeGraph::LifeGraph()
{

}

GraphBar* LifeGraph::AddBar(int pop_percent){
    if(graph_bars_.size() < 40){
        GraphBar *bar = new GraphBar((graph_bars_.size() * 20), pop_percent);
        graph_bars_.push_back(bar);
        return NULL;
    }
    else{
        GraphBar* to_delete = graph_bars_.front();
        graph_bars_.pop_front();
        for(GraphBar *b : graph_bars_){
            b->RelocateBack();
        }
        GraphBar *bar = new GraphBar((graph_bars_.size() * 20), pop_percent);
        graph_bars_.push_back(bar);
        return to_delete;
    }
}

#include "lifegraph.h"

/**
LifeGraph's constructor is empty as no parameters need to be set upon initailization
*/
LifeGraph::LifeGraph()
{

}

/**
Handles adding a bar to the life graph, returns whatever may have been deleted, as if something was deleted it changes LifeWindow's behavior
*/
GraphBar* LifeGraph::AddBar(int pop_percent){
    //If new bar would still be in bounds just add it to the end
    if(graph_bars_.size() < 40){
        GraphBar *bar = new GraphBar((graph_bars_.size() * 20), pop_percent);
        graph_bars_.push_back(bar);
        //return null so that LifeWindow can easily tell nothing was deleted
        return NULL;
    }
    else{
        //if the new bar would be out of bounds delete the first bar, relocate all other bars back 20, then add the new bar
        GraphBar* to_delete = graph_bars_.front();
        graph_bars_.pop_front();
        for(GraphBar *b : graph_bars_){
            b->RelocateBack();
        }
        GraphBar *bar = new GraphBar((graph_bars_.size() * 20), pop_percent);
        graph_bars_.push_back(bar);
        //send to_delete back to caller so it knows how to handle it
        return to_delete;
    }
}

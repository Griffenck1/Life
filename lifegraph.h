#ifndef LIFEGRAPH_H
#define LIFEGRAPH_H

#include "graphbar.h"
#include "lifeboard.h"
#include <deque>

class LifeGraph{
    public:
        LifeGraph();

        GraphBar* get_last_bar() const {return graph_bars_.back();}

        std::deque<GraphBar*> get_graph_bars() const {return graph_bars_;}

        GraphBar* AddBar(int pop_percent);
    private:
        std::deque<GraphBar*> graph_bars_;
};

#endif // LIFEGRAPH_H

#ifndef LIFEGRAPH_H
#define LIFEGRAPH_H

#include "graphbar.h"
#include "lifeboard.h"

class LifeGraph{
    public:
        LifeGraph();

        std::vector<GraphBar*> get_graph_bars() const {return graph_bars_;}

        void Step(int turn);
    private:
        std::vector<GraphBar*> graph_bars_;
};

#endif // LIFEGRAPH_H

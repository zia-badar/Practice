//
// Created by zia on 4/21/21.
//

#include "../../algorithms/cluster_graph.h"

int main(int argc, char **argv)
{
    cluster_graph cg;
    if (argc < 2)
    {
        cout << "usage: cluster_graph <path_to_cluster_graph_input_file>\n";
        exit(0);
    }
    cg.load_graph_from_file(argv[1]);

    cout << "computing ...\n";
    for (int k = 1; true; k++)
    {
        int ret = cg.solve(k);
        if (ret != -1)
        {
            cout << k << endl;
            for (int i = 0; i < cg.n; i++)
            {
                for (int j = i + 1; j < cg.n; j++)
                    if (cg.all_edge_statuses[i][j] != cluster_graph::UNCHANGED)
                        cout << i + 1 << ", " << j + 1 << endl;
            }
            break;
        }
    }

    return 0;
}
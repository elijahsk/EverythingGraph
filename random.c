#include "random.h"

__thread int __id;  
int isSymmetric = 0;
int createUndir = 0;
int not_processed = 1; 
int load_mode = 2;
int numa = 0;
int labels = 0;
algo_t algo_phase = ALGO;  
volatile int parallels_done; 
volatile int waiting;       
struct edge* edge_array_out;
struct edge* edge_array_in;

pthread_spinlock_t* locks;
int silent;    // Do not print debug info messages if 1
char* in_frontier_next;
char* in_frontier;
uint32_t items_in_frontier = 0;
uint32_t front_degree = 0;
algo_mode mode= PUSH;

int switch_mode = 1;
int a_mode = 0;


static void usage(void) {
	printf("Usage: ./random -f <graph file> -n <nb_nodes> [-m [data mode] -r -l [labelSet] -a [algo mode] -N ]\n");
	printf("\t-r [switch]: switch between PUSH and PULL where applicable (default 1)\n");
	printf("\t-n: NB_NODES \n");
	printf("\t-a [mode] : Algo mode, 0 PUSH, 1 PULL, (default 0)\n");
	printf("\t-l: labelSet \n");
	printf("\t-N: when running pr_numa or bfs_numa, run the NUMA aware version \n"); 
	printf("\t-m [0 1 2 3 4 5 6 7 8 9] : default = 2 0 grid sorted; 1 grid nosort; 2 adj sort by src only; 3 adj sort by src and dst;\n\t\t 4 adjacency created without sort; 5 grid fully sorted; 6 grid sort by source; \n \t\t7 edge array sort by source 8 edge array sort by source then dst 9 edge array no sort\n"); 
	_exit(-1);
}

int main(int argc, char **argv) {
	uint64_t start, stop;
	uint64_t load_start, load_stop;
	setlocale(LC_NUMERIC, "");
	int update = 0;

	int c;
	while ((c = getopt (argc, argv, "f:n:m:ul:La:p:srNh")) != -1) {
		switch (c) {
			case 'f':
				filename = optarg;
				break;
			case 'm':
				load_mode = atoi(optarg);
				printf("Load mode = %d\n", load_mode);
				break;
			case 'n':
				NB_NODES = atol(optarg);
				//					#if GRID	
				P = (NB_NODES * 8 / 1024) / 20;
				if(P> 2000) P = 256;
				if(P == 0 ) P = 4;

				printf("P = %d\n", P);
				in_frontier = (char*) malloc(NB_NODES * sizeof(char));
				in_frontier_next = (char* ) malloc(NB_NODES * sizeof(char));
				memset(in_frontier, 0, NB_NODES * sizeof(char));
				memset(in_frontier_next, 0 , NB_NODES * sizeof(char)); 

				break;
			case 'u':
				createUndir = 1;
				printf("#Creating Undir\n");
				break;
			case 'r':
				switch_mode = 0;
				break;
			case 's':
				isSymmetric = 1;
				printf(" no in-edges created\n");
				break;
			case 'a':
				a_mode = atoi(optarg);
				if(a_mode == 0) mode = PUSH;
				else mode = PULL;
				break;
			case 'l':
				labels = atoi(optarg);
				break;
			case 'p':
				BFS_ROOT= atol(optarg);
				break;
			case 'N':
				numa = 1;
				break;
			case 'h':
				usage();
			case '?':
				if (optopt == 'f' || optopt == 'n' || optopt == 'a')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				usage();
			default:
				usage();
		}
	}
	if(!NB_NODES || !filename)
		usage();

	printf("#Running with %d update threads and %d algo threads\n", NB_CONCURRENCY, ALGO_NB_THREADS);
	rdtscll(start);

	setWorkers(ALGO_NB_THREADS);
	init(update);
	rdtscll(stop);
	printf("#Total loading time %lu ( %fs )\n", stop - start, ((float)(stop - start))/(float)get_cpu_freq());

	current_algo.construct();
	rdtscll(start);
	{
		rdtscll(load_start);

		current_algo.reset(nodes);
		rdtscll(load_stop);
		printf ("#Total reset  time  %lu ( %fs )\n", load_stop - load_start, ((float)(load_stop - load_start))/(float)get_cpu_freq());

		current_algo.main(nodes, (uint8_t) labels);
	}
	rdtscll(stop);
	printf("#Total algo time %lu ( %fs )\n", stop - start, ((float)(stop - start))/(float)get_cpu_freq());

end:
	current_algo.destruct();
	return 0;
}

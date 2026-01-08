
#ifndef PV_H
#define PV_H

#include "moves.h"

// Principal variation (PV) data for the current search/iteration.  
// pv_list[ply][index]:  
//   - First index (0..63) is the ply (depth from the root).  
//   - Second index (0..63) is the move number within the PV at that ply.  
// The arrays are 64x64 because the engine assumes a maximum search depth  
// of 64 plies, and at each ply we can store a line of up to 64 moves.  
extern Move pv_list[64][64];  

// pv_length[ply] stores the number of moves in the PV line starting at 'ply'  
// for the current search/iteration.  
extern int pv_length[64];  

// Principal variation data from the previous iteration (e.g., iterative  
// deepening). This is kept separate so that the previous best line can be  
// reused as a hint for move ordering in the current iteration.  
// The indexing scheme and dimensions match pv_list/pv_length:  
// old_pv_list[ply][index], with a maximum depth of 64 plies.  
extern Move old_pv_list[64][64];  

// old_pv_length[ply] stores the length of the PV line starting at 'ply'  
// from the previous iteration.  
extern int old_pv_length[64];



#endif // PV_H

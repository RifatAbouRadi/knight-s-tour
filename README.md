# Knight’s Tour ♞
Project Description

This program attempts to solve the Knight’s Tour problem — a classic challenge in chess and computer science.
The task is to move a knight across a chessboard so that it visits every square exactly once.

The program can use two different algorithms:

Backtracking search – systematically explores all possible moves until a full tour is found.

Warnsdorff’s heuristic – a greedy method that chooses the next move with the fewest onward options, usually producing a valid tour much faster.

You can experiment with different board sizes (e.g., 4×4, 6×6, 8×8) and algorithms to explore how the knight behaves.
---
# Features

Solves or attempts the Knight’s Tour for any N×N board.

Two algorithm modes:

Backtracking (brute-force search)

Warnsdorff heuristic (greedy approach)

Prints the complete board path if a full tour is found.

Reports when no full tour exists (for example, on a 4×4 board).
---
# Note:

A 4×4 board has no valid Knight’s Tour — you can try it to observe how the knight gets trapped after a few moves.
Starting from the center usually gives a longer partial path than starting from a corner.
---
# How to Compile and Run
# Compile
gcc -O2 -Wall knight_tour.c -o knight_tour

# Run
./knight_tour <board_size> <use_warnsdorff>

---
## Example Output

Tour found on 8x8 (start 0,0, Warnsdorff):
  1  60  39  34  31  18   9  64
 38  35  32  19  10  63  30  17
 59   2  61  40  33  28  11   8
 36  49  42  23  20  13  62  29
  3  58  25  46  41  22   7  12
 50  37  48  43  24  15  14  21
 57   4  55  26  45  52  27   6
 44  51  56   5  54  47  16  53


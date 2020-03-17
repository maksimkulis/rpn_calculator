# rpn_calculator

###Simple Reverse Polish notation

Example of rpn from wiki:
https://en.wikipedia.org/wiki/Reverse_Polish_notation

15 7 1 1 + − ÷ 3 × 2 1 1 + + − =
15 7     2 − ÷ 3 × 2 1 1 + + − =
15         5 ÷ 3 × 2 1 1 + + − =
             3 3 × 2 1 1 + + − =
                 9 2 1 1 + + − =
                 9 2     2 + − =
                 9         4 − =
                             5 =
                             5

Usage: a.out "[expression]"
all values and operations must be separated by spaces

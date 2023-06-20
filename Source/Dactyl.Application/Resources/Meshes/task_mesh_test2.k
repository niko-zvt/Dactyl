*KEYWORD
*TITLE
*PART
Test
       1       2     100       0       0       0       0       0
*SECTION_SHELL
       2
       1       1       1       1
*MAT_ELASTIC
     100       0    2e11     0.29     0.0     0.0       0
*NODE
$    nid               x               y               z      tc      rc
     1               0.0               0               0       0       0
     2               1.5               0               0       0       0
     3               1.5             1.5               0       0       0
     4               1.5             4.0               0       0       0
     5               0.0             4.0               0       0       0
     6              -1.2             4.0               0       0       0
     7              -1.2             1.5               0       0       0
     8               0.0             1.5               0       0       0
*ELEMENT_SHELL
       1       1       6	7	5	5
       2       1       7	8	5	5
       3       1       1	2	8	8
       4       1       8	2	3	3
       5       1       8	3	4	4
       6       1       8	4	5	5
*END

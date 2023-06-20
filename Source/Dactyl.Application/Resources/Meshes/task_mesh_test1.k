*KEYWORD
*TITLE
*PART
Test
       1       2     100       0       0       0       0       0
*SECTION_SHELL
       2
       1       1       1       1
*MAT_ELASTIC
     100       0    2000     0.3     0.0     0.0       0
*NODE
$    nid               x               y               z      tc      rc
     1               0.0               0               0       0       0
     2               1.7               0               0       0       0
     3               1.7             1.5               0       0       0
     4               1.7             3.0               0       0       0
     5               0.0             3.0               0       0       0
     6               0.0             1.5               0       0       0
*ELEMENT_SHELL
       1       1       1       2       3      3
       2       1       1       3       6      6
       3       1       3       4       5      5
       4       1       6       3       5      5
*END

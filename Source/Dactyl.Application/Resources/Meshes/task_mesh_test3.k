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
      2              0.0               0               0       0       0
      1              1.5               0               0       0       0
      4              1.5             1.5               0       0       0
      8              1.5             4.0               0       0       0
      7              0.0             4.0               0       0       0
      6             -1.2             4.0               0       0       0
      5             -1.2             1.5               0       0       0
      3              0.0             1.5               0       0       0
*ELEMENT_SHELL
       1       1       1	2	4	4
       2       1       2	3	4	4
       3       1       5	6	3	3
       4       1       6	7	3	3
       5       1       8	4	7	7
       6       1       4	3	7	7
*END

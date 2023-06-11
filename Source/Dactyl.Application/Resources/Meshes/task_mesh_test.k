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
     0                 0               0               0       0       0
     1               1.0               0               0       0       0
     2                 0             1.0               0       0       0
     3               1.0             1.0               0       0       0
*ELEMENT_SHELL
       1       1       0       1       2      2
       2       1       1       3       2      2
*END

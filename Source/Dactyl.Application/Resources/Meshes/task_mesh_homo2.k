*KEYWORD
$
$ File created by cubit version 2021.11
$...>....1....>....2....>....3....>....4....>....5....>....6....>....7....>....8
*TITLE
$ cubit(C:/Users/Kukushkin/Desktop/task_mesh_homo2.k): 08/11/2022: 15:45:42
*PART
Block 3
$    pid     sid     mid   eosid    hgid    grav  adpopt    tmid
       3       3     100       0       0       0       0     100
*SECTION_SHELL
       3
$     t1      t2      t3      t4
       1       1       1       1

*MAT_ELASTIC
     100   7e-06  206800    0.29     0.0     0.0       0
*MAT_THERMAL_ISOTROPIC
     100     0.0     0.0     0.0     0.0     0.0
     500   0.045
*NODE
$    nid               x               y               z      tc      rc
     305               0               0               0       0       0
     304            0.15               0               0       0       0
     302            0.15            0.25               0       0       0
     303               0            0.25               0       0       0
$
$...>....1....>....2....>....3....>....4....>....5....>....6....>....7....>....8
$    eid     pid      n1      n2      n3      n4      n5      n6      n7      n8
*ELEMENT_SHELL
       1       3     305     304     302     302
       2       3     303     305     302     302
*END

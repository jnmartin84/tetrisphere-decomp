glabel func_80073290
    /* 4E640 80073290 3C06800F */  lui        $a2, %hi(D_800F22C0)
    /* 4E644 80073294 8CC622C0 */  lw         $a2, %lo(D_800F22C0)($a2)
    /* 4E648 80073298 27BDFFB0 */  addiu      $sp, $sp, -0x50
    /* 4E64C 8007329C 3C0E8010 */  lui        $t6, %hi(D_800FC5AC)
    /* 4E650 800732A0 8DCEC5AC */  lw         $t6, %lo(D_800FC5AC)($t6)
    /* 4E654 800732A4 AFBF0024 */  sw         $ra, 0x24($sp)
    /* 4E658 800732A8 3C04800F */  lui        $a0, %hi(D_800EDF70)
    /* 4E65C 800732AC AFB10020 */  sw         $s1, 0x20($sp)
    /* 4E660 800732B0 AFB0001C */  sw         $s0, 0x1C($sp)
    /* 4E664 800732B4 2484DF70 */  addiu      $a0, $a0, %lo(D_800EDF70)
    /* 4E668 800732B8 AFA60040 */  sw         $a2, 0x40($sp)
    /* 4E66C 800732BC 0C00A5D8 */  jal        func_80029760
    /* 4E670 800732C0 01C62823 */   subu      $a1, $t6, $a2
    /* 4E674 800732C4 3C0A8016 */  lui        $t2, %hi(D_8015D980)
    /* 4E678 800732C8 3C028010 */  lui        $v0, %hi(D_8010345B)
    /* 4E67C 800732CC 3C048011 */  lui        $a0, %hi(D_80110222)
    /* 4E680 800732D0 3C0B8011 */  lui        $t3, %hi(D_80113488)
    /* 4E684 800732D4 854AD980 */  lh         $t2, %lo(D_8015D980)($t2)
    /* 4E688 800732D8 256B3488 */  addiu      $t3, $t3, %lo(D_80113488)
    /* 4E68C 800732DC 24840222 */  addiu      $a0, $a0, %lo(D_80110222)
    /* 4E690 800732E0 2442345B */  addiu      $v0, $v0, %lo(D_8010345B)
    /* 4E694 800732E4 24070001 */  addiu      $a3, $zero, 0x1
    /* 4E698 800732E8 24030002 */  addiu      $v1, $zero, 0x2
    /* 4E69C 800732EC 24090057 */  addiu      $t1, $zero, 0x57
    /* 4E6A0 800732F0 2408005F */  addiu      $t0, $zero, 0x5F
    /* 4E6A4 800732F4 2406001E */  addiu      $a2, $zero, 0x1E
  .L800732F8:
    /* 4E6A8 800732F8 00066A00 */  sll        $t5, $a2, 8
    /* 4E6AC 800732FC 31AEF800 */  andi       $t6, $t5, 0xF800
    /* 4E6B0 80073300 0009C083 */  sra        $t8, $t1, 2
    /* 4E6B4 80073304 3319003E */  andi       $t9, $t8, 0x3E
    /* 4E6B8 80073308 000860C0 */  sll        $t4, $t0, 3
    /* 4E6BC 8007330C 318D07C0 */  andi       $t5, $t4, 0x7C0
    /* 4E6C0 80073310 032E7825 */  or         $t7, $t9, $t6
    /* 4E6C4 80073314 01ED2825 */  or         $a1, $t7, $t5
    /* 4E6C8 80073318 34B90001 */  ori        $t9, $a1, 0x1
    /* 4E6CC 8007331C 29410002 */  slti       $at, $t2, 0x2
    /* 4E6D0 80073320 A0460000 */  sb         $a2, 0x0($v0)
    /* 4E6D4 80073324 A0480001 */  sb         $t0, 0x1($v0)
    /* 4E6D8 80073328 A0490002 */  sb         $t1, 0x2($v0)
    /* 4E6DC 8007332C 14200003 */  bnez       $at, .L8007333C
    /* 4E6E0 80073330 A4992DAE */   sh        $t9, 0x2DAE($a0)
    /* 4E6E4 80073334 01637021 */  addu       $t6, $t3, $v1
    /* 4E6E8 80073338 A5D92DAE */  sh         $t9, 0x2DAE($t6)
  .L8007333C:
    /* 4E6EC 8007333C 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4E6F0 80073340 28E100C9 */  slti       $at, $a3, 0xC9
    /* 4E6F4 80073344 24420003 */  addiu      $v0, $v0, 0x3
    /* 4E6F8 80073348 24630002 */  addiu      $v1, $v1, 0x2
    /* 4E6FC 8007334C 1420FFEA */  bnez       $at, .L800732F8
    /* 4E700 80073350 24840002 */   addiu     $a0, $a0, 0x2
    /* 4E704 80073354 3C018011 */  lui        $at, %hi(D_80112FCE)
    /* 4E708 80073358 A4202FCE */  sh         $zero, %lo(D_80112FCE)($at)
    /* 4E70C 8007335C 29410002 */  slti       $at, $t2, 0x2
    /* 4E710 80073360 14200002 */  bnez       $at, .L8007336C
    /* 4E714 80073364 AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4E718 80073368 A5602DAE */  sh         $zero, 0x2DAE($t3)
  .L8007336C:
    /* 4E71C 8007336C 3C18800F */  lui        $t8, %hi(D_800F22C0)
    /* 4E720 80073370 8F1822C0 */  lw         $t8, %lo(D_800F22C0)($t8)
    /* 4E724 80073374 3C108010 */  lui        $s0, %hi(D_80103210)
    /* 4E728 80073378 3C110073 */  lui        $s1, %hi(D_736C50)
    /* 4E72C 8007337C 26316C50 */  addiu      $s1, $s1, %lo(D_736C50)
    /* 4E730 80073380 26103210 */  addiu      $s0, $s0, %lo(D_80103210)
    /* 4E734 80073384 02202025 */  or         $a0, $s1, $zero
    /* 4E738 80073388 24050016 */  addiu      $a1, $zero, 0x16
    /* 4E73C 8007338C 24060008 */  addiu      $a2, $zero, 0x8
    /* 4E740 80073390 0C00AA2D */  jal        loadAsset
    /* 4E744 80073394 AE180144 */   sw        $t8, 0x144($s0)
    /* 4E748 80073398 AE020000 */  sw         $v0, 0x0($s0)
    /* 4E74C 8007339C 3C0C800E */  lui        $t4, %hi(D_800E44A8)
    /* 4E750 800733A0 858C44A8 */  lh         $t4, %lo(D_800E44A8)($t4)
    /* 4E754 800733A4 24010003 */  addiu      $at, $zero, 0x3
    /* 4E758 800733A8 15810006 */  bne        $t4, $at, .L800733C4
    /* 4E75C 800733AC 02202025 */   or        $a0, $s1, $zero
    /* 4E760 800733B0 240500C2 */  addiu      $a1, $zero, 0xC2
    /* 4E764 800733B4 0C00AA2D */  jal        loadAsset
    /* 4E768 800733B8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E76C 800733BC 1000000E */  b          .L800733F8
    /* 4E770 800733C0 AE020004 */   sw        $v0, 0x4($s0)
  .L800733C4:
    /* 4E774 800733C4 02202025 */  or         $a0, $s1, $zero
    /* 4E778 800733C8 24050016 */  addiu      $a1, $zero, 0x16
    /* 4E77C 800733CC 0C00AA2D */  jal        loadAsset
    /* 4E780 800733D0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E784 800733D4 AE020004 */  sw         $v0, 0x4($s0)
    /* 4E788 800733D8 02202025 */  or         $a0, $s1, $zero
    /* 4E78C 800733DC 240500C2 */  addiu      $a1, $zero, 0xC2
    /* 4E790 800733E0 0C00AA2D */  jal        loadAsset
    /* 4E794 800733E4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E798 800733E8 AE020008 */  sw         $v0, 0x8($s0)
    /* 4E79C 800733EC 00402025 */  or         $a0, $v0, $zero
    /* 4E7A0 800733F0 0C00DFE7 */  jal        func_80037F9C
    /* 4E7A4 800733F4 24050002 */   addiu     $a1, $zero, 0x2
  .L800733F8:
    /* 4E7A8 800733F8 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4E7AC 800733FC 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4E7B0 80073400 24010004 */  addiu      $at, $zero, 0x4
    /* 4E7B4 80073404 1061011A */  beq        $v1, $at, .L80073870
    /* 4E7B8 80073408 24010003 */   addiu     $at, $zero, 0x3
    /* 4E7BC 8007340C 10610118 */  beq        $v1, $at, .L80073870
    /* 4E7C0 80073410 3C0F8016 */   lui       $t7, %hi(D_8015D980)
    /* 4E7C4 80073414 85EFD980 */  lh         $t7, %lo(D_8015D980)($t7)
    /* 4E7C8 80073418 24010001 */  addiu      $at, $zero, 0x1
    /* 4E7CC 8007341C 15E10114 */  bne        $t7, $at, .L80073870
    /* 4E7D0 80073420 02202025 */   or        $a0, $s1, $zero
    /* 4E7D4 80073424 2405002A */  addiu      $a1, $zero, 0x2A
    /* 4E7D8 80073428 0C00AA2D */  jal        loadAsset
    /* 4E7DC 8007342C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E7E0 80073430 AE020014 */  sw         $v0, 0x14($s0)
    /* 4E7E4 80073434 90590009 */  lbu        $t9, 0x9($v0)
    /* 4E7E8 80073438 3C018011 */  lui        $at, %hi(D_80112FCE)
    /* 4E7EC 8007343C 00197040 */  sll        $t6, $t9, 1
    /* 4E7F0 80073440 002E0821 */  addu       $at, $at, $t6
    /* 4E7F4 80073444 A4202FCE */  sh         $zero, %lo(D_80112FCE)($at)
    /* 4E7F8 80073448 02202025 */  or         $a0, $s1, $zero
    /* 4E7FC 8007344C 2405002C */  addiu      $a1, $zero, 0x2C
    /* 4E800 80073450 0C00AA2D */  jal        loadAsset
    /* 4E804 80073454 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E808 80073458 AE020018 */  sw         $v0, 0x18($s0)
    /* 4E80C 8007345C 02202025 */  or         $a0, $s1, $zero
    /* 4E810 80073460 2405002B */  addiu      $a1, $zero, 0x2B
    /* 4E814 80073464 0C00AA2D */  jal        loadAsset
    /* 4E818 80073468 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E81C 8007346C AE02001C */  sw         $v0, 0x1C($s0)
    /* 4E820 80073470 02202025 */  or         $a0, $s1, $zero
    /* 4E824 80073474 240500C0 */  addiu      $a1, $zero, 0xC0
    /* 4E828 80073478 0C00AA2D */  jal        loadAsset
    /* 4E82C 8007347C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E830 80073480 AE0200E0 */  sw         $v0, 0xE0($s0)
    /* 4E834 80073484 02202025 */  or         $a0, $s1, $zero
    /* 4E838 80073488 240500BF */  addiu      $a1, $zero, 0xBF
    /* 4E83C 8007348C 0C00AA2D */  jal        loadAsset
    /* 4E840 80073490 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E844 80073494 AE0200DC */  sw         $v0, 0xDC($s0)
    /* 4E848 80073498 02202025 */  or         $a0, $s1, $zero
    /* 4E84C 8007349C 24050027 */  addiu      $a1, $zero, 0x27
    /* 4E850 800734A0 0C00AA2D */  jal        loadAsset
    /* 4E854 800734A4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E858 800734A8 AE02000C */  sw         $v0, 0xC($s0)
    /* 4E85C 800734AC 02202025 */  or         $a0, $s1, $zero
    /* 4E860 800734B0 24050031 */  addiu      $a1, $zero, 0x31
    /* 4E864 800734B4 0C00AA2D */  jal        loadAsset
    /* 4E868 800734B8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E86C 800734BC AE020040 */  sw         $v0, 0x40($s0)
    /* 4E870 800734C0 02202025 */  or         $a0, $s1, $zero
    /* 4E874 800734C4 240500C1 */  addiu      $a1, $zero, 0xC1
    /* 4E878 800734C8 0C00AA2D */  jal        loadAsset
    /* 4E87C 800734CC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E880 800734D0 AE02004C */  sw         $v0, 0x4C($s0)
    /* 4E884 800734D4 02202025 */  or         $a0, $s1, $zero
    /* 4E888 800734D8 24050028 */  addiu      $a1, $zero, 0x28
    /* 4E88C 800734DC 0C00AA2D */  jal        loadAsset
    /* 4E890 800734E0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E894 800734E4 AE02013C */  sw         $v0, 0x13C($s0)
    /* 4E898 800734E8 02202025 */  or         $a0, $s1, $zero
    /* 4E89C 800734EC 24050067 */  addiu      $a1, $zero, 0x67
    /* 4E8A0 800734F0 0C00AA2D */  jal        loadAsset
    /* 4E8A4 800734F4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E8A8 800734F8 AE020044 */  sw         $v0, 0x44($s0)
    /* 4E8AC 800734FC 02202025 */  or         $a0, $s1, $zero
    /* 4E8B0 80073500 240500CF */  addiu      $a1, $zero, 0xCF
    /* 4E8B4 80073504 0C00AA2D */  jal        loadAsset
    /* 4E8B8 80073508 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E8BC 8007350C AE02008C */  sw         $v0, 0x8C($s0)
    /* 4E8C0 80073510 02202025 */  or         $a0, $s1, $zero
    /* 4E8C4 80073514 240500D0 */  addiu      $a1, $zero, 0xD0
    /* 4E8C8 80073518 0C00AA2D */  jal        loadAsset
    /* 4E8CC 8007351C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E8D0 80073520 AE020088 */  sw         $v0, 0x88($s0)
    /* 4E8D4 80073524 02202025 */  or         $a0, $s1, $zero
    /* 4E8D8 80073528 240500D1 */  addiu      $a1, $zero, 0xD1
    /* 4E8DC 8007352C 0C00AA2D */  jal        loadAsset
    /* 4E8E0 80073530 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E8E4 80073534 AE020084 */  sw         $v0, 0x84($s0)
    /* 4E8E8 80073538 02202025 */  or         $a0, $s1, $zero
    /* 4E8EC 8007353C 240500D2 */  addiu      $a1, $zero, 0xD2
    /* 4E8F0 80073540 0C00AA2D */  jal        loadAsset
    /* 4E8F4 80073544 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E8F8 80073548 AE020080 */  sw         $v0, 0x80($s0)
    /* 4E8FC 8007354C 02202025 */  or         $a0, $s1, $zero
    /* 4E900 80073550 240500D3 */  addiu      $a1, $zero, 0xD3
    /* 4E904 80073554 0C00AA2D */  jal        loadAsset
    /* 4E908 80073558 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E90C 8007355C AE02007C */  sw         $v0, 0x7C($s0)
    /* 4E910 80073560 02202025 */  or         $a0, $s1, $zero
    /* 4E914 80073564 240500D4 */  addiu      $a1, $zero, 0xD4
    /* 4E918 80073568 0C00AA2D */  jal        loadAsset
    /* 4E91C 8007356C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E920 80073570 AE020078 */  sw         $v0, 0x78($s0)
    /* 4E924 80073574 02202025 */  or         $a0, $s1, $zero
    /* 4E928 80073578 240500D5 */  addiu      $a1, $zero, 0xD5
    /* 4E92C 8007357C 0C00AA2D */  jal        loadAsset
    /* 4E930 80073580 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E934 80073584 AE020074 */  sw         $v0, 0x74($s0)
    /* 4E938 80073588 02202025 */  or         $a0, $s1, $zero
    /* 4E93C 8007358C 240500D6 */  addiu      $a1, $zero, 0xD6
    /* 4E940 80073590 0C00AA2D */  jal        loadAsset
    /* 4E944 80073594 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E948 80073598 AE020070 */  sw         $v0, 0x70($s0)
    /* 4E94C 8007359C 02202025 */  or         $a0, $s1, $zero
    /* 4E950 800735A0 240500D7 */  addiu      $a1, $zero, 0xD7
    /* 4E954 800735A4 0C00AA2D */  jal        loadAsset
    /* 4E958 800735A8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E95C 800735AC AE02006C */  sw         $v0, 0x6C($s0)
    /* 4E960 800735B0 02202025 */  or         $a0, $s1, $zero
    /* 4E964 800735B4 240500D8 */  addiu      $a1, $zero, 0xD8
    /* 4E968 800735B8 0C00AA2D */  jal        loadAsset
    /* 4E96C 800735BC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E970 800735C0 AE020068 */  sw         $v0, 0x68($s0)
    /* 4E974 800735C4 02202025 */  or         $a0, $s1, $zero
    /* 4E978 800735C8 240500D9 */  addiu      $a1, $zero, 0xD9
    /* 4E97C 800735CC 0C00AA2D */  jal        loadAsset
    /* 4E980 800735D0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E984 800735D4 AE020064 */  sw         $v0, 0x64($s0)
    /* 4E988 800735D8 02202025 */  or         $a0, $s1, $zero
    /* 4E98C 800735DC 240500DA */  addiu      $a1, $zero, 0xDA
    /* 4E990 800735E0 0C00AA2D */  jal        loadAsset
    /* 4E994 800735E4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E998 800735E8 AE020060 */  sw         $v0, 0x60($s0)
    /* 4E99C 800735EC 02202025 */  or         $a0, $s1, $zero
    /* 4E9A0 800735F0 240500DB */  addiu      $a1, $zero, 0xDB
    /* 4E9A4 800735F4 0C00AA2D */  jal        loadAsset
    /* 4E9A8 800735F8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E9AC 800735FC AE02005C */  sw         $v0, 0x5C($s0)
    /* 4E9B0 80073600 02202025 */  or         $a0, $s1, $zero
    /* 4E9B4 80073604 240500DC */  addiu      $a1, $zero, 0xDC
    /* 4E9B8 80073608 0C00AA2D */  jal        loadAsset
    /* 4E9BC 8007360C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E9C0 80073610 AE020058 */  sw         $v0, 0x58($s0)
    /* 4E9C4 80073614 02202025 */  or         $a0, $s1, $zero
    /* 4E9C8 80073618 240500DD */  addiu      $a1, $zero, 0xDD
    /* 4E9CC 8007361C 0C00AA2D */  jal        loadAsset
    /* 4E9D0 80073620 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E9D4 80073624 AE020054 */  sw         $v0, 0x54($s0)
    /* 4E9D8 80073628 02202025 */  or         $a0, $s1, $zero
    /* 4E9DC 8007362C 24050074 */  addiu      $a1, $zero, 0x74
    /* 4E9E0 80073630 0C00AA2D */  jal        loadAsset
    /* 4E9E4 80073634 24060008 */   addiu     $a2, $zero, 0x8
    /* 4E9E8 80073638 AE0200CC */  sw         $v0, 0xCC($s0)
    /* 4E9EC 8007363C 00003825 */  or         $a3, $zero, $zero
  .L80073640:
    /* 4E9F0 80073640 02202025 */  or         $a0, $s1, $zero
    /* 4E9F4 80073644 24E500FC */  addiu      $a1, $a3, 0xFC
    /* 4E9F8 80073648 24060008 */  addiu      $a2, $zero, 0x8
    /* 4E9FC 8007364C 0C00AA2D */  jal        loadAsset
    /* 4EA00 80073650 AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4EA04 80073654 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4EA08 80073658 00000000 */  nop
    /* 4EA0C 8007365C 0007C080 */  sll        $t8, $a3, 2
    /* 4EA10 80073660 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4EA14 80073664 28E10014 */  slti       $at, $a3, 0x14
    /* 4EA18 80073668 02186021 */  addu       $t4, $s0, $t8
    /* 4EA1C 8007366C 1420FFF4 */  bnez       $at, .L80073640
    /* 4EA20 80073670 AD8200E4 */   sw        $v0, 0xE4($t4)
    /* 4EA24 80073674 AFA7004C */  sw         $a3, 0x4C($sp)
    /* 4EA28 80073678 02202025 */  or         $a0, $s1, $zero
    /* 4EA2C 8007367C 24050062 */  addiu      $a1, $zero, 0x62
    /* 4EA30 80073680 0C00AA2D */  jal        loadAsset
    /* 4EA34 80073684 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EA38 80073688 AE020134 */  sw         $v0, 0x134($s0)
    /* 4EA3C 8007368C 02202025 */  or         $a0, $s1, $zero
    /* 4EA40 80073690 24050011 */  addiu      $a1, $zero, 0x11
    /* 4EA44 80073694 0C00AA2D */  jal        loadAsset
    /* 4EA48 80073698 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EA4C 8007369C AE020138 */  sw         $v0, 0x138($s0)
    /* 4EA50 800736A0 3C0F800E */  lui        $t7, %hi(D_800E44A8)
    /* 4EA54 800736A4 85EF44A8 */  lh         $t7, %lo(D_800E44A8)($t7)
    /* 4EA58 800736A8 00000000 */  nop
    /* 4EA5C 800736AC 25EDFFFF */  addiu      $t5, $t7, -0x1
    /* 4EA60 800736B0 2DA1000C */  sltiu      $at, $t5, 0xC
    /* 4EA64 800736B4 10200061 */  beqz       $at, .L8007383C
    /* 4EA68 800736B8 000D6880 */   sll       $t5, $t5, 2
    /* 4EA6C 800736BC 3C01800F */  lui        $at, %hi(jtbl_800EE070)
    /* 4EA70 800736C0 002D0821 */  addu       $at, $at, $t5
    /* 4EA74 800736C4 8C2DE070 */  lw         $t5, %lo(jtbl_800EE070)($at)
    /* 4EA78 800736C8 00000000 */  nop
    /* 4EA7C 800736CC 01A00008 */  jr         $t5
    /* 4EA80 800736D0 00000000 */   nop
    /* 4EA84 800736D4 3C19800E */  lui        $t9, %hi(D_800E44A4)
    /* 4EA88 800736D8 873944A4 */  lh         $t9, %lo(D_800E44A4)($t9)
    /* 4EA8C 800736DC 24010003 */  addiu      $at, $zero, 0x3
    /* 4EA90 800736E0 17210007 */  bne        $t9, $at, .L80073700
    /* 4EA94 800736E4 02202025 */   or        $a0, $s1, $zero
    /* 4EA98 800736E8 02202025 */  or         $a0, $s1, $zero
    /* 4EA9C 800736EC 2405008A */  addiu      $a1, $zero, 0x8A
    /* 4EAA0 800736F0 0C00AA2D */  jal        loadAsset
    /* 4EAA4 800736F4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EAA8 800736F8 10000005 */  b          .L80073710
    /* 4EAAC 800736FC AE0200D8 */   sw        $v0, 0xD8($s0)
  .L80073700:
    /* 4EAB0 80073700 240500BE */  addiu      $a1, $zero, 0xBE
    /* 4EAB4 80073704 0C00AA2D */  jal        loadAsset
    /* 4EAB8 80073708 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EABC 8007370C AE0200D8 */  sw         $v0, 0xD8($s0)
  .L80073710:
    /* 4EAC0 80073710 02202025 */  or         $a0, $s1, $zero
    /* 4EAC4 80073714 240500CC */  addiu      $a1, $zero, 0xCC
    /* 4EAC8 80073718 0C00AA2D */  jal        loadAsset
    /* 4EACC 8007371C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EAD0 80073720 AE0200D0 */  sw         $v0, 0xD0($s0)
    /* 4EAD4 80073724 02202025 */  or         $a0, $s1, $zero
    /* 4EAD8 80073728 240500CE */  addiu      $a1, $zero, 0xCE
    /* 4EADC 8007372C 0C00AA2D */  jal        loadAsset
    /* 4EAE0 80073730 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EAE4 80073734 AE0200D4 */  sw         $v0, 0xD4($s0)
    /* 4EAE8 80073738 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EAEC 8007373C 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EAF0 80073740 1000004C */  b          .L80073874
    /* 4EAF4 80073744 24010003 */   addiu     $at, $zero, 0x3
    /* 4EAF8 80073748 3C0E8011 */  lui        $t6, %hi(D_80113322)
    /* 4EAFC 8007374C 81CE3322 */  lb         $t6, %lo(D_80113322)($t6)
    /* 4EB00 80073750 3C05800E */  lui        $a1, %hi(D_800E23C0)
    /* 4EB04 80073754 000EC040 */  sll        $t8, $t6, 1
    /* 4EB08 80073758 00B82821 */  addu       $a1, $a1, $t8
    /* 4EB0C 8007375C 84A523C0 */  lh         $a1, %lo(D_800E23C0)($a1)
    /* 4EB10 80073760 02202025 */  or         $a0, $s1, $zero
    /* 4EB14 80073764 0C00AA2D */  jal        loadAsset
    /* 4EB18 80073768 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EB1C 8007376C AE020010 */  sw         $v0, 0x10($s0)
    /* 4EB20 80073770 02202025 */  or         $a0, $s1, $zero
    /* 4EB24 80073774 240500C5 */  addiu      $a1, $zero, 0xC5
    /* 4EB28 80073778 0C00AA2D */  jal        loadAsset
    /* 4EB2C 8007377C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EB30 80073780 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EB34 80073784 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EB38 80073788 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EB3C 8007378C 10000039 */  b          .L80073874
    /* 4EB40 80073790 24010003 */   addiu     $at, $zero, 0x3
    /* 4EB44 80073794 02202025 */  or         $a0, $s1, $zero
    /* 4EB48 80073798 24050064 */  addiu      $a1, $zero, 0x64
    /* 4EB4C 8007379C 0C00AA2D */  jal        loadAsset
    /* 4EB50 800737A0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EB54 800737A4 AE020010 */  sw         $v0, 0x10($s0)
    /* 4EB58 800737A8 02202025 */  or         $a0, $s1, $zero
    /* 4EB5C 800737AC 24050035 */  addiu      $a1, $zero, 0x35
    /* 4EB60 800737B0 0C00AA2D */  jal        loadAsset
    /* 4EB64 800737B4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EB68 800737B8 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EB6C 800737BC 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EB70 800737C0 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EB74 800737C4 1000002B */  b          .L80073874
    /* 4EB78 800737C8 24010003 */   addiu     $at, $zero, 0x3
    /* 4EB7C 800737CC 02202025 */  or         $a0, $s1, $zero
    /* 4EB80 800737D0 240500A1 */  addiu      $a1, $zero, 0xA1
    /* 4EB84 800737D4 0C00AA2D */  jal        loadAsset
    /* 4EB88 800737D8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EB8C 800737DC AE020010 */  sw         $v0, 0x10($s0)
    /* 4EB90 800737E0 02202025 */  or         $a0, $s1, $zero
    /* 4EB94 800737E4 240500A2 */  addiu      $a1, $zero, 0xA2
    /* 4EB98 800737E8 0C00AA2D */  jal        loadAsset
    /* 4EB9C 800737EC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EBA0 800737F0 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EBA4 800737F4 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EBA8 800737F8 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EBAC 800737FC 1000001D */  b          .L80073874
    /* 4EBB0 80073800 24010003 */   addiu     $at, $zero, 0x3
    /* 4EBB4 80073804 02202025 */  or         $a0, $s1, $zero
    /* 4EBB8 80073808 24050038 */  addiu      $a1, $zero, 0x38
    /* 4EBBC 8007380C 0C00AA2D */  jal        loadAsset
    /* 4EBC0 80073810 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EBC4 80073814 AE020010 */  sw         $v0, 0x10($s0)
    /* 4EBC8 80073818 02202025 */  or         $a0, $s1, $zero
    /* 4EBCC 8007381C 24050037 */  addiu      $a1, $zero, 0x37
    /* 4EBD0 80073820 0C00AA2D */  jal        loadAsset
    /* 4EBD4 80073824 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EBD8 80073828 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EBDC 8007382C 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EBE0 80073830 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EBE4 80073834 1000000F */  b          .L80073874
    /* 4EBE8 80073838 24010003 */   addiu     $at, $zero, 0x3
  .L8007383C:
    /* 4EBEC 8007383C 02202025 */  or         $a0, $s1, $zero
    /* 4EBF0 80073840 24050026 */  addiu      $a1, $zero, 0x26
    /* 4EBF4 80073844 0C00AA2D */  jal        loadAsset
    /* 4EBF8 80073848 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EBFC 8007384C AE020010 */  sw         $v0, 0x10($s0)
    /* 4EC00 80073850 02202025 */  or         $a0, $s1, $zero
    /* 4EC04 80073854 24050035 */  addiu      $a1, $zero, 0x35
    /* 4EC08 80073858 0C00AA2D */  jal        loadAsset
    /* 4EC0C 8007385C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC10 80073860 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EC14 80073864 3C03800E */  lui        $v1, %hi(D_800E44A8)
    /* 4EC18 80073868 846344A8 */  lh         $v1, %lo(D_800E44A8)($v1)
    /* 4EC1C 8007386C 00000000 */  nop
  .L80073870:
    /* 4EC20 80073870 24010003 */  addiu      $at, $zero, 0x3
  .L80073874:
    /* 4EC24 80073874 14610063 */  bne        $v1, $at, .L80073A04
    /* 4EC28 80073878 02202025 */   or        $a0, $s1, $zero
    /* 4EC2C 8007387C 24050091 */  addiu      $a1, $zero, 0x91
    /* 4EC30 80073880 0C00AA2D */  jal        loadAsset
    /* 4EC34 80073884 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC38 80073888 AE020020 */  sw         $v0, 0x20($s0)
    /* 4EC3C 8007388C 02202025 */  or         $a0, $s1, $zero
    /* 4EC40 80073890 24050093 */  addiu      $a1, $zero, 0x93
    /* 4EC44 80073894 0C00AA2D */  jal        loadAsset
    /* 4EC48 80073898 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC4C 8007389C AE020024 */  sw         $v0, 0x24($s0)
    /* 4EC50 800738A0 02202025 */  or         $a0, $s1, $zero
    /* 4EC54 800738A4 24050008 */  addiu      $a1, $zero, 0x8
    /* 4EC58 800738A8 0C00AA2D */  jal        loadAsset
    /* 4EC5C 800738AC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC60 800738B0 AE020028 */  sw         $v0, 0x28($s0)
    /* 4EC64 800738B4 02202025 */  or         $a0, $s1, $zero
    /* 4EC68 800738B8 24050009 */  addiu      $a1, $zero, 0x9
    /* 4EC6C 800738BC 0C00AA2D */  jal        loadAsset
    /* 4EC70 800738C0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC74 800738C4 AE02002C */  sw         $v0, 0x2C($s0)
    /* 4EC78 800738C8 02202025 */  or         $a0, $s1, $zero
    /* 4EC7C 800738CC 2405000A */  addiu      $a1, $zero, 0xA
    /* 4EC80 800738D0 0C00AA2D */  jal        loadAsset
    /* 4EC84 800738D4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC88 800738D8 AE020030 */  sw         $v0, 0x30($s0)
    /* 4EC8C 800738DC 02202025 */  or         $a0, $s1, $zero
    /* 4EC90 800738E0 2405000B */  addiu      $a1, $zero, 0xB
    /* 4EC94 800738E4 0C00AA2D */  jal        loadAsset
    /* 4EC98 800738E8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EC9C 800738EC AE020034 */  sw         $v0, 0x34($s0)
    /* 4ECA0 800738F0 02202025 */  or         $a0, $s1, $zero
    /* 4ECA4 800738F4 24050092 */  addiu      $a1, $zero, 0x92
    /* 4ECA8 800738F8 0C00AA2D */  jal        loadAsset
    /* 4ECAC 800738FC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ECB0 80073900 AE020038 */  sw         $v0, 0x38($s0)
    /* 4ECB4 80073904 02202025 */  or         $a0, $s1, $zero
    /* 4ECB8 80073908 240500A4 */  addiu      $a1, $zero, 0xA4
    /* 4ECBC 8007390C 0C00AA2D */  jal        loadAsset
    /* 4ECC0 80073910 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ECC4 80073914 AE020160 */  sw         $v0, 0x160($s0)
    /* 4ECC8 80073918 02202025 */  or         $a0, $s1, $zero
    /* 4ECCC 8007391C 240500CA */  addiu      $a1, $zero, 0xCA
    /* 4ECD0 80073920 0C00AA2D */  jal        loadAsset
    /* 4ECD4 80073924 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ECD8 80073928 AE020164 */  sw         $v0, 0x164($s0)
    /* 4ECDC 8007392C 02202025 */  or         $a0, $s1, $zero
    /* 4ECE0 80073930 240500A5 */  addiu      $a1, $zero, 0xA5
    /* 4ECE4 80073934 0C00AA2D */  jal        loadAsset
    /* 4ECE8 80073938 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ECEC 8007393C AE020170 */  sw         $v0, 0x170($s0)
    /* 4ECF0 80073940 02202025 */  or         $a0, $s1, $zero
    /* 4ECF4 80073944 240500C6 */  addiu      $a1, $zero, 0xC6
    /* 4ECF8 80073948 0C00AA2D */  jal        loadAsset
    /* 4ECFC 8007394C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ED00 80073950 AE020174 */  sw         $v0, 0x174($s0)
    /* 4ED04 80073954 02202025 */  or         $a0, $s1, $zero
    /* 4ED08 80073958 240500C7 */  addiu      $a1, $zero, 0xC7
    /* 4ED0C 8007395C 0C00AA2D */  jal        loadAsset
    /* 4ED10 80073960 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ED14 80073964 AE020168 */  sw         $v0, 0x168($s0)
    /* 4ED18 80073968 02202025 */  or         $a0, $s1, $zero
    /* 4ED1C 8007396C 240500C8 */  addiu      $a1, $zero, 0xC8
    /* 4ED20 80073970 0C00AA2D */  jal        loadAsset
    /* 4ED24 80073974 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ED28 80073978 AE02016C */  sw         $v0, 0x16C($s0)
    /* 4ED2C 8007397C 02202025 */  or         $a0, $s1, $zero
    /* 4ED30 80073980 240500A6 */  addiu      $a1, $zero, 0xA6
    /* 4ED34 80073984 0C00AA2D */  jal        loadAsset
    /* 4ED38 80073988 24060008 */   addiu     $a2, $zero, 0x8
    /* 4ED3C 8007398C AE020178 */  sw         $v0, 0x178($s0)
    /* 4ED40 80073990 0C00A830 */  jal        loadAnim
    /* 4ED44 80073994 24040038 */   addiu     $a0, $zero, 0x38
    /* 4ED48 80073998 AFA20048 */  sw         $v0, 0x48($sp)
    /* 4ED4C 8007399C 0C00A840 */  jal        loadMesh
    /* 4ED50 800739A0 24040013 */   addiu     $a0, $zero, 0x13
    /* 4ED54 800739A4 3C03800F */  lui        $v1, %hi(D_800F22C0)
    /* 4ED58 800739A8 246322C0 */  addiu      $v1, $v1, %lo(D_800F22C0)
    /* 4ED5C 800739AC 8C6C0000 */  lw         $t4, 0x0($v1)
    /* 4ED60 800739B0 2401FFF0 */  addiu      $at, $zero, -0x10
    /* 4ED64 800739B4 258F000F */  addiu      $t7, $t4, 0xF
    /* 4ED68 800739B8 01E12024 */  and        $a0, $t7, $at
    /* 4ED6C 800739BC 8FA50048 */  lw         $a1, 0x48($sp)
    /* 4ED70 800739C0 27B9004C */  addiu      $t9, $sp, 0x4C
    /* 4ED74 800739C4 AFA20044 */  sw         $v0, 0x44($sp)
    /* 4ED78 800739C8 AC640000 */  sw         $a0, 0x0($v1)
    /* 4ED7C 800739CC AFB90010 */  sw         $t9, 0x10($sp)
    /* 4ED80 800739D0 27A60044 */  addiu      $a2, $sp, 0x44
    /* 4ED84 800739D4 0C00B3DC */  jal        func_8002CF70
    /* 4ED88 800739D8 24070001 */   addiu     $a3, $zero, 0x1
    /* 4ED8C 800739DC 3C038010 */  lui        $v1, %hi(D_801033B8)
    /* 4ED90 800739E0 246333B8 */  addiu      $v1, $v1, %lo(D_801033B8)
    /* 4ED94 800739E4 AC620008 */  sw         $v0, 0x8($v1)
    /* 4ED98 800739E8 A460000C */  sh         $zero, 0xC($v1)
    /* 4ED9C 800739EC 3C0E800F */  lui        $t6, %hi(D_800F22C0)
    /* 4EDA0 800739F0 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4EDA4 800739F4 8DCE22C0 */  lw         $t6, %lo(D_800F22C0)($t6)
    /* 4EDA8 800739F8 3C01800F */  lui        $at, %hi(D_800F22C0)
    /* 4EDAC 800739FC 01C7C021 */  addu       $t8, $t6, $a3
    /* 4EDB0 80073A00 AC3822C0 */  sw         $t8, %lo(D_800F22C0)($at)
  .L80073A04:
    /* 4EDB4 80073A04 3C0C8016 */  lui        $t4, %hi(D_8015D980)
    /* 4EDB8 80073A08 858CD980 */  lh         $t4, %lo(D_8015D980)($t4)
    /* 4EDBC 80073A0C 3C0F800E */  lui        $t7, %hi(D_800E44A8)
    /* 4EDC0 80073A10 29810002 */  slti       $at, $t4, 0x2
    /* 4EDC4 80073A14 10200005 */  beqz       $at, .L80073A2C
    /* 4EDC8 80073A18 00003825 */   or        $a3, $zero, $zero
    /* 4EDCC 80073A1C 85EF44A8 */  lh         $t7, %lo(D_800E44A8)($t7)
    /* 4EDD0 80073A20 24010003 */  addiu      $at, $zero, 0x3
    /* 4EDD4 80073A24 15E10115 */  bne        $t7, $at, .L80073E7C
    /* 4EDD8 80073A28 02202025 */   or        $a0, $s1, $zero
  .L80073A2C:
    /* 4EDDC 80073A2C 02202025 */  or         $a0, $s1, $zero
    /* 4EDE0 80073A30 24E500FC */  addiu      $a1, $a3, 0xFC
    /* 4EDE4 80073A34 24060008 */  addiu      $a2, $zero, 0x8
    /* 4EDE8 80073A38 0C00AA2D */  jal        loadAsset
    /* 4EDEC 80073A3C AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4EDF0 80073A40 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4EDF4 80073A44 00000000 */  nop
    /* 4EDF8 80073A48 00076880 */  sll        $t5, $a3, 2
    /* 4EDFC 80073A4C 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4EE00 80073A50 28E10014 */  slti       $at, $a3, 0x14
    /* 4EE04 80073A54 020DC821 */  addu       $t9, $s0, $t5
    /* 4EE08 80073A58 1420FFF4 */  bnez       $at, .L80073A2C
    /* 4EE0C 80073A5C AF2200E4 */   sw        $v0, 0xE4($t9)
    /* 4EE10 80073A60 AFA7004C */  sw         $a3, 0x4C($sp)
    /* 4EE14 80073A64 02202025 */  or         $a0, $s1, $zero
    /* 4EE18 80073A68 24050062 */  addiu      $a1, $zero, 0x62
    /* 4EE1C 80073A6C 0C00AA2D */  jal        loadAsset
    /* 4EE20 80073A70 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE24 80073A74 AE020134 */  sw         $v0, 0x134($s0)
    /* 4EE28 80073A78 02202025 */  or         $a0, $s1, $zero
    /* 4EE2C 80073A7C 24050011 */  addiu      $a1, $zero, 0x11
    /* 4EE30 80073A80 0C00AA2D */  jal        loadAsset
    /* 4EE34 80073A84 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE38 80073A88 AE020138 */  sw         $v0, 0x138($s0)
    /* 4EE3C 80073A8C 02202025 */  or         $a0, $s1, $zero
    /* 4EE40 80073A90 2405007A */  addiu      $a1, $zero, 0x7A
    /* 4EE44 80073A94 0C00AA2D */  jal        loadAsset
    /* 4EE48 80073A98 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE4C 80073A9C AE020044 */  sw         $v0, 0x44($s0)
    /* 4EE50 80073AA0 02202025 */  or         $a0, $s1, $zero
    /* 4EE54 80073AA4 24050060 */  addiu      $a1, $zero, 0x60
    /* 4EE58 80073AA8 0C00AA2D */  jal        loadAsset
    /* 4EE5C 80073AAC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE60 80073AB0 AE02004C */  sw         $v0, 0x4C($s0)
    /* 4EE64 80073AB4 02202025 */  or         $a0, $s1, $zero
    /* 4EE68 80073AB8 2405007C */  addiu      $a1, $zero, 0x7C
    /* 4EE6C 80073ABC 0C00AA2D */  jal        loadAsset
    /* 4EE70 80073AC0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE74 80073AC4 AE020014 */  sw         $v0, 0x14($s0)
    /* 4EE78 80073AC8 02202025 */  or         $a0, $s1, $zero
    /* 4EE7C 80073ACC 2405007D */  addiu      $a1, $zero, 0x7D
    /* 4EE80 80073AD0 0C00AA2D */  jal        loadAsset
    /* 4EE84 80073AD4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE88 80073AD8 AE020018 */  sw         $v0, 0x18($s0)
    /* 4EE8C 80073ADC 02202025 */  or         $a0, $s1, $zero
    /* 4EE90 80073AE0 2405007E */  addiu      $a1, $zero, 0x7E
    /* 4EE94 80073AE4 0C00AA2D */  jal        loadAsset
    /* 4EE98 80073AE8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EE9C 80073AEC AE0200CC */  sw         $v0, 0xCC($s0)
    /* 4EEA0 80073AF0 3C0E800E */  lui        $t6, %hi(D_800E44A8)
    /* 4EEA4 80073AF4 85CE44A8 */  lh         $t6, %lo(D_800E44A8)($t6)
    /* 4EEA8 80073AF8 24010003 */  addiu      $at, $zero, 0x3
    /* 4EEAC 80073AFC 15C10014 */  bne        $t6, $at, .L80073B50
    /* 4EEB0 80073B00 3C18800E */   lui       $t8, %hi(D_800E44AC)
    /* 4EEB4 80073B04 871844AC */  lh         $t8, %lo(D_800E44AC)($t8)
    /* 4EEB8 80073B08 24010003 */  addiu      $at, $zero, 0x3
    /* 4EEBC 80073B0C 17010010 */  bne        $t8, $at, .L80073B50
    /* 4EEC0 80073B10 02202025 */   or        $a0, $s1, $zero
    /* 4EEC4 80073B14 2405003E */  addiu      $a1, $zero, 0x3E
    /* 4EEC8 80073B18 0C00AA2D */  jal        loadAsset
    /* 4EECC 80073B1C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EED0 80073B20 AE02001C */  sw         $v0, 0x1C($s0)
    /* 4EED4 80073B24 02202025 */  or         $a0, $s1, $zero
    /* 4EED8 80073B28 24050029 */  addiu      $a1, $zero, 0x29
    /* 4EEDC 80073B2C 0C00AA2D */  jal        loadAsset
    /* 4EEE0 80073B30 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EEE4 80073B34 AE0200E0 */  sw         $v0, 0xE0($s0)
    /* 4EEE8 80073B38 02202025 */  or         $a0, $s1, $zero
    /* 4EEEC 80073B3C 2405003F */  addiu      $a1, $zero, 0x3F
    /* 4EEF0 80073B40 0C00AA2D */  jal        loadAsset
    /* 4EEF4 80073B44 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EEF8 80073B48 1000000B */  b          .L80073B78
    /* 4EEFC 80073B4C AE0200D8 */   sw        $v0, 0xD8($s0)
  .L80073B50:
    /* 4EF00 80073B50 02202025 */  or         $a0, $s1, $zero
    /* 4EF04 80073B54 2405002B */  addiu      $a1, $zero, 0x2B
    /* 4EF08 80073B58 0C00AA2D */  jal        loadAsset
    /* 4EF0C 80073B5C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF10 80073B60 AE02001C */  sw         $v0, 0x1C($s0)
    /* 4EF14 80073B64 02202025 */  or         $a0, $s1, $zero
    /* 4EF18 80073B68 240500C0 */  addiu      $a1, $zero, 0xC0
    /* 4EF1C 80073B6C 0C00AA2D */  jal        loadAsset
    /* 4EF20 80073B70 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF24 80073B74 AE0200E0 */  sw         $v0, 0xE0($s0)
  .L80073B78:
    /* 4EF28 80073B78 3C0C800E */  lui        $t4, %hi(D_800E44A8)
    /* 4EF2C 80073B7C 858C44A8 */  lh         $t4, %lo(D_800E44A8)($t4)
    /* 4EF30 80073B80 24010003 */  addiu      $at, $zero, 0x3
    /* 4EF34 80073B84 11810019 */  beq        $t4, $at, .L80073BEC
    /* 4EF38 80073B88 02202025 */   or        $a0, $s1, $zero
    /* 4EF3C 80073B8C 2405002D */  addiu      $a1, $zero, 0x2D
    /* 4EF40 80073B90 0C00AA2D */  jal        loadAsset
    /* 4EF44 80073B94 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF48 80073B98 AE020010 */  sw         $v0, 0x10($s0)
    /* 4EF4C 80073B9C 02202025 */  or         $a0, $s1, $zero
    /* 4EF50 80073BA0 2405002E */  addiu      $a1, $zero, 0x2E
    /* 4EF54 80073BA4 0C00AA2D */  jal        loadAsset
    /* 4EF58 80073BA8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF5C 80073BAC AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4EF60 80073BB0 02202025 */  or         $a0, $s1, $zero
    /* 4EF64 80073BB4 24050117 */  addiu      $a1, $zero, 0x117
    /* 4EF68 80073BB8 0C00AA2D */  jal        loadAsset
    /* 4EF6C 80073BBC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF70 80073BC0 AE02013C */  sw         $v0, 0x13C($s0)
    /* 4EF74 80073BC4 02202025 */  or         $a0, $s1, $zero
    /* 4EF78 80073BC8 2405005F */  addiu      $a1, $zero, 0x5F
    /* 4EF7C 80073BCC 0C00AA2D */  jal        loadAsset
    /* 4EF80 80073BD0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF84 80073BD4 AE020048 */  sw         $v0, 0x48($s0)
    /* 4EF88 80073BD8 02202025 */  or         $a0, $s1, $zero
    /* 4EF8C 80073BDC 24050061 */  addiu      $a1, $zero, 0x61
    /* 4EF90 80073BE0 0C00AA2D */  jal        loadAsset
    /* 4EF94 80073BE4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EF98 80073BE8 AE020050 */  sw         $v0, 0x50($s0)
  .L80073BEC:
    /* 4EF9C 80073BEC 02202025 */  or         $a0, $s1, $zero
    /* 4EFA0 80073BF0 240500DE */  addiu      $a1, $zero, 0xDE
    /* 4EFA4 80073BF4 0C00AA2D */  jal        loadAsset
    /* 4EFA8 80073BF8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EFAC 80073BFC AE020078 */  sw         $v0, 0x78($s0)
    /* 4EFB0 80073C00 02202025 */  or         $a0, $s1, $zero
    /* 4EFB4 80073C04 240500DF */  addiu      $a1, $zero, 0xDF
    /* 4EFB8 80073C08 0C00AA2D */  jal        loadAsset
    /* 4EFBC 80073C0C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EFC0 80073C10 AE020074 */  sw         $v0, 0x74($s0)
    /* 4EFC4 80073C14 02202025 */  or         $a0, $s1, $zero
    /* 4EFC8 80073C18 240500E0 */  addiu      $a1, $zero, 0xE0
    /* 4EFCC 80073C1C 0C00AA2D */  jal        loadAsset
    /* 4EFD0 80073C20 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EFD4 80073C24 AE020070 */  sw         $v0, 0x70($s0)
    /* 4EFD8 80073C28 02202025 */  or         $a0, $s1, $zero
    /* 4EFDC 80073C2C 240500E1 */  addiu      $a1, $zero, 0xE1
    /* 4EFE0 80073C30 0C00AA2D */  jal        loadAsset
    /* 4EFE4 80073C34 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EFE8 80073C38 AE02006C */  sw         $v0, 0x6C($s0)
    /* 4EFEC 80073C3C 02202025 */  or         $a0, $s1, $zero
    /* 4EFF0 80073C40 240500E2 */  addiu      $a1, $zero, 0xE2
    /* 4EFF4 80073C44 0C00AA2D */  jal        loadAsset
    /* 4EFF8 80073C48 24060008 */   addiu     $a2, $zero, 0x8
    /* 4EFFC 80073C4C AE020068 */  sw         $v0, 0x68($s0)
    /* 4F000 80073C50 02202025 */  or         $a0, $s1, $zero
    /* 4F004 80073C54 240500E3 */  addiu      $a1, $zero, 0xE3
    /* 4F008 80073C58 0C00AA2D */  jal        loadAsset
    /* 4F00C 80073C5C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F010 80073C60 AE020064 */  sw         $v0, 0x64($s0)
    /* 4F014 80073C64 02202025 */  or         $a0, $s1, $zero
    /* 4F018 80073C68 240500E4 */  addiu      $a1, $zero, 0xE4
    /* 4F01C 80073C6C 0C00AA2D */  jal        loadAsset
    /* 4F020 80073C70 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F024 80073C74 AE020060 */  sw         $v0, 0x60($s0)
    /* 4F028 80073C78 02202025 */  or         $a0, $s1, $zero
    /* 4F02C 80073C7C 240500E5 */  addiu      $a1, $zero, 0xE5
    /* 4F030 80073C80 0C00AA2D */  jal        loadAsset
    /* 4F034 80073C84 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F038 80073C88 AE02005C */  sw         $v0, 0x5C($s0)
    /* 4F03C 80073C8C 02202025 */  or         $a0, $s1, $zero
    /* 4F040 80073C90 240500E6 */  addiu      $a1, $zero, 0xE6
    /* 4F044 80073C94 0C00AA2D */  jal        loadAsset
    /* 4F048 80073C98 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F04C 80073C9C AE020058 */  sw         $v0, 0x58($s0)
    /* 4F050 80073CA0 02202025 */  or         $a0, $s1, $zero
    /* 4F054 80073CA4 240500E7 */  addiu      $a1, $zero, 0xE7
    /* 4F058 80073CA8 0C00AA2D */  jal        loadAsset
    /* 4F05C 80073CAC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F060 80073CB0 AE020054 */  sw         $v0, 0x54($s0)
    /* 4F064 80073CB4 02202025 */  or         $a0, $s1, $zero
    /* 4F068 80073CB8 240500ED */  addiu      $a1, $zero, 0xED
    /* 4F06C 80073CBC 0C00AA2D */  jal        loadAsset
    /* 4F070 80073CC0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F074 80073CC4 AE0200A0 */  sw         $v0, 0xA0($s0)
    /* 4F078 80073CC8 02202025 */  or         $a0, $s1, $zero
    /* 4F07C 80073CCC 240500EE */  addiu      $a1, $zero, 0xEE
    /* 4F080 80073CD0 0C00AA2D */  jal        loadAsset
    /* 4F084 80073CD4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F088 80073CD8 AE02009C */  sw         $v0, 0x9C($s0)
    /* 4F08C 80073CDC 02202025 */  or         $a0, $s1, $zero
    /* 4F090 80073CE0 240500EF */  addiu      $a1, $zero, 0xEF
    /* 4F094 80073CE4 0C00AA2D */  jal        loadAsset
    /* 4F098 80073CE8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F09C 80073CEC AE020098 */  sw         $v0, 0x98($s0)
    /* 4F0A0 80073CF0 02202025 */  or         $a0, $s1, $zero
    /* 4F0A4 80073CF4 240500F0 */  addiu      $a1, $zero, 0xF0
    /* 4F0A8 80073CF8 0C00AA2D */  jal        loadAsset
    /* 4F0AC 80073CFC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F0B0 80073D00 AE020094 */  sw         $v0, 0x94($s0)
    /* 4F0B4 80073D04 02202025 */  or         $a0, $s1, $zero
    /* 4F0B8 80073D08 240500F1 */  addiu      $a1, $zero, 0xF1
    /* 4F0BC 80073D0C 0C00AA2D */  jal        loadAsset
    /* 4F0C0 80073D10 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F0C4 80073D14 AE020090 */  sw         $v0, 0x90($s0)
    /* 4F0C8 80073D18 02202025 */  or         $a0, $s1, $zero
    /* 4F0CC 80073D1C 240500F2 */  addiu      $a1, $zero, 0xF2
    /* 4F0D0 80073D20 0C00AA2D */  jal        loadAsset
    /* 4F0D4 80073D24 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F0D8 80073D28 AE02008C */  sw         $v0, 0x8C($s0)
    /* 4F0DC 80073D2C 02202025 */  or         $a0, $s1, $zero
    /* 4F0E0 80073D30 240500F3 */  addiu      $a1, $zero, 0xF3
    /* 4F0E4 80073D34 0C00AA2D */  jal        loadAsset
    /* 4F0E8 80073D38 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F0EC 80073D3C AE020088 */  sw         $v0, 0x88($s0)
    /* 4F0F0 80073D40 02202025 */  or         $a0, $s1, $zero
    /* 4F0F4 80073D44 240500F4 */  addiu      $a1, $zero, 0xF4
    /* 4F0F8 80073D48 0C00AA2D */  jal        loadAsset
    /* 4F0FC 80073D4C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F100 80073D50 AE020084 */  sw         $v0, 0x84($s0)
    /* 4F104 80073D54 02202025 */  or         $a0, $s1, $zero
    /* 4F108 80073D58 240500F5 */  addiu      $a1, $zero, 0xF5
    /* 4F10C 80073D5C 0C00AA2D */  jal        loadAsset
    /* 4F110 80073D60 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F114 80073D64 AE020080 */  sw         $v0, 0x80($s0)
    /* 4F118 80073D68 02202025 */  or         $a0, $s1, $zero
    /* 4F11C 80073D6C 240500F6 */  addiu      $a1, $zero, 0xF6
    /* 4F120 80073D70 0C00AA2D */  jal        loadAsset
    /* 4F124 80073D74 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F128 80073D78 8E0F0014 */  lw         $t7, 0x14($s0)
    /* 4F12C 80073D7C AE02007C */  sw         $v0, 0x7C($s0)
    /* 4F130 80073D80 91ED0009 */  lbu        $t5, 0x9($t7)
    /* 4F134 80073D84 3C018011 */  lui        $at, %hi(D_80112FCE)
    /* 4F138 80073D88 3C0E8016 */  lui        $t6, %hi(D_8015D980)
    /* 4F13C 80073D8C 000DC840 */  sll        $t9, $t5, 1
    /* 4F140 80073D90 85CED980 */  lh         $t6, %lo(D_8015D980)($t6)
    /* 4F144 80073D94 00390821 */  addu       $at, $at, $t9
    /* 4F148 80073D98 A4202FCE */  sh         $zero, %lo(D_80112FCE)($at)
    /* 4F14C 80073D9C 29C10002 */  slti       $at, $t6, 0x2
    /* 4F150 80073DA0 1420003F */  bnez       $at, .L80073EA0
    /* 4F154 80073DA4 02202025 */   or        $a0, $s1, $zero
    /* 4F158 80073DA8 2405000F */  addiu      $a1, $zero, 0xF
    /* 4F15C 80073DAC 0C00AA2D */  jal        loadAsset
    /* 4F160 80073DB0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F164 80073DB4 8E180014 */  lw         $t8, 0x14($s0)
    /* 4F168 80073DB8 AE020140 */  sw         $v0, 0x140($s0)
    /* 4F16C 80073DBC 930C0009 */  lbu        $t4, 0x9($t8)
    /* 4F170 80073DC0 3C018011 */  lui        $at, %hi(D_80116236)
    /* 4F174 80073DC4 3C048011 */  lui        $a0, %hi(D_80113328)
    /* 4F178 80073DC8 000C7840 */  sll        $t7, $t4, 1
    /* 4F17C 80073DCC 002F0821 */  addu       $at, $at, $t7
    /* 4F180 80073DD0 3C038010 */  lui        $v1, %hi(D_80103210)
    /* 4F184 80073DD4 8C843328 */  lw         $a0, %lo(D_80113328)($a0)
    /* 4F188 80073DD8 A4206236 */  sh         $zero, %lo(D_80116236)($at)
    /* 4F18C 80073DDC 24633210 */  addiu      $v1, $v1, %lo(D_80103210)
    /* 4F190 80073DE0 AFA0004C */  sw         $zero, 0x4C($sp)
  .L80073DE4:
    /* 4F194 80073DE4 908D0000 */  lbu        $t5, 0x0($a0)
    /* 4F198 80073DE8 24630001 */  addiu      $v1, $v1, 0x1
    /* 4F19C 80073DEC 31B900FF */  andi       $t9, $t5, 0xFF
    /* 4F1A0 80073DF0 17200006 */  bnez       $t9, .L80073E0C
    /* 4F1A4 80073DF4 A06D017B */   sb        $t5, 0x17B($v1)
    /* 4F1A8 80073DF8 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4F1AC 80073DFC 00000000 */  nop
    /* 4F1B0 80073E00 A2070185 */  sb         $a3, 0x185($s0)
    /* 4F1B4 80073E04 10000008 */  b          .L80073E28
    /* 4F1B8 80073E08 00003825 */   or        $a3, $zero, $zero
  .L80073E0C:
    /* 4F1BC 80073E0C 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4F1C0 80073E10 24840001 */  addiu      $a0, $a0, 0x1
    /* 4F1C4 80073E14 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4F1C8 80073E18 28E10009 */  slti       $at, $a3, 0x9
    /* 4F1CC 80073E1C 1420FFF1 */  bnez       $at, .L80073DE4
    /* 4F1D0 80073E20 AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4F1D4 80073E24 00003825 */  or         $a3, $zero, $zero
  .L80073E28:
    /* 4F1D8 80073E28 3C028011 */  lui        $v0, %hi(D_80116590)
    /* 4F1DC 80073E2C 3C038010 */  lui        $v1, %hi(D_80103210)
    /* 4F1E0 80073E30 8C426590 */  lw         $v0, %lo(D_80116590)($v0)
    /* 4F1E4 80073E34 24633210 */  addiu      $v1, $v1, %lo(D_80103210)
    /* 4F1E8 80073E38 AFA7004C */  sw         $a3, 0x4C($sp)
  .L80073E3C:
    /* 4F1EC 80073E3C 904E0000 */  lbu        $t6, 0x0($v0)
    /* 4F1F0 80073E40 24630001 */  addiu      $v1, $v1, 0x1
    /* 4F1F4 80073E44 31D800FF */  andi       $t8, $t6, 0xFF
    /* 4F1F8 80073E48 17000004 */  bnez       $t8, .L80073E5C
    /* 4F1FC 80073E4C A06E0185 */   sb        $t6, 0x185($v1)
    /* 4F200 80073E50 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4F204 80073E54 10000012 */  b          .L80073EA0
    /* 4F208 80073E58 A207018F */   sb        $a3, 0x18F($s0)
  .L80073E5C:
    /* 4F20C 80073E5C 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4F210 80073E60 24420001 */  addiu      $v0, $v0, 0x1
    /* 4F214 80073E64 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4F218 80073E68 28E10009 */  slti       $at, $a3, 0x9
    /* 4F21C 80073E6C 1420FFF3 */  bnez       $at, .L80073E3C
    /* 4F220 80073E70 AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4F224 80073E74 1000000A */  b          .L80073EA0
    /* 4F228 80073E78 00000000 */   nop
  .L80073E7C:
    /* 4F22C 80073E7C 24050079 */  addiu      $a1, $zero, 0x79
    /* 4F230 80073E80 0C00AA2D */  jal        loadAsset
    /* 4F234 80073E84 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F238 80073E88 AE020160 */  sw         $v0, 0x160($s0)
    /* 4F23C 80073E8C 02202025 */  or         $a0, $s1, $zero
    /* 4F240 80073E90 240500CA */  addiu      $a1, $zero, 0xCA
    /* 4F244 80073E94 0C00AA2D */  jal        loadAsset
    /* 4F248 80073E98 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F24C 80073E9C AE020164 */  sw         $v0, 0x164($s0)
  .L80073EA0:
    /* 4F250 80073EA0 3C0C800E */  lui        $t4, %hi(D_800E44A8)
    /* 4F254 80073EA4 858C44A8 */  lh         $t4, %lo(D_800E44A8)($t4)
    /* 4F258 80073EA8 24010004 */  addiu      $at, $zero, 0x4
    /* 4F25C 80073EAC 15810043 */  bne        $t4, $at, .L80073FBC
    /* 4F260 80073EB0 02202025 */   or        $a0, $s1, $zero
    /* 4F264 80073EB4 02202025 */  or         $a0, $s1, $zero
    /* 4F268 80073EB8 24050075 */  addiu      $a1, $zero, 0x75
    /* 4F26C 80073EBC 0C00AA2D */  jal        loadAsset
    /* 4F270 80073EC0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F274 80073EC4 AE020010 */  sw         $v0, 0x10($s0)
    /* 4F278 80073EC8 02202025 */  or         $a0, $s1, $zero
    /* 4F27C 80073ECC 24050036 */  addiu      $a1, $zero, 0x36
    /* 4F280 80073ED0 0C00AA2D */  jal        loadAsset
    /* 4F284 80073ED4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F288 80073ED8 AE0200D8 */  sw         $v0, 0xD8($s0)
    /* 4F28C 80073EDC 02202025 */  or         $a0, $s1, $zero
    /* 4F290 80073EE0 24050027 */  addiu      $a1, $zero, 0x27
    /* 4F294 80073EE4 0C00AA2D */  jal        loadAsset
    /* 4F298 80073EE8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F29C 80073EEC AE02000C */  sw         $v0, 0xC($s0)
    /* 4F2A0 80073EF0 02202025 */  or         $a0, $s1, $zero
    /* 4F2A4 80073EF4 24050068 */  addiu      $a1, $zero, 0x68
    /* 4F2A8 80073EF8 0C00AA2D */  jal        loadAsset
    /* 4F2AC 80073EFC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F2B0 80073F00 AE020054 */  sw         $v0, 0x54($s0)
    /* 4F2B4 80073F04 02202025 */  or         $a0, $s1, $zero
    /* 4F2B8 80073F08 24050069 */  addiu      $a1, $zero, 0x69
    /* 4F2BC 80073F0C 0C00AA2D */  jal        loadAsset
    /* 4F2C0 80073F10 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F2C4 80073F14 AE020058 */  sw         $v0, 0x58($s0)
    /* 4F2C8 80073F18 02202025 */  or         $a0, $s1, $zero
    /* 4F2CC 80073F1C 24050063 */  addiu      $a1, $zero, 0x63
    /* 4F2D0 80073F20 0C00AA2D */  jal        loadAsset
    /* 4F2D4 80073F24 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F2D8 80073F28 AE02005C */  sw         $v0, 0x5C($s0)
    /* 4F2DC 80073F2C 02202025 */  or         $a0, $s1, $zero
    /* 4F2E0 80073F30 2405006A */  addiu      $a1, $zero, 0x6A
    /* 4F2E4 80073F34 0C00AA2D */  jal        loadAsset
    /* 4F2E8 80073F38 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F2EC 80073F3C AE020060 */  sw         $v0, 0x60($s0)
    /* 4F2F0 80073F40 02202025 */  or         $a0, $s1, $zero
    /* 4F2F4 80073F44 2405006B */  addiu      $a1, $zero, 0x6B
    /* 4F2F8 80073F48 0C00AA2D */  jal        loadAsset
    /* 4F2FC 80073F4C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F300 80073F50 AE020064 */  sw         $v0, 0x64($s0)
    /* 4F304 80073F54 00003825 */  or         $a3, $zero, $zero
  .L80073F58:
    /* 4F308 80073F58 02202025 */  or         $a0, $s1, $zero
    /* 4F30C 80073F5C 24E500FC */  addiu      $a1, $a3, 0xFC
    /* 4F310 80073F60 24060008 */  addiu      $a2, $zero, 0x8
    /* 4F314 80073F64 0C00AA2D */  jal        loadAsset
    /* 4F318 80073F68 AFA7004C */   sw        $a3, 0x4C($sp)
    /* 4F31C 80073F6C 8FA7004C */  lw         $a3, 0x4C($sp)
    /* 4F320 80073F70 00000000 */  nop
    /* 4F324 80073F74 00077880 */  sll        $t7, $a3, 2
    /* 4F328 80073F78 24E70001 */  addiu      $a3, $a3, 0x1
    /* 4F32C 80073F7C 28E10014 */  slti       $at, $a3, 0x14
    /* 4F330 80073F80 020F6821 */  addu       $t5, $s0, $t7
    /* 4F334 80073F84 1420FFF4 */  bnez       $at, .L80073F58
    /* 4F338 80073F88 ADA200E4 */   sw        $v0, 0xE4($t5)
    /* 4F33C 80073F8C AFA7004C */  sw         $a3, 0x4C($sp)
    /* 4F340 80073F90 02202025 */  or         $a0, $s1, $zero
    /* 4F344 80073F94 24050062 */  addiu      $a1, $zero, 0x62
    /* 4F348 80073F98 0C00AA2D */  jal        loadAsset
    /* 4F34C 80073F9C 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F350 80073FA0 AE020134 */  sw         $v0, 0x134($s0)
    /* 4F354 80073FA4 02202025 */  or         $a0, $s1, $zero
    /* 4F358 80073FA8 24050011 */  addiu      $a1, $zero, 0x11
    /* 4F35C 80073FAC 0C00AA2D */  jal        loadAsset
    /* 4F360 80073FB0 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F364 80073FB4 10000019 */  b          .L8007401C
    /* 4F368 80073FB8 AE020138 */   sw        $v0, 0x138($s0)
  .L80073FBC:
    /* 4F36C 80073FBC 2405003B */  addiu      $a1, $zero, 0x3B
    /* 4F370 80073FC0 0C00AA2D */  jal        loadAsset
    /* 4F374 80073FC4 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F378 80073FC8 AE020148 */  sw         $v0, 0x148($s0)
    /* 4F37C 80073FCC 02202025 */  or         $a0, $s1, $zero
    /* 4F380 80073FD0 2405003C */  addiu      $a1, $zero, 0x3C
    /* 4F384 80073FD4 0C00AA2D */  jal        loadAsset
    /* 4F388 80073FD8 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F38C 80073FDC AE02014C */  sw         $v0, 0x14C($s0)
    /* 4F390 80073FE0 02202025 */  or         $a0, $s1, $zero
    /* 4F394 80073FE4 2405003D */  addiu      $a1, $zero, 0x3D
    /* 4F398 80073FE8 0C00AA2D */  jal        loadAsset
    /* 4F39C 80073FEC 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F3A0 80073FF0 AE020150 */  sw         $v0, 0x150($s0)
    /* 4F3A4 80073FF4 02202025 */  or         $a0, $s1, $zero
    /* 4F3A8 80073FF8 24050041 */  addiu      $a1, $zero, 0x41
    /* 4F3AC 80073FFC 0C00AA2D */  jal        loadAsset
    /* 4F3B0 80074000 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F3B4 80074004 AE020154 */  sw         $v0, 0x154($s0)
    /* 4F3B8 80074008 02202025 */  or         $a0, $s1, $zero
    /* 4F3BC 8007400C 24050044 */  addiu      $a1, $zero, 0x44
    /* 4F3C0 80074010 0C00AA2D */  jal        loadAsset
    /* 4F3C4 80074014 24060008 */   addiu     $a2, $zero, 0x8
    /* 4F3C8 80074018 AE020158 */  sw         $v0, 0x158($s0)
  .L8007401C:
    /* 4F3CC 8007401C 8E040000 */  lw         $a0, 0x0($s0)
    /* 4F3D0 80074020 0C00E095 */  jal        func_80038254
    /* 4F3D4 80074024 00000000 */   nop
    /* 4F3D8 80074028 8E040004 */  lw         $a0, 0x4($s0)
    /* 4F3DC 8007402C 0C00E0A1 */  jal        func_80038284
    /* 4F3E0 80074030 00000000 */   nop
    /* 4F3E4 80074034 3C19800F */  lui        $t9, %hi(D_800F22C0)
    /* 4F3E8 80074038 8F3922C0 */  lw         $t9, %lo(D_800F22C0)($t9)
    /* 4F3EC 8007403C 8FAE0040 */  lw         $t6, 0x40($sp)
    /* 4F3F0 80074040 3C04800F */  lui        $a0, %hi(D_800EDFBC)
    /* 4F3F4 80074044 2484DFBC */  addiu      $a0, $a0, %lo(D_800EDFBC)
    /* 4F3F8 80074048 0C00A5D8 */  jal        func_80029760
    /* 4F3FC 8007404C 032E2823 */   subu      $a1, $t9, $t6
    /* 4F400 80074050 3C10800F */  lui        $s0, %hi(D_800F22C0)
    /* 4F404 80074054 8E1022C0 */  lw         $s0, %lo(D_800F22C0)($s0)
    /* 4F408 80074058 0C01CAA5 */  jal        func_80072A94
    /* 4F40C 8007405C 00000000 */   nop
    /* 4F410 80074060 0C01CBC6 */  jal        func_80072F18
    /* 4F414 80074064 00000000 */   nop
    /* 4F418 80074068 3C02800F */  lui        $v0, %hi(D_800F22C0)
    /* 4F41C 8007406C 8C4222C0 */  lw         $v0, %lo(D_800F22C0)($v0)
    /* 4F420 80074070 3C038014 */  lui        $v1, %hi(D_8013E474)
    /* 4F424 80074074 2463E474 */  addiu      $v1, $v1, %lo(D_8013E474)
    /* 4F428 80074078 3C018014 */  lui        $at, %hi(D_8013DD08)
    /* 4F42C 8007407C 3C04800F */  lui        $a0, %hi(D_800EDFE4)
    /* 4F430 80074080 AC620000 */  sw         $v0, 0x0($v1)
    /* 4F434 80074084 2484DFE4 */  addiu      $a0, $a0, %lo(D_800EDFE4)
    /* 4F438 80074088 AC22DD08 */  sw         $v0, %lo(D_8013DD08)($at)
    /* 4F43C 8007408C 0C00A5D8 */  jal        func_80029760
    /* 4F440 80074090 00502823 */   subu      $a1, $v0, $s0
    /* 4F444 80074094 3C06800F */  lui        $a2, %hi(D_800F22C0)
    /* 4F448 80074098 8CC622C0 */  lw         $a2, %lo(D_800F22C0)($a2)
    /* 4F44C 8007409C 8FAC0040 */  lw         $t4, 0x40($sp)
    /* 4F450 800740A0 3C04800F */  lui        $a0, %hi(D_800EE010)
    /* 4F454 800740A4 2484E010 */  addiu      $a0, $a0, %lo(D_800EE010)
    /* 4F458 800740A8 0C00A5D8 */  jal        func_80029760
    /* 4F45C 800740AC 00CC2823 */   subu      $a1, $a2, $t4
    /* 4F460 800740B0 8FBF0024 */  lw         $ra, 0x24($sp)
    /* 4F464 800740B4 8FB0001C */  lw         $s0, 0x1C($sp)
    /* 4F468 800740B8 8FB10020 */  lw         $s1, 0x20($sp)
    /* 4F46C 800740BC 03E00008 */  jr         $ra
    /* 4F470 800740C0 27BD0050 */   addiu     $sp, $sp, 0x50

glabel func_800BA694
    /* 95A44 800BA694 27BDFFA8 */  addiu      $sp, $sp, -0x58
    /* 95A48 800BA698 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 95A4C 800BA69C 908E001A */  lbu        $t6, 0x1A($a0)
    /* 95A50 800BA6A0 00803825 */  or         $a3, $a0, $zero
    /* 95A54 800BA6A4 11C0013F */  beqz       $t6, .L800BABA4
    /* 95A58 800BA6A8 3C058016 */   lui       $a1, %hi(D_80160C64)
    /* 95A5C 800BA6AC 24A50C64 */  addiu      $a1, $a1, %lo(D_80160C64)
    /* 95A60 800BA6B0 84A30000 */  lh         $v1, 0x0($a1)
    /* 95A64 800BA6B4 84820018 */  lh         $v0, 0x18($a0)
    /* 95A68 800BA6B8 00000000 */  nop
    /* 95A6C 800BA6BC 0043082A */  slt        $at, $v0, $v1
    /* 95A70 800BA6C0 10200005 */  beqz       $at, .L800BA6D8
    /* 95A74 800BA6C4 00437823 */   subu      $t7, $v0, $v1
    /* 95A78 800BA6C8 0C02E98A */  jal        func_800BA628
    /* 95A7C 800BA6CC 00000000 */   nop
    /* 95A80 800BA6D0 10000135 */  b          .L800BABA8
    /* 95A84 800BA6D4 8FBF0014 */   lw        $ra, 0x14($sp)
  .L800BA6D8:
    /* 95A88 800BA6D8 A4EF0018 */  sh         $t7, 0x18($a3)
    /* 95A8C 800BA6DC 84B90000 */  lh         $t9, 0x0($a1)
    /* 95A90 800BA6E0 8CF8000C */  lw         $t8, 0xC($a3)
    /* 95A94 800BA6E4 8CE30008 */  lw         $v1, 0x8($a3)
    /* 95A98 800BA6E8 03190019 */  multu      $t8, $t9
    /* 95A9C 800BA6EC 8CE40010 */  lw         $a0, 0x10($a3)
    /* 95AA0 800BA6F0 3C0A8016 */  lui        $t2, %hi(D_80160C80)
    /* 95AA4 800BA6F4 00044C03 */  sra        $t1, $a0, 16
    /* 95AA8 800BA6F8 00007012 */  mflo       $t6
    /* 95AAC 800BA6FC 006E7821 */  addu       $t7, $v1, $t6
    /* 95AB0 800BA700 05210002 */  bgez       $t1, .L800BA70C
    /* 95AB4 800BA704 ACEF0008 */   sw        $t7, 0x8($a3)
    /* 95AB8 800BA708 00004825 */  or         $t1, $zero, $zero
  .L800BA70C:
    /* 95ABC 800BA70C 29210100 */  slti       $at, $t1, 0x100
    /* 95AC0 800BA710 14200002 */  bnez       $at, .L800BA71C
    /* 95AC4 800BA714 00000000 */   nop
    /* 95AC8 800BA718 240900FF */  addiu      $t1, $zero, 0xFF
  .L800BA71C:
    /* 95ACC 800BA71C 8CF80014 */  lw         $t8, 0x14($a3)
    /* 95AD0 800BA720 84B90000 */  lh         $t9, 0x0($a1)
    /* 95AD4 800BA724 90E2001B */  lbu        $v0, 0x1B($a3)
    /* 95AD8 800BA728 03190019 */  multu      $t8, $t9
    /* 95ADC 800BA72C 30580001 */  andi       $t8, $v0, 0x1
    /* 95AE0 800BA730 03001025 */  or         $v0, $t8, $zero
    /* 95AE4 800BA734 3C018016 */  lui        $at, %hi(D_80160C78)
    /* 95AE8 800BA738 3C058016 */  lui        $a1, %hi(D_80160C7C)
    /* 95AEC 800BA73C 00007012 */  mflo       $t6
    /* 95AF0 800BA740 008E7821 */  addu       $t7, $a0, $t6
    /* 95AF4 800BA744 17000022 */  bnez       $t8, .L800BA7D0
    /* 95AF8 800BA748 ACEF0010 */   sw        $t7, 0x10($a3)
    /* 95AFC 800BA74C 84F90002 */  lh         $t9, 0x2($a3)
    /* 95B00 800BA750 0003C403 */  sra        $t8, $v1, 16
    /* 95B04 800BA754 AC390C78 */  sw         $t9, %lo(D_80160C78)($at)
    /* 95B08 800BA758 84EE0004 */  lh         $t6, 0x4($a3)
    /* 95B0C 800BA75C 3C018016 */  lui        $at, %hi(D_80160C7C)
    /* 95B10 800BA760 AC2E0C7C */  sw         $t6, %lo(D_80160C7C)($at)
    /* 95B14 800BA764 84EF0006 */  lh         $t7, 0x6($a3)
    /* 95B18 800BA768 3C018016 */  lui        $at, %hi(D_80160C80)
    /* 95B1C 800BA76C AC2F0C80 */  sw         $t7, %lo(D_80160C80)($at)
    /* 95B20 800BA770 8CA50C7C */  lw         $a1, %lo(D_80160C7C)($a1)
    /* 95B24 800BA774 8D4A0C80 */  lw         $t2, %lo(D_80160C80)($t2)
    /* 95B28 800BA778 3C048016 */  lui        $a0, %hi(D_80160C78)
    /* 95B2C 800BA77C 8C840C78 */  lw         $a0, %lo(D_80160C78)($a0)
    /* 95B30 800BA780 00B84023 */  subu       $t0, $a1, $t8
    /* 95B34 800BA784 00B86821 */  addu       $t5, $a1, $t8
    /* 95B38 800BA788 00983021 */  addu       $a2, $a0, $t8
    /* 95B3C 800BA78C AFA60044 */  sw         $a2, 0x44($sp)
    /* 95B40 800BA790 AFA8004C */  sw         $t0, 0x4C($sp)
    /* 95B44 800BA794 AFAD0034 */  sw         $t5, 0x34($sp)
    /* 95B48 800BA798 AFAA0030 */  sw         $t2, 0x30($sp)
    /* 95B4C 800BA79C AFAA003C */  sw         $t2, 0x3C($sp)
    /* 95B50 800BA7A0 AFAA0048 */  sw         $t2, 0x48($sp)
    /* 95B54 800BA7A4 90E2001B */  lbu        $v0, 0x1B($a3)
    /* 95B58 800BA7A8 00986023 */  subu       $t4, $a0, $t8
    /* 95B5C 800BA7AC 30590001 */  andi       $t9, $v0, 0x1
    /* 95B60 800BA7B0 03001825 */  or         $v1, $t8, $zero
    /* 95B64 800BA7B4 03201025 */  or         $v0, $t9, $zero
    /* 95B68 800BA7B8 AFAC002C */  sw         $t4, 0x2C($sp)
    /* 95B6C 800BA7BC AFAC0050 */  sw         $t4, 0x50($sp)
    /* 95B70 800BA7C0 AFAD0028 */  sw         $t5, 0x28($sp)
    /* 95B74 800BA7C4 AFA80040 */  sw         $t0, 0x40($sp)
    /* 95B78 800BA7C8 AFA60038 */  sw         $a2, 0x38($sp)
    /* 95B7C 800BA7CC AFAA0024 */  sw         $t2, 0x24($sp)
  .L800BA7D0:
    /* 95B80 800BA7D0 8FA60038 */  lw         $a2, 0x38($sp)
    /* 95B84 800BA7D4 8FA80040 */  lw         $t0, 0x40($sp)
    /* 95B88 800BA7D8 8FAA0024 */  lw         $t2, 0x24($sp)
    /* 95B8C 800BA7DC 8FAC002C */  lw         $t4, 0x2C($sp)
    /* 95B90 800BA7E0 8FAD0028 */  lw         $t5, 0x28($sp)
    /* 95B94 800BA7E4 8FBF0050 */  lw         $ra, 0x50($sp)
    /* 95B98 800BA7E8 1040005E */  beqz       $v0, .L800BA964
    /* 95B9C 800BA7EC 00000000 */   nop
    /* 95BA0 800BA7F0 84E40002 */  lh         $a0, 0x2($a3)
    /* 95BA4 800BA7F4 84E50004 */  lh         $a1, 0x4($a3)
    /* 95BA8 800BA7F8 84E60006 */  lh         $a2, 0x6($a3)
    /* 95BAC 800BA7FC AFA90020 */  sw         $t1, 0x20($sp)
    /* 95BB0 800BA800 0C026363 */  jal        func_80098D8C
    /* 95BB4 800BA804 AFA3001C */   sw        $v1, 0x1C($sp)
    /* 95BB8 800BA808 8FA3001C */  lw         $v1, 0x1C($sp)
    /* 95BBC 800BA80C 8FA90020 */  lw         $t1, 0x20($sp)
    /* 95BC0 800BA810 144000E4 */  bnez       $v0, .L800BABA4
    /* 95BC4 800BA814 3C0E8016 */   lui       $t6, %hi(D_8015ED9C)
    /* 95BC8 800BA818 85CEED9C */  lh         $t6, %lo(D_8015ED9C)($t6)
    /* 95BCC 800BA81C 3C198016 */  lui        $t9, %hi(D_8015EDA4)
    /* 95BD0 800BA820 01C30019 */  multu      $t6, $v1
    /* 95BD4 800BA824 8739EDA4 */  lh         $t9, %lo(D_8015EDA4)($t9)
    /* 95BD8 800BA828 3C048016 */  lui        $a0, %hi(D_80160C78)
    /* 95BDC 800BA82C 8C840C78 */  lw         $a0, %lo(D_80160C78)($a0)
    /* 95BE0 800BA830 3C058016 */  lui        $a1, %hi(D_80160C7C)
    /* 95BE4 800BA834 8CA50C7C */  lw         $a1, %lo(D_80160C7C)($a1)
    /* 95BE8 800BA838 3C028016 */  lui        $v0, %hi(D_80160C80)
    /* 95BEC 800BA83C 8C420C80 */  lw         $v0, %lo(D_80160C80)($v0)
    /* 95BF0 800BA840 00007812 */  mflo       $t7
    /* 95BF4 800BA844 000FC403 */  sra        $t8, $t7, 16
    /* 95BF8 800BA848 0304F821 */  addu       $ra, $t8, $a0
    /* 95BFC 800BA84C 03230019 */  multu      $t9, $v1
    /* 95C00 800BA850 3C198016 */  lui        $t9, %hi(D_8015EDAC)
    /* 95C04 800BA854 8739EDAC */  lh         $t9, %lo(D_8015EDAC)($t9)
    /* 95C08 800BA858 00007012 */  mflo       $t6
    /* 95C0C 800BA85C 000E7C03 */  sra        $t7, $t6, 16
    /* 95C10 800BA860 01E5C021 */  addu       $t8, $t7, $a1
    /* 95C14 800BA864 03230019 */  multu      $t9, $v1
    /* 95C18 800BA868 3C198016 */  lui        $t9, %hi(D_8015EDB0)
    /* 95C1C 800BA86C 8739EDB0 */  lh         $t9, %lo(D_8015EDB0)($t9)
    /* 95C20 800BA870 AFB8004C */  sw         $t8, 0x4C($sp)
    /* 95C24 800BA874 00007012 */  mflo       $t6
    /* 95C28 800BA878 000E7C03 */  sra        $t7, $t6, 16
    /* 95C2C 800BA87C 01E2C021 */  addu       $t8, $t7, $v0
    /* 95C30 800BA880 03230019 */  multu      $t9, $v1
    /* 95C34 800BA884 3C198016 */  lui        $t9, %hi(D_8015EDB4)
    /* 95C38 800BA888 8739EDB4 */  lh         $t9, %lo(D_8015EDB4)($t9)
    /* 95C3C 800BA88C AFB80048 */  sw         $t8, 0x48($sp)
    /* 95C40 800BA890 00007012 */  mflo       $t6
    /* 95C44 800BA894 000E7C03 */  sra        $t7, $t6, 16
    /* 95C48 800BA898 01E4C021 */  addu       $t8, $t7, $a0
    /* 95C4C 800BA89C 03230019 */  multu      $t9, $v1
    /* 95C50 800BA8A0 AFB80044 */  sw         $t8, 0x44($sp)
    /* 95C54 800BA8A4 3C188016 */  lui        $t8, %hi(D_8015EDB8)
    /* 95C58 800BA8A8 8718EDB8 */  lh         $t8, %lo(D_8015EDB8)($t8)
    /* 95C5C 800BA8AC 00007012 */  mflo       $t6
    /* 95C60 800BA8B0 000E7C03 */  sra        $t7, $t6, 16
    /* 95C64 800BA8B4 01E54021 */  addu       $t0, $t7, $a1
    /* 95C68 800BA8B8 03030019 */  multu      $t8, $v1
    /* 95C6C 800BA8BC 3C188016 */  lui        $t8, %hi(D_8015EDBC)
    /* 95C70 800BA8C0 8718EDBC */  lh         $t8, %lo(D_8015EDBC)($t8)
    /* 95C74 800BA8C4 0000C812 */  mflo       $t9
    /* 95C78 800BA8C8 00197403 */  sra        $t6, $t9, 16
    /* 95C7C 800BA8CC 01C27821 */  addu       $t7, $t6, $v0
    /* 95C80 800BA8D0 03030019 */  multu      $t8, $v1
    /* 95C84 800BA8D4 AFAF003C */  sw         $t7, 0x3C($sp)
    /* 95C88 800BA8D8 3C0F8016 */  lui        $t7, %hi(D_8015EE1A)
    /* 95C8C 800BA8DC 85EFEE1A */  lh         $t7, %lo(D_8015EE1A)($t7)
    /* 95C90 800BA8E0 0000C812 */  mflo       $t9
    /* 95C94 800BA8E4 00197403 */  sra        $t6, $t9, 16
    /* 95C98 800BA8E8 01C43021 */  addu       $a2, $t6, $a0
    /* 95C9C 800BA8EC 01E30019 */  multu      $t7, $v1
    /* 95CA0 800BA8F0 3C0F8016 */  lui        $t7, %hi(D_8015EEC8)
    /* 95CA4 800BA8F4 85EFEEC8 */  lh         $t7, %lo(D_8015EEC8)($t7)
    /* 95CA8 800BA8F8 0000C012 */  mflo       $t8
    /* 95CAC 800BA8FC 0018CC03 */  sra        $t9, $t8, 16
    /* 95CB0 800BA900 03257021 */  addu       $t6, $t9, $a1
    /* 95CB4 800BA904 01E30019 */  multu      $t7, $v1
    /* 95CB8 800BA908 3C0F8016 */  lui        $t7, %hi(D_8015F4D2)
    /* 95CBC 800BA90C 85EFF4D2 */  lh         $t7, %lo(D_8015F4D2)($t7)
    /* 95CC0 800BA910 AFAE0034 */  sw         $t6, 0x34($sp)
    /* 95CC4 800BA914 0000C012 */  mflo       $t8
    /* 95CC8 800BA918 0018CC03 */  sra        $t9, $t8, 16
    /* 95CCC 800BA91C 03227021 */  addu       $t6, $t9, $v0
    /* 95CD0 800BA920 01E30019 */  multu      $t7, $v1
    /* 95CD4 800BA924 AFAE0030 */  sw         $t6, 0x30($sp)
    /* 95CD8 800BA928 3C0E8016 */  lui        $t6, %hi(D_8015F4DC)
    /* 95CDC 800BA92C 85CEF4DC */  lh         $t6, %lo(D_8015F4DC)($t6)
    /* 95CE0 800BA930 0000C012 */  mflo       $t8
    /* 95CE4 800BA934 0018CC03 */  sra        $t9, $t8, 16
    /* 95CE8 800BA938 03246021 */  addu       $t4, $t9, $a0
    /* 95CEC 800BA93C 01C30019 */  multu      $t6, $v1
    /* 95CF0 800BA940 3C198016 */  lui        $t9, %hi(D_8015F4E0)
    /* 95CF4 800BA944 8739F4E0 */  lh         $t9, %lo(D_8015F4E0)($t9)
    /* 95CF8 800BA948 00007812 */  mflo       $t7
    /* 95CFC 800BA94C 000FC403 */  sra        $t8, $t7, 16
    /* 95D00 800BA950 03056821 */  addu       $t5, $t8, $a1
    /* 95D04 800BA954 03230019 */  multu      $t9, $v1
    /* 95D08 800BA958 00007012 */  mflo       $t6
    /* 95D0C 800BA95C 000E7C03 */  sra        $t7, $t6, 16
    /* 95D10 800BA960 01E25021 */  addu       $t2, $t7, $v0
  .L800BA964:
    /* 95D14 800BA964 3C028016 */  lui        $v0, %hi(D_8015F848)
    /* 95D18 800BA968 2442F848 */  addiu      $v0, $v0, %lo(D_8015F848)
    /* 95D1C 800BA96C 8C580000 */  lw         $t8, 0x0($v0)
    /* 95D20 800BA970 240400FF */  addiu      $a0, $zero, 0xFF
    /* 95D24 800BA974 A71F0000 */  sh         $ra, 0x0($t8)
    /* 95D28 800BA978 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95D2C 800BA97C 8FB9004C */  lw         $t9, 0x4C($sp)
    /* 95D30 800BA980 240B07C0 */  addiu      $t3, $zero, 0x7C0
    /* 95D34 800BA984 A5D90002 */  sh         $t9, 0x2($t6)
    /* 95D38 800BA988 8C580000 */  lw         $t8, 0x0($v0)
    /* 95D3C 800BA98C 8FAF0048 */  lw         $t7, 0x48($sp)
    /* 95D40 800BA990 3C05800F */  lui        $a1, %hi(D_800F22B4)
    /* 95D44 800BA994 A70F0004 */  sh         $t7, 0x4($t8)
    /* 95D48 800BA998 8C590000 */  lw         $t9, 0x0($v0)
    /* 95D4C 800BA99C 24A522B4 */  addiu      $a1, $a1, %lo(D_800F22B4)
    /* 95D50 800BA9A0 A7200008 */  sh         $zero, 0x8($t9)
    /* 95D54 800BA9A4 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95D58 800BA9A8 3C1FBF00 */  lui        $ra, (0xBF000000 >> 16)
    /* 95D5C 800BA9AC A5C0000A */  sh         $zero, 0xA($t6)
    /* 95D60 800BA9B0 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95D64 800BA9B4 3C01800E */  lui        $at, %hi(D_800E44F0)
    /* 95D68 800BA9B8 A1E4000C */  sb         $a0, 0xC($t7)
    /* 95D6C 800BA9BC 8C580000 */  lw         $t8, 0x0($v0)
    /* 95D70 800BA9C0 00000000 */  nop
    /* 95D74 800BA9C4 A304000D */  sb         $a0, 0xD($t8)
    /* 95D78 800BA9C8 8C590000 */  lw         $t9, 0x0($v0)
    /* 95D7C 800BA9CC 00000000 */  nop
    /* 95D80 800BA9D0 A324000E */  sb         $a0, 0xE($t9)
    /* 95D84 800BA9D4 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95D88 800BA9D8 00000000 */  nop
    /* 95D8C 800BA9DC A1C9000F */  sb         $t1, 0xF($t6)
    /* 95D90 800BA9E0 8C580000 */  lw         $t8, 0x0($v0)
    /* 95D94 800BA9E4 8FAF0044 */  lw         $t7, 0x44($sp)
    /* 95D98 800BA9E8 00000000 */  nop
    /* 95D9C 800BA9EC A70F0010 */  sh         $t7, 0x10($t8)
    /* 95DA0 800BA9F0 8C590000 */  lw         $t9, 0x0($v0)
    /* 95DA4 800BA9F4 00000000 */  nop
    /* 95DA8 800BA9F8 A7280012 */  sh         $t0, 0x12($t9)
    /* 95DAC 800BA9FC 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95DB0 800BAA00 8FAE003C */  lw         $t6, 0x3C($sp)
    /* 95DB4 800BAA04 00000000 */  nop
    /* 95DB8 800BAA08 A5EE0014 */  sh         $t6, 0x14($t7)
    /* 95DBC 800BAA0C 8C580000 */  lw         $t8, 0x0($v0)
    /* 95DC0 800BAA10 00000000 */  nop
    /* 95DC4 800BAA14 A70B0018 */  sh         $t3, 0x18($t8)
    /* 95DC8 800BAA18 8C590000 */  lw         $t9, 0x0($v0)
    /* 95DCC 800BAA1C 00000000 */  nop
    /* 95DD0 800BAA20 A720001A */  sh         $zero, 0x1A($t9)
    /* 95DD4 800BAA24 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95DD8 800BAA28 00000000 */  nop
    /* 95DDC 800BAA2C A1C4001C */  sb         $a0, 0x1C($t6)
    /* 95DE0 800BAA30 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95DE4 800BAA34 00000000 */  nop
    /* 95DE8 800BAA38 A1E4001D */  sb         $a0, 0x1D($t7)
    /* 95DEC 800BAA3C 8C580000 */  lw         $t8, 0x0($v0)
    /* 95DF0 800BAA40 00000000 */  nop
    /* 95DF4 800BAA44 A304001E */  sb         $a0, 0x1E($t8)
    /* 95DF8 800BAA48 8C590000 */  lw         $t9, 0x0($v0)
    /* 95DFC 800BAA4C 00000000 */  nop
    /* 95E00 800BAA50 A329001F */  sb         $t1, 0x1F($t9)
    /* 95E04 800BAA54 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95E08 800BAA58 00000000 */  nop
    /* 95E0C 800BAA5C A5C60020 */  sh         $a2, 0x20($t6)
    /* 95E10 800BAA60 8C580000 */  lw         $t8, 0x0($v0)
    /* 95E14 800BAA64 8FAF0034 */  lw         $t7, 0x34($sp)
    /* 95E18 800BAA68 00000000 */  nop
    /* 95E1C 800BAA6C A70F0022 */  sh         $t7, 0x22($t8)
    /* 95E20 800BAA70 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95E24 800BAA74 8FB90030 */  lw         $t9, 0x30($sp)
    /* 95E28 800BAA78 00000000 */  nop
    /* 95E2C 800BAA7C A5D90024 */  sh         $t9, 0x24($t6)
    /* 95E30 800BAA80 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95E34 800BAA84 00000000 */  nop
    /* 95E38 800BAA88 A5EB0028 */  sh         $t3, 0x28($t7)
    /* 95E3C 800BAA8C 8C580000 */  lw         $t8, 0x0($v0)
    /* 95E40 800BAA90 00000000 */  nop
    /* 95E44 800BAA94 A70B002A */  sh         $t3, 0x2A($t8)
    /* 95E48 800BAA98 8C590000 */  lw         $t9, 0x0($v0)
    /* 95E4C 800BAA9C 00000000 */  nop
    /* 95E50 800BAAA0 A324002C */  sb         $a0, 0x2C($t9)
    /* 95E54 800BAAA4 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95E58 800BAAA8 00000000 */  nop
    /* 95E5C 800BAAAC A1C4002D */  sb         $a0, 0x2D($t6)
    /* 95E60 800BAAB0 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95E64 800BAAB4 00000000 */  nop
    /* 95E68 800BAAB8 A1E4002E */  sb         $a0, 0x2E($t7)
    /* 95E6C 800BAABC 8C580000 */  lw         $t8, 0x0($v0)
    /* 95E70 800BAAC0 00000000 */  nop
    /* 95E74 800BAAC4 A309002F */  sb         $t1, 0x2F($t8)
    /* 95E78 800BAAC8 8C590000 */  lw         $t9, 0x0($v0)
    /* 95E7C 800BAACC 00000000 */  nop
    /* 95E80 800BAAD0 A72C0030 */  sh         $t4, 0x30($t9)
    /* 95E84 800BAAD4 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95E88 800BAAD8 00000000 */  nop
    /* 95E8C 800BAADC A5CD0032 */  sh         $t5, 0x32($t6)
    /* 95E90 800BAAE0 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95E94 800BAAE4 00000000 */  nop
    /* 95E98 800BAAE8 A5EA0034 */  sh         $t2, 0x34($t7)
    /* 95E9C 800BAAEC 8C580000 */  lw         $t8, 0x0($v0)
    /* 95EA0 800BAAF0 00000000 */  nop
    /* 95EA4 800BAAF4 A7000038 */  sh         $zero, 0x38($t8)
    /* 95EA8 800BAAF8 8C590000 */  lw         $t9, 0x0($v0)
    /* 95EAC 800BAAFC 00000000 */  nop
    /* 95EB0 800BAB00 A72B003A */  sh         $t3, 0x3A($t9)
    /* 95EB4 800BAB04 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 95EB8 800BAB08 00000000 */  nop
    /* 95EBC 800BAB0C A1C4003C */  sb         $a0, 0x3C($t6)
    /* 95EC0 800BAB10 8C4F0000 */  lw         $t7, 0x0($v0)
    /* 95EC4 800BAB14 00000000 */  nop
    /* 95EC8 800BAB18 A1E4003D */  sb         $a0, 0x3D($t7)
    /* 95ECC 800BAB1C 8C580000 */  lw         $t8, 0x0($v0)
    /* 95ED0 800BAB20 3C0F0430 */  lui        $t7, (0x4300040 >> 16)
    /* 95ED4 800BAB24 A304003E */  sb         $a0, 0x3E($t8)
    /* 95ED8 800BAB28 8C590000 */  lw         $t9, 0x0($v0)
    /* 95EDC 800BAB2C 35EF0040 */  ori        $t7, $t7, (0x4300040 & 0xFFFF)
    /* 95EE0 800BAB30 A329003F */  sb         $t1, 0x3F($t9)
    /* 95EE4 800BAB34 8CA30000 */  lw         $v1, 0x0($a1)
    /* 95EE8 800BAB38 00000000 */  nop
    /* 95EEC 800BAB3C 246E0008 */  addiu      $t6, $v1, 0x8
    /* 95EF0 800BAB40 ACAE0000 */  sw         $t6, 0x0($a1)
    /* 95EF4 800BAB44 AC6F0000 */  sw         $t7, 0x0($v1)
    /* 95EF8 800BAB48 8C580000 */  lw         $t8, 0x0($v0)
    /* 95EFC 800BAB4C 240E0A14 */  addiu      $t6, $zero, 0xA14
    /* 95F00 800BAB50 AC780004 */  sw         $t8, 0x4($v1)
    /* 95F04 800BAB54 8CA30000 */  lw         $v1, 0x0($a1)
    /* 95F08 800BAB58 3C180214 */  lui        $t8, (0x2141E00 >> 16)
    /* 95F0C 800BAB5C 24790008 */  addiu      $t9, $v1, 0x8
    /* 95F10 800BAB60 ACB90000 */  sw         $t9, 0x0($a1)
    /* 95F14 800BAB64 AC6E0004 */  sw         $t6, 0x4($v1)
    /* 95F18 800BAB68 AC7F0000 */  sw         $ra, 0x0($v1)
    /* 95F1C 800BAB6C 8CA30000 */  lw         $v1, 0x0($a1)
    /* 95F20 800BAB70 37181E00 */  ori        $t8, $t8, (0x2141E00 & 0xFFFF)
    /* 95F24 800BAB74 246F0008 */  addiu      $t7, $v1, 0x8
    /* 95F28 800BAB78 ACAF0000 */  sw         $t7, 0x0($a1)
    /* 95F2C 800BAB7C AC780004 */  sw         $t8, 0x4($v1)
    /* 95F30 800BAB80 AC7F0000 */  sw         $ra, 0x0($v1)
    /* 95F34 800BAB84 8C590000 */  lw         $t9, 0x0($v0)
    /* 95F38 800BAB88 3C0F800E */  lui        $t7, %hi(D_800E44F0)
    /* 95F3C 800BAB8C 272E0040 */  addiu      $t6, $t9, 0x40
    /* 95F40 800BAB90 AC4E0000 */  sw         $t6, 0x0($v0)
    /* 95F44 800BAB94 8DEF44F0 */  lw         $t7, %lo(D_800E44F0)($t7)
    /* 95F48 800BAB98 00000000 */  nop
    /* 95F4C 800BAB9C 25F80004 */  addiu      $t8, $t7, 0x4
    /* 95F50 800BABA0 AC3844F0 */  sw         $t8, %lo(D_800E44F0)($at)
  .L800BABA4:
    /* 95F54 800BABA4 8FBF0014 */  lw         $ra, 0x14($sp)
  .L800BABA8:
    /* 95F58 800BABA8 27BD0058 */  addiu      $sp, $sp, 0x58
    /* 95F5C 800BABAC 03E00008 */  jr         $ra
    /* 95F60 800BABB0 00000000 */   nop

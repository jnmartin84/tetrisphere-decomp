/* Standalone port of Tetrisphere's LW-engine 'J' filter (func_80081444 +
 * func_80081264) — an LZ77-on-u16 codec. Ported verbatim from src/code_5B5D0.c.
 * Decodes one sub-asset from assets/CD3F0.bin and dumps the result.
 * usage: lwdec <blob> <archive_rom_hex> <asset_idx> [out.bin] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char u8; typedef unsigned short u16; typedef int s32; typedef unsigned int u32;

#define BASE 0xCD3F0
static u8 *blob; static long blen;
static u32 be16(long o){return (blob[o]<<8)|blob[o+1];}
static u32 be32(long o){return (blob[o]<<24)|(blob[o+1]<<16)|(blob[o+2]<<8)|blob[o+3];}

static void func_80080220(u8 *d,u8 *s,s32 n){while(n--)*d++=*s++;}

/* LZ inner: arg0=src, arg1=dst(u16 units), arg2=complen. Verbatim. */
static s32 func_80081264(u8 *arg0, u16 *arg1, s32 arg2){
  s32 spC,sp8,sp4,sp0; sp0=0; spC=0;
  if(spC<arg2){ do {
    sp8=arg0[spC]; spC+=1;
    if(sp8&0x80){                                   /* back-reference */
      sp8=(sp8&0x7F)+1;
      sp4=(arg0[spC]<<8)|arg0[spC+1]; spC+=2;
      if(sp8!=0){ do { arg1[sp0]=arg1[sp4]; sp0+=1; sp4+=1; sp8-=1; } while(sp8!=0); }
    } else {                                        /* literal run */
      sp8+=1;
      if(sp8!=0){ do { arg1[sp0]=(arg0[spC]<<8)|arg0[spC+1]; sp0+=1; spC+=2; sp8-=1; } while(sp8!=0); }
    }
  } while(spC<arg2); }
  return sp0*2;
}

/* 'J' filter: block loop. arg0=src, arg1=dst, arg2=srclen. Verbatim. */
static s32 func_80081444(u8 *arg0, u8 *dst, s32 arg2){
  s32 sp24,sp20,sp1C; u8 *arg1=dst; sp1C=0;
  if(arg2!=0){ do {
    sp24=(arg0[4]<<24)|(arg0[5]<<16)|(arg0[6]<<8)|arg0[7];   /* uncompressed size */
    sp20=(arg0[8]<<24)|(arg0[9]<<16)|(arg0[0xA]<<8)|arg0[0xB]; /* compressed size */
    arg0+=0xC; arg2-=0xC;
    if(sp24==sp20) func_80080220(arg1,arg0,sp20);            /* stored */
    else func_80081264(arg0,(u16*)arg1,sp20);               /* LZ */
    arg1+=((sp24+1)/2)*2; arg0+=sp20; arg2-=sp20; sp1C+=sp24;
  } while(arg2!=0); }
  return sp1C;
}

int main(int argc,char**argv){
  if(argc<4){fprintf(stderr,"usage: lwdec blob archive_hex idx [out]\n");return 2;}
  FILE*f=fopen(argv[1],"rb"); fseek(f,0,SEEK_END); blen=ftell(f); fseek(f,0,SEEK_SET);
  blob=malloc(blen); fread(blob,1,blen,f); fclose(f);
  long rom=strtol(argv[2],0,16); int idx=atoi(argv[3]);
  long o=rom-BASE;
  u32 cnt=be16(o);
  u32 off0=be32(o+2+idx*4), off1=be32(o+2+(idx+1)*4);
  long d=o+off0; long subsz=off1-off0;
  u8 nops=blob[d];
  char ops[32]; memcpy(ops,blob+d+1,nops); ops[nops]=0;
  u32 size=be32(d+1+nops);
  u8 *payload=blob+d+1+nops+4;
  printf("archive 0x%lX idx %d: count=%u  sub-asset=0x%lX bytes\n",rom,idx,cnt,subsz);
  printf("  header: numOps=%u ops=\"%s\" declSize=0x%X  payload@+0x%lX\n",nops,ops,size,(d+1+nops+4)-d);
  if(nops!=1||ops[0]!='J'){printf("  (not a single-'J' asset; this tool only does J)\n");return 1;}
  u8 *out=malloc(64*1024*1024);
  s32 n=func_80081444(payload,out,(s32)size);
  printf("  DECODED %d bytes (%.2fx expansion)\n",n,(double)n/subsz);
  printf("  first 48 bytes: ");
  for(int i=0;i<48&&i<n;i++)printf("%02X%s",out[i],(i%16==15)?"\n                  ":" ");
  printf("\n");
  if(argc>4){FILE*g=fopen(argv[4],"wb");fwrite(out,1,n,g);fclose(g);printf("  wrote %s\n",argv[4]);}
  return 0;
}

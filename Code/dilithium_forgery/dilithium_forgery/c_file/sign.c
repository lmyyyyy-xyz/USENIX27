#include <stdint.h>
#include "params.h"
#include "sign.h"
#include "packing.h"
#include "polyvec.h"
#include "poly.h"
#include "randombytes.h"
#include "symmetric.h"
#include "fips202.h"


#include <stdio.h>
#include <unistd.h>

#ifndef F_OK
#define F_OK 0
#endif


void write_to_file(char *filename,int32_t data_array[],int size){
FILE* file = fopen(filename, "a");

if (file == NULL) {
        printf("无法打开文件。\n");
        //return 1;
    }
    
   fseek(file, 0, SEEK_END);
    //char data[20];
  //printf("\n%d\n",sizeof(data_array) / sizeof(uint8_t));
   // int ii;
	size_t i;
    for (i = 0; i < size; i++) {
        fprintf(file, "%d ", data_array[i]);
        //fprintf(file,' ');
    }
     
     fprintf(file, "\n");
    
    fclose(file);
}

/*************************************************
* Name:        crypto_sign_keypair
*
* Description: Generates public and private key.
*
* Arguments:   - uint8_t *pk: pointer to output public key (allocated
*                             array of CRYPTO_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key (allocated
*                             array of CRYPTO_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int crypto_sign_keypair(uint8_t *pk, uint8_t *sk) {
  uint8_t seedbuf[3*SEEDBYTES];
  uint8_t tr[CRHBYTES];
  const uint8_t *rho, *rhoprime, *key;
  polyvecl mat[K];
  polyvecl s1, s1hat;
  polyveck s2, t1, t0;

  /* Get randomness for rho, rhoprime and key */
  randombytes(seedbuf, SEEDBYTES);
  shake256(seedbuf, 3*SEEDBYTES, seedbuf, SEEDBYTES);
  rho = seedbuf;
  rhoprime = seedbuf + SEEDBYTES;
  key = seedbuf + 2*SEEDBYTES;

  /* Expand matrix */
  polyvec_matrix_expand(mat, rho);

  /* Sample short vectors s1 and s2 */
  polyvecl_uniform_eta(&s1, rhoprime, 0);
  polyveck_uniform_eta(&s2, rhoprime, L);

  /* Matrix-vector multiplication */
  s1hat = s1;
  polyvecl_ntt(&s1hat);
  polyvec_matrix_pointwise_montgomery(&t1, mat, &s1hat);
  polyveck_reduce(&t1);
  polyveck_invntt_tomont(&t1);

  /* Add error vector s2 */
  polyveck_add(&t1, &t1, &s2);

  /* Extract t1 and write public key */
  polyveck_caddq(&t1);
  polyveck_power2round(&t1, &t0, &t1);
  pack_pk(pk, rho, &t1);

  /* Compute CRH(rho, t1) and write secret key */
  crh(tr, pk, CRYPTO_PUBLICKEYBYTES);
  pack_sk(sk, rho, tr, key, &t0, &s1, &s2);

  return 0;
}
/*************************************************
* Name:        forgery_signature
*
* Description: Computes signature.
*
* Arguments:   - uint8_t *sig:   pointer to output signature (of length CRYPTO_BYTES)
*              - size_t *siglen: pointer to output length of signature
*              - uint8_t *m:     pointer to message to be signed
*              - size_t mlen:    length of message
*              - uint8_t *sk:    pointer to bit-packed secret key
*
* Returns 0 (success)
**************************************************/
int crypto_sign_signature(uint8_t *sig,
                          size_t *siglen,
                          const uint8_t *m,
                          size_t mlen,
                          const uint8_t *sk,
                          const uint8_t *pk,
                          int diedai)
{
  uint8_t *pk1 = pk;
  unsigned int n;
  FILE *file;
  uint8_t seedbuf[2*SEEDBYTES + 3*CRHBYTES];
  uint8_t *rho, *tr, *key, *mu, *rhoprime, *tr1;
  uint8_t rhoo[SEEDBYTES],rhooo[SEEDBYTES];
  uint16_t nonce = 0;
  polyvecl mat[K], s1, y, z,z1;
  polyveck t1,t0, s2, w1, w0, h,tmp;
  poly cp;
  keccak_state state;


  // unsigned int i;
  uint8_t buf[K*POLYW1_PACKEDBYTES];
  // uint8_t rho[SEEDBYTES];
  // uint8_t mu[CRHBYTES];
  // uint8_t c[SEEDBYTES];
  // uint8_t c2[SEEDBYTES];
  // poly cp;
  // polyvecl mat[K], z;
  // polyveck t1, w1, h;
  // keccak_state state;
  //---------------

  unpack_pk(rhoo, &t1, pk1);
  
  
  rho = seedbuf;
  tr = rho + SEEDBYTES;
  key = tr + CRHBYTES;
  mu = key + SEEDBYTES;
  rhoprime = mu + CRHBYTES;
  unpack_sk(rho, tr, key, &t0, &s1, &s2, sk);
  
  //crh(tr, pk1, CRYPTO_PUBLICKEYBYTES);
  
  /*printf("print tr\n");
  for(int i=0; i < CRHBYTES;i++)
  	printf("%d\n",tr[i]);
  printf("tr结束");
  
  printf("print tr1\n");
  for(int i=0; i < CRHBYTES;i++)
  	printf("%d\n",tr1[i]);
  printf("tr1结束");
  
  
  printf("print key");
  for(int i=0; i < SEEDBYTES;i++)
  	printf("%d\n",key[i]);
  printf("key结束");*/
  
  
  /*for(int i = 0; i < SEEDBYTES; ++i)
    rho[i] = pk[i];*/
  //unpack_pk(rhooo, &t1, pk);
  
  rho = rhoo;
  
  //读取s1==========================================
  
  char buffer[5000];
   file = fopen("../median_value/write_s1.txt", "r");
    
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    // 逐行读取文件内容
    int j=0;
    int k=0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
    	//printf("haha\n");
    	//printf("%s", buffer); // 打印每行内容
    	k =0;
    	int num=0;
    	//printf("%s\n",token);// 使用空格作为分隔符，将字符串分割成数字
    	while (num<256) {
    	 	int temp = 0;
    	 	//printf("%c ",buffer[2*num]);
    	 	if(DILITHIUM_MODE == 2 || DILITHIUM_MODE ==5){
    		if(buffer[2*num] == '3')
    			temp = -1;
    		if(buffer[2*num] == '4')
    			temp = -2;
    		if(buffer[2*num] == '1')
    			temp = 1;
    		if(buffer[2*num] == '2')
    			temp = 2;
    		}
    		else{
    		if(buffer[2*num] == '1')
    			temp = 1;
    		if(buffer[2*num] == '2')
    			temp = 2;
    		if(buffer[2*num] == '3')
    			temp = 3;
    		if(buffer[2*num] == '4')
    			temp = 4;
    		if(buffer[2*num] == '5')
    			temp = -1;
    		if(buffer[2*num] == '6')
    			temp = -2;
    		if(buffer[2*num] == '7')
    			temp = -3;
    		if(buffer[2*num] == '8')
    			temp = -4;
    		}
    		
    		//printf("%d\n",temp);
    		//printf("%s ", token);
		s1.vec[j].coeffs[k++] = temp;
		num++;
		 // 将提取的数字转换为整数并存入数组 // 继续提取下一个数字
	    }

        j++;
    }
    
     fclose(file);
     //=================================
     //输出s1
     int32_t buf_s1[L][256];
  
  for(int i=0; i < L;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_s1[i][j] = s1.vec[i].coeffs[j];
  }
  if (access("../median_value/ssss.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/ssss.txt") == 0) {
            printf("ssss文件删除成功\n");
        } else {
            printf("ssss文件删除失败\n");
        }
    } else {
        printf("ssss文件不存在\n");
    }
  for(int i=0; i < L ;i++)
  	write_to_file("../median_value/ssss.txt",buf_s1[i],256);
  	
  
     //===================================
     
     int32_t buf_ss[L][256];
  
  for(int i=0; i < L;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_ss[i][j] = s1.vec[i].coeffs[j];
  }
  if (access("../median_value/ss.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/ss.txt") == 0) {
            printf("ss文件删除成功\n");
        } else {
            printf("ss文件删除失败\n");
        }
    } else {
        printf("ss文件不存在\n");
    }
  for(int i=0; i < L ;i++)
  	write_to_file("../median_value/ss.txt",buf_ss[i],256);
     
  
  //==========================================
  

  /* Compute CRH(tr, msg) */
  
  //========================================================
  crh(mu, pk, CRYPTO_PUBLICKEYBYTES);
  shake256_init(&state);
  shake256_absorb(&state, mu, CRHBYTES);
  shake256_absorb(&state, m, mlen);
  shake256_finalize(&state);
  shake256_squeeze(mu, CRHBYTES, &state);
  
  
  //===========================================
  
  //====================注释
  /*shake256_init(&state);
  shake256_absorb(&state, tr, CRHBYTES);
  shake256_absorb(&state, m, mlen);
  shake256_finalize(&state);
  shake256_squeeze(mu, CRHBYTES, &state);*/
//================================================
#ifdef DILITHIUM_RANDOMIZED_SIGNING
  randombytes(rhoprime, CRHBYTES);
#else
  crh(rhoprime, key, SEEDBYTES + CRHBYTES);
#endif

  /* Expand matrix and transform vectors */
  polyvec_matrix_expand(mat, rho);
  polyvecl_ntt(&s1);
  //polyveck_ntt(&s2);
  //polyveck_ntt(&t0);

  /* Sample intermediate vector y */
  polyvecl_uniform_gamma1(&y, rhoprime, diedai++);
  z = y;
  polyvecl_ntt(&z);

  /* Matrix-vector multiplication */
  polyvec_matrix_pointwise_montgomery(&w1, mat, &z);
  polyveck_reduce(&w1);
  polyveck_invntt_tomont(&w1);


  /* Decompose w and call the random oracle */
  polyveck_caddq(&w1);
  polyveck_decompose(&w1, &w0, &w1);//取高位

  //------------------------------------
  //将w1返回到python文件中
  //输出w1到文件中
  int32_t buf_w1[K][256];
  for(int i=0; i < K;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_w1[i][j] = w1.vec[i].coeffs[j];
  }
  if (access("../median_value/w1.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/w1.txt") == 0) {
            printf("w1文件删除成功\n");
        } else {
            printf("w1文件删除失败\n");
        }
    } else {
        printf("w1文件不存在\n");
    }
  for(int i=0; i < K ;i++)
  	write_to_file("../median_value/w1.txt",buf_w1[i],256);
  //------------------------------------
  
  polyveck_pack_w1(sig, &w1);
   //------------------------------------
  //将s1返回到python文件中
  //------------------------------------

  shake256_init(&state);
  shake256_absorb(&state, mu, CRHBYTES);
  shake256_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
  shake256_finalize(&state);
  shake256_squeeze(sig, SEEDBYTES, &state);
  poly_challenge(&cp, sig);//生成挑战c的过程
  
  int32_t buf_c[256];
  
  for(int i=0; i < 256 ;i++)
  	buf_c[i] = cp.coeffs[i];
  	
  if (access("../median_value/c.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/c.txt") == 0) {
            printf("c文件删除成功\n");
        } else {
            printf("c文件删除失败\n");
        }
    } else {
        printf("c文件不存在\n");
    }
    
  write_to_file("../median_value/c.txt",buf_c,256);
  
  
  poly_ntt(&cp);//对c进行NTT

  /* Compute z, reject if it reveals secret */
  polyvecl_pointwise_poly_montgomery(&z, &cp, &s1);//这步运算是要在NTT域下进行的
  polyvecl_invntt_tomont(&z);//cs回归正常域
  polyvecl_add(&z, &z, &y);//正常域的加法
  polyvecl_reduce(&z);//约简
  
  //输出z到文件
  //===============================================================
  int32_t buf_z[L][256];
  
  for(int i=0; i < L;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_z[i][j] = z.vec[i].coeffs[j];
  }
  if (access("../median_value/z.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/z.txt") == 0) {
            printf("z文件删除成功\n");
        } else {
            printf("z文件删除失败\n");
        }
    } else {
        printf("z文件不存在\n");
    }
  for(int i=0; i < L ;i++)
  	write_to_file("../median_value/z.txt",buf_z[i],256);
  	
  
  for(int i=0; i < L;i++)
  	for(int j=0; j < 256 ;j++)
  		z1.vec[i].coeffs[j] = z.vec[i].coeffs[j];
  	
  //========================================================
  if(polyvecl_chknorm(&z, GAMMA1 - BETA))
   ;
  

  // /* Check that subtracting cs2 does not change high bits of w and low bits
  //  * do not reveal secret information */
  // polyveck_pointwise_poly_montgomery(&h, &cp, &s2);//now，h=cs2
  // polyveck_invntt_tomont(&h);
  // polyveck_sub(&w0, &w0, &h);//w0=w-cs2
  // polyveck_reduce(&w0);
  // if(polyveck_chknorm(&w0, GAMMA2 - BETA))
  //   goto rej;

  /* Compute hints for w1 */
  polyveck_pointwise_poly_montgomery(&h, &cp, &t0);//now,h=ct0
  polyveck_invntt_tomont(&h);
  polyveck_reduce(&h);
  // if(polyveck_chknorm(&h, GAMMA2))
  //   goto rej;

  polyveck_add(&w0, &w0, &h);//w0=w-cs2+ct0
  polyveck_caddq(&w0);
  //n = polyveck_make_hint(&h, &w0, &w1);//利用w1和w0之间的差距h，并返回h中1的个数
  
  //gaidong1====================================================
 
  		
  polyvecl_ntt(&z);
  polyvec_matrix_pointwise_montgomery(&tmp, mat, &z);
  //poly_ntt(&cp);
  //int32_t buf_z[L][256];
  
  
  polyvecl_invntt_tomont(&z);
  polyvecl_reduce(&z);
  
  //int32_t buf_z[L][256];
  
  
  polyveck_shiftl(&t1);
  polyveck_ntt(&t1);
  polyveck_pointwise_poly_montgomery(&t1, &cp, &t1);
  
  polyveck_sub(&tmp, &tmp, &t1);
  polyveck_reduce(&tmp);
  polyveck_invntt_tomont(&tmp);
  
  /* Reconstruct w1 */
  polyveck_caddq(&tmp);
   for(int i=0; i < K;i++)
  	for(int j=0; j < 256 ;j++)
  		h.vec[i].coeffs[j] = 0;
  polyveck_use_hint(&tmp, &tmp, &h);//az-ct=tmp
  
  //输出tmp到文件中
  int32_t buf_tmp[K][256];
  for(int i=0; i < K;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_tmp[i][j] = tmp.vec[i].coeffs[j];
  }
  if (access("../median_value/t.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/t.txt") == 0) {
            printf("t文件删除成功\n");
        } else {
            printf("t文件删除失败\n");
        }
    } else {
        printf("t文件不存在\n");
    }
  for(int i=0; i < K ;i++)
  	write_to_file("../median_value/t.txt",buf_tmp[i],256);
  
  polyveck_pack_w1(buf, &tmp);
  
  //==============================================================
  if(n > OMEGA)
    ;

  //--------------------------------------------------------
   /* Matrix-vector multiplication; compute Az - c2^dt1 */
  // poly_challenge(&cp, c);
  // polyvec_matrix_expand(mat, rho);

  

  
//----------------------------------------------------------

  /* Write signature */
  n=0;
  for(int i=0; i < K;i++)
  	for(int j=0; j < 256;j++){
  	if (tmp.vec[i].coeffs[j] != w1.vec[i].coeffs[j] )
    			h.vec[i].coeffs[j] = 1;
    	else
    			h.vec[i].coeffs[j] = 0;
    	n = n + h.vec[i].coeffs[j];
  	}
  
  
  
  int32_t buf_h[K][256];
  for(int i=0; i < K;i++){
  	for(int j=0; j < 256 ;j++)
  	   buf_h[i][j] = h.vec[i].coeffs[j];
  }
  if (access("../median_value/h.txt", F_OK) != -1) {
        // 文件存在，删除文件
        if (remove("../median_value/h.txt") == 0) {
            printf("h文件删除成功\n");
        } else {
            printf("h文件删除失败\n");
        }
    } else {
        printf("h文件不存在\n");
    }
  for(int i=0; i < K ;i++)
  	write_to_file("../median_value/h.txt",buf_h[i],256);
  
  
  
  pack_sig(sig, sig, &z1, &h);
  *siglen = CRYPTO_BYTES;
  return 0;
}

/*************************************************
* Name:        crypto_sign_signature
*
* Description: Computes signature.
*
* Arguments:   - uint8_t *sig:   pointer to output signature (of length CRYPTO_BYTES)
*              - size_t *siglen: pointer to output length of signature
*              - uint8_t *m:     pointer to message to be signed
*              - size_t mlen:    length of message
*              - uint8_t *sk:    pointer to bit-packed secret key
*
* Returns 0 (success)
**************************************************/


/*************************************************
* Name:        crypto_sign
*
* Description: Compute signed message.
*
* Arguments:   - uint8_t *sm: pointer to output signed message (allocated
*                             array with CRYPTO_BYTES + mlen bytes),
*                             can be equal to m
*              - size_t *smlen: pointer to output length of signed
*                               message
*              - const uint8_t *m: pointer to message to be signed
*              - size_t mlen: length of message
*              - const uint8_t *sk: pointer to bit-packed secret key
*
* Returns 0 (success)
**************************************************/
int crypto_sign(uint8_t *sm,
                size_t *smlen,
                const uint8_t *m,
                size_t mlen,
                const uint8_t *sk,const uint8_t *pk,int diedai)
{
  size_t i;

  for(i = 0; i < mlen; ++i)
    sm[CRYPTO_BYTES + mlen - 1 - i] = m[mlen - 1 - i];
  crypto_sign_signature(sm, smlen, sm + CRYPTO_BYTES, mlen, sk,pk,diedai);
  *smlen += mlen;
  return 0;
}

/*************************************************
* Name:        crypto_sign_verify
*
* Description: Verifies signature.
*
* Arguments:   - uint8_t *m: pointer to input signature
*              - size_t siglen: length of signature
*              - const uint8_t *m: pointer to message
*              - size_t mlen: length of message
*              - const uint8_t *pk: pointer to bit-packed public key
*
* Returns 0 if signature could be verified correctly and -1 otherwise
**************************************************/
int crypto_sign_verify(const uint8_t *sig,
                       size_t siglen,
                       const uint8_t *m,
                       size_t mlen,
                       const uint8_t *pk)
{
  unsigned int i;
  uint8_t buf[K*POLYW1_PACKEDBYTES];
  uint8_t rho[SEEDBYTES];
  uint8_t mu[CRHBYTES];
  uint8_t c[SEEDBYTES];
  uint8_t c2[SEEDBYTES];
  poly cp;
  polyvecl mat[K], z;
  polyveck t1, w1, h;
  keccak_state state;

  if(siglen != CRYPTO_BYTES)
    return -1;

  unpack_pk(rho, &t1, pk);
  if(unpack_sig(c, &z, &h, sig))
    return -1;
  if(polyvecl_chknorm(&z, GAMMA1 - BETA))
    return -1;

  /* Compute CRH(CRH(rho, t1), msg) */
  crh(mu, pk, CRYPTO_PUBLICKEYBYTES);
  shake256_init(&state);
  shake256_absorb(&state, mu, CRHBYTES);
  shake256_absorb(&state, m, mlen);
  shake256_finalize(&state);
  shake256_squeeze(mu, CRHBYTES, &state);

  /* Matrix-vector multiplication; compute Az - c2^dt1 */
  poly_challenge(&cp, c);
  polyvec_matrix_expand(mat, rho);

  polyvecl_ntt(&z);
  polyvec_matrix_pointwise_montgomery(&w1, mat, &z);

  poly_ntt(&cp);
  polyveck_shiftl(&t1);
  polyveck_ntt(&t1);
  polyveck_pointwise_poly_montgomery(&t1, &cp, &t1);

  polyveck_sub(&w1, &w1, &t1);
  polyveck_reduce(&w1);
  polyveck_invntt_tomont(&w1);

  /* Reconstruct w1 */
  polyveck_caddq(&w1);
  polyveck_use_hint(&w1, &w1, &h);
  polyveck_pack_w1(buf, &w1);

  /* Call random oracle and verify challenge */
  shake256_init(&state);
  shake256_absorb(&state, mu, CRHBYTES);
  shake256_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
  shake256_finalize(&state);
  shake256_squeeze(c2, SEEDBYTES, &state);
  for(i = 0; i < SEEDBYTES; ++i)
    if(c[i] != c2[i])
      return -1;

  return 0;
}

/*************************************************
* Name:        crypto_sign_open
*
* Description: Verify signed message.
*
* Arguments:   - uint8_t *m: pointer to output message (allocated
*                            array with smlen bytes), can be equal to sm
*              - size_t *mlen: pointer to output length of message
*              - const uint8_t *sm: pointer to signed message
*              - size_t smlen: length of signed message
*              - const uint8_t *pk: pointer to bit-packed public key
*
* Returns 0 if signed message could be verified correctly and -1 otherwise
**************************************************/
int crypto_sign_open(uint8_t *m,
                     size_t *mlen,
                     const uint8_t *sm,
                     size_t smlen,
                     const uint8_t *pk)
{
  size_t i;

  if(smlen < CRYPTO_BYTES)
    goto badsig;

  *mlen = smlen - CRYPTO_BYTES;
  if(crypto_sign_verify(sm, CRYPTO_BYTES, sm + CRYPTO_BYTES, *mlen, pk))
    goto badsig;
  else {
    /* All good, copy msg, return 0 */
    for(i = 0; i < *mlen; ++i)
      m[i] = sm[CRYPTO_BYTES + i];
    return 0;
  }

badsig:
  /* Signature verification failed */
  *mlen = -1;
  for(i = 0; i < smlen; ++i)
    m[i] = 0;

  return -1;
}


//
//  PQCgenKAT_sign.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rng.h"
#include "api.h"

#define	MAX_MARKER_LEN		50

#define KAT_SUCCESS          0
#define KAT_FILE_OPEN_ERROR -1
#define KAT_DATA_ERROR      -3
#define KAT_CRYPTO_FAILURE  -4

int		FindMarker(FILE *infile, const char *marker);
int		ReadHex(FILE *infile, unsigned char *A, int Length, char *str);
void	fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L);

char    AlgName[] = "My Alg Name";

int
main(int argc, char *argv[])
{
    char                fn_req[32], fn_rsp[32],fn_rsp1[32];
    FILE                *fp_req, *fp_rsp,*fp_mtxt,*fp_pk,*fp_rsp1,*fp_sk;
    unsigned char       seed[48];
    unsigned char       msg[3300];
    unsigned char       entropy_input[48];
    unsigned char       *m, *sm, *m1;
    unsigned long long  mlen, smlen, mlen1;
    int                 count;
    int                 done;
    unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
    int                 ret_val;
    int diedai = atoi(argv[1]);
    
    // Create the REQUEST file
    //=====================================================
    sprintf(fn_req, "./PQCsignKAT_%d.req", CRYPTO_SECRETKEYBYTES);
    if ( (fp_req = fopen(fn_req, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    ///////////////
    //printf("haha");
    sprintf(fn_rsp, "./PQCsignKAT_%d.rsp", CRYPTO_SECRETKEYBYTES);
    sprintf(fn_rsp1, "./PQCsignKAT_%d.rsp1", CRYPTO_SECRETKEYBYTES);
    if ( (fp_rsp = fopen(fn_rsp, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp);
        return KAT_FILE_OPEN_ERROR;
    }
    
    if ( (fp_rsp1 = fopen(fn_rsp1, "w")) == NULL ) {
        printf("Couldn't open <%s> for write\n", fn_rsp1);
        return KAT_FILE_OPEN_ERROR;
    }
    
    
    //printf("haha");
    
    //printf("dsfsdf");
    for (int i=0; i<48; i++)
        entropy_input[i] = i;
      
    
    ///////////////////////////

    randombytes_init(entropy_input, NULL, 256);
     
    for (int i=0; i<1; i++) {
        fprintf(fp_req, "count = %d\n", i);
        randombytes(seed, 48);
        fprintBstr(fp_req, "seed = ", seed, 48);
        mlen = 33*(i+1);
        fprintf(fp_req, "mlen = %llu\n", mlen);
        randombytes(msg, mlen);
        fprintBstr(fp_req, "msg = ", msg, mlen);
        fprintf(fp_req, "pk =\n");
        fprintf(fp_req, "sk =\n");
        fprintf(fp_req, "smlen =\n");
        fprintf(fp_req, "sm =\n\n");
    }
    fclose(fp_req);
    
    
    
    //printf("haha");

    //Create the RESPONSE file based on what's in the REQUEST file
    if ( (fp_req = fopen(fn_req, "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fn_req);
        return KAT_FILE_OPEN_ERROR;
    }
    
    
    if ( (fp_mtxt = fopen("../median_value/m.txt", "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fp_mtxt);
        return KAT_FILE_OPEN_ERROR;
    }
    
    if ( (fp_pk = fopen("../median_value/pk.txt", "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fp_pk);
        return KAT_FILE_OPEN_ERROR;
    }
    
    /*if ( (fp_sk = fopen("../median_value/sk.txt", "r")) == NULL ) {
        printf("Couldn't open <%s> for read\n", fp_sk);
        return KAT_FILE_OPEN_ERROR;
    }*/
    
    
    

    fprintf(fp_rsp, "# %s\n\n", CRYPTO_ALGNAME);
    
    //========================================================
    
 
    

    
    
    //Create the RESPONSE file based on what's in the REQUEST file
    
    done = 0;
    do {
        if ( FindMarker(fp_req, "count = ") )
            {fscanf(fp_req, "%d", &count);
            }
            
        else {
            done = 1;
            break;
        }
        fprintf(fp_rsp, "count = %d\n", count);
        
        if ( !ReadHex(fp_req, seed, 48, "seed = ") ) {
            printf("ERROR: unable to read 'seed' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "seed = ", seed, 48);
        
        randombytes_init(seed, NULL, 256);
        
        if ( FindMarker(fp_req, "mlen = ") )
            fscanf(fp_req, "%llu", &mlen);
        else {
            printf("ERROR: unable to read 'mlen' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintf(fp_rsp, "mlen = %llu\n", mlen);
        
        m = (unsigned char *)calloc(mlen, sizeof(unsigned char));
        m1 = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
        sm = (unsigned char *)calloc(mlen+CRYPTO_BYTES, sizeof(unsigned char));
        

        
        if ( !ReadHex(fp_mtxt, m, (int)mlen, "m = ") ) {
            printf("ERROR: unable to read 'msg' from <%s>\n", fn_req);
            return KAT_DATA_ERROR;
        }
        fprintBstr(fp_rsp, "msg = ", m, mlen);
        
        // Generate the public/private keypair
        //printf("asfsdf");
        
        if ( (ret_val = crypto_sign_keypair(pk, sk)) != 0) {
            printf("crypto_sign_keypair returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        /*for(int i=0; i < 1312;i++){
        	pk[i] = '0';
        }*/
        /*if ( !ReadHex(fp_pk, pk, CRYPTO_PUBLICKEYBYTES , "pk = ") ) {
            printf("ERROR: unable to read 'pk' from <%s>\n", fp_pk);
            return KAT_DATA_ERROR;
        }
        
        if ( !ReadHex(fp_sk, sk, CRYPTO_PUBLICKEYBYTES , "sk = ") ) {
            printf("ERROR: unable to read 'sk' from <%s>\n", fp_sk);
            return KAT_DATA_ERROR;
        }*/
        
        //读取pk文件=======================================================
        char pkstr[2625];

         if (fgets(pkstr, 2625, fp_pk) != NULL) {
        //printf("读取的字符串: %s\n", pkstr);
       }
        int cacheint1[2624];	
         for(int i=0; i < 2624;i++)
              if(pkstr[i]  - 'a'>=  0 )
                 cacheint1[i] = 10 + pkstr[i] - 'a';
              else
                 cacheint1[i] = pkstr[i] - '0';
         
        for(int i=0; i < 1312 ;i++)
            pk[i] = cacheint1[2*i] * 16 + cacheint1[2*i+1];
            
        /*for(int i=0; i < 10;i++)
            printf("%d\n",pk[i]);*/
        //=====================================================================================
        
        //读取sk文件===========================================================================
        /*
         char skstr[5089];

         if (fgets(skstr, 5089, fp_sk) != NULL) {
           printf("读取的字符串: %s\n", skstr);
       }
       
       int cacheint2[5088];	
         for(int i=0; i < 5088;i++)
              if(skstr[i]  - 'a'>=  0 )
                 cacheint2[i] = 10 + skstr[i] - 'a';
              else
                 cacheint2[i] = skstr[i] - '0';
         
        for(int i=0; i < 2544 ;i++)
            sk[i] = cacheint2[2*i] * 16 + cacheint2[2*i+1];
        
        for(int i=0; i < 10;i++)
            printf("%d\n",sk[i]);
          */
            
        //==========================================================================
            
        
        fprintBstr(fp_rsp, "pk = ", pk, CRYPTO_PUBLICKEYBYTES);
        fprintBstr(fp_rsp, "sk = ", sk, CRYPTO_SECRETKEYBYTES);
        
        /*for(int i=0; i < CRYPTO_PUBLICKEYBYTES;i++){
        	printf("%d\n",pk[i]);
        }*/
        char c[16];
   	unsigned int i=0;
	unsigned int j=0,k=0;
	    for	(i=0;i<16;i++){
		if (i<10)
		c[i] = '0' +i;
		else
		c[i] = 'A' + i-10;
		}
		
	
        	/*char pkstr[2624]="177da35b558d048f1c5097473069d316298fdc1210dd3beef44dc2c6bac918fb43d35bd02fbf0e1bf4bdd39be573b848eb2d82a92892a503ad8097e3c2433ab4df118adbc2c7697624078da36444ffc3bb3d3425f53d4c8c973bf25fea11d047f55ba08485c36d328fca49eab8606427473fc0d63bf1e05ff5609430a6c78de763c151ead2a969d72afe6a82ca8909b74d0cfca2f2d4e4076069fc213a58da6c1d242668da6e3b3029018a606163303c9e4898ef7948ef0d2184eee711380a897abebe7f216fb3863f719172277fee45616e0784fe2bab4bbff7847afc58e00fd7aa90315cf1a869ff580da6a10cd32421be0f11636b25b5aaf18ca5ddaaf9da30e8b37b4abc97772e99d2cebef2a04f513889316585986dc2f3d6770b5282131eb399a5a4ac930ee501c047dd6749a8c6f2907b45dd467576f70e499630007591bb0a17cef6b8dd7e7cb44b4da17bfae939546c42dcdef5db7d1c38da84e3cac1b3bd1215b5744c9c8c80de06e0eea59e36fc3ea546bac7c9a07e6456b684537b8edfac18fd7b664e5338b720bbb627ad8d27349814a87f65011d99abafcd1c277f6a239ded7cf051941a2cac5c6d9047b39f897da9077a204a4880f9de4304c51efc98ef419db8f9c7368a77f4b49b5565386789db29cecd9c22693fed6246048b1c3e11ed2840865bd8b4cff60455f1031ab6131b8c019e898d4b0d3071ddbeac6ee6b282f54805d0d8f8091f0fadb16ef7a199500fb6b67486e5f9f8174afa23f5980eda0e506a9dae2beac3e39f1a694a382238e0a92c19749c131352e1afc1089e6b4fd93ef8f7c92a5eeed1c151b2e6ceaa6043155265fe08fe31425c973c37de2060ec99e152570b63ba5a47f4945e93df978ad5a58f0cfa4178d83f123c0cc237e1dd6218e521c96f54a0becb76af90436471b2a9d7a9a422d96d3f8b48b9ea181d1c14f854f3434823b1f62058dd31b63726b1e68c362862187e0f5456f56b9ca48c48ec84f37c93e989716c122b55af33572ee20af8a0b0edaf835b316e26dd06e017dcfca34afcbf8cb118fc9cb7bb065c7b6d5430ffdba70fc495448652881a65d18c8dbae985b0247fa7db2bc6928da89e50caf3d43554771bf4fb6b37424c1798db2ba93f802503b41bc04baf1581b20ccdf94dcce8df2e2513ea77d4277af98078c425979b7f7873883ee9e7817713f10e95cf1f8fe1bd987dec768edd72a5858c375809e22e62f23f9de3231c4a8ec49a4622db128904d1d6236fd510f9664ac79a538bb94da18cc2a323dc65d6515319db9126456bae373e08983553ed0bcc6777547e7db573ba5e626bb4dbad7c98fc75863641ae286d443e6a0c675bcb103c0d9ee57f9ebe1f68fdcdeaee6cdb2d493d33e1c7317d2e8d647996bef5f3224179670c8813c71ec999df6f44100cd890f556a2c081b8237a0b0569bbef0630e63ee42cf8e1fe63e95e79fe48b26fc7483b2639e22d6fb75a142bf33d03b089db858f6932c30b2fb1bb34f718b5c499918ae2443572ef0fba9889b256c2af2a22ae2ca79454741bbb9e1718640c3366eedb97bc7a56bedcbabbe1d80661f4da361b5f8f47337c1f23d6b1f6f805efda07b239ecb479014987f3ecbc1b784a5133200f3d62cd7356765ff7afd745a8c5f5d24d71022cb6529c752f945fa3576a48f18dc6ec4bfc71b0c6d65be8b4fce6a0353d1409c61fadff14a7b0119ed78ebc52f20a439c6c8dbaa4c0c3e97f5bcda7409013de19e5fd8e1c388b73434d7f7abfffa7609f66aec9e23755dd0611d82551d1403afa6688e209e4c2f003050191c51e2fa5af9f24de0da9f1c79f00a8e5ec864b30414942";
        int cacheint1[2624];	
         for(int i=0; i < 2624;i++)
              if(pkstr[i]  - 'a'>=  0 )
                 cacheint1[i] = 10 + pkstr[i] - 'a';
              else
                 cacheint1[i] = pkstr[i] - '0';
         
        for(int i=0; i < 2544 ;i++)
            pk[i] = cacheint1[2*i] * 16 + cacheint1[2*i+1];
        printf("haha1");
        for(int i=0; i < 10;i++)
            printf("%d\n",pk[i]);*/
        
	//fprintBstr(fp_rsp1, "pk = ", pk, CRYPTO_PUBLICKEYBYTES);
	
	fclose(fp_rsp1);
	
	/*char skstr[5088]="177da35b558d048f1c5097412069d316298fdc1210dd3beef44dc2c6b35918fb85765f1874f9afb94b1e6a5ca123456c04d2f4b78ffe69b07c12ae30644077c8576f853df7b1ef04622a5755beb0853d357d574ab3c40d1ca27598eb655520f398ec6e3ebb6d7609693d3ae7dbf7a06fd88249500890c1982419392c088680e0a63148206910214e244440d142658bc26800122e091071e048658184400136521094641a87851a3182e2145212c9081a9510541630d8844c54122640428813120492b0300ca60004c76049340c9ca26911244120081212a11061868c80a22149420ddc122008b970ccb4914934851227124a482d131768d8882803c900c4404920018a0903821c2390e0882054c6519ab25024a6810a2460db22812226662248104124442292449b842123150223c66001438aa4a885a2c6641c26000836314426215304705c040911a4680b220549a00c61364ca0b890dab244d4162044488d0a165220434480966810170e1c963084306c00b90c000424a3386248484064b409428421121664dc229092246464902cc2c20d04223001134d53845080126898a48002b58d9a44810ba6689118020a086de23041a3860001c6045910124a108a03429201a7650440499a26828c128a60384ae0161193a40c1c458c518421d8b44c1ac34021334683204c0b09448b102953380224a74114c5440805691435652040258036815a22021a38104226902204714a246d1c176120318a80220ee1a04413352ddc322153166ec32082222464d1162299b0610ab22d091768638270c8c04103304e0a461019814852382264904158245211217264384a20a12d23c38559402a21c970190202d3a01080960944881193408ed4904c52827008122143086ad8164904996d1996501844300a439064265160080923c52d04464ca4c26810c03194b88d21258481380e4ba24d14956822380890128a883221e1242049426c1894301a96205146428818059c02050a212c098700193071c2a83113099052c221db106d8aa63182304a04a3411912485aa644c834705a167042824511b7291cb79010a7289b044c22b07009a28c48c24c09184de046918c962c08c00d52244a8bc28dd1802cc4c244e096688184081202221128610c220982a64889447259c42d90107260460944408da3148602497001036513a18420a3714ab605032511e24424d3184592c67048b445daa42c4a0665f16fa9f25f69c9e7c488736f36d461463a4d0236140e40863f60a013c44b03a6a7f13437194e15e7dbc21d49b1f8760d24a01ebccf6a53447689479626855173d134767f784fb522bd27b50167c6bf4bd81345e9d3c5fa1b7bbd6fc3cfc896f0a0d6da3d7125f440934c55c3465886d46a9921e46c74dddc9f7f3354e61bd680b34a1bc08a2d79a62568217fcf5c0b31301528752ce70906f5f41020438ac83241c458bd8f612dbc2b26939c6ae454a2b937646e9a906326dd9c3e16439e79bcb136180d9243f9ca3c2b3fae7c55eb60aebae14de9ae790c2824155742d1f66e567027c2a4fc9b3dfc6f2a2d7b1156f8f88140a937e024bcac6e0495c784ec42e62d8bfe3247171e11b7207d5e68edae8a65950f6b322ec6fc286a7acb6aebaa19431b117a97f082573747409e17bc88e5394a93dfacfe823ce4f09c0e907a603e6cd694c300e683d1f18069d2721efa2295b5c3c7ddb6c473a2c31fea89b925f37d9cfd0103c11b8d35d49e31d314f47008e2f3e4b6fe15ada18e8c22eb8a3a37f8eb28ea8fb2f45541534780b03bd4cdae065f2291be446b554f9d1f7447b9d127d2a7125db4c4c7760a0f930180c0110997164621ddc50ab7e55aa83b0d7b53562102404e48174147d4f783b6669e39ecea9d20b1c345234c3ee1a5c1ca3b0559ebd3a0532094098b75503b34420a1ea47e02332ff2d030a7ae5d550d73925880f45bb8b4e6dd1c6d678baa7e80f0c23c56dfe0f931676c6720ce259d20ef0b57ed53943ed76e7affa8043a20a1e4e9cbcf1967d8b27a48c791163fb5569f93706c6a495320bedd4c0119984a137325fbfb00bf8373a42465e143779e649e44ee9c2b2c29530eb4b546a2bf162d7032672076e3fa400ef4520658287cf9aca662161d6182c1cd0563dc1f4293e7861442a4386e62f64808be19e5baad12a3ac5e80290b474ce31ab00fb3bb494694d04053b579751e6cb2b433b619a4855cf823d6215405f2109fbf123e7dd8c7f60d88e382c0744b3f565bc528790aef1366a1c063610b0399f8733ce6a9447adc41d19ff8b34d40400908a9902f84d9b2b700b159cbf80b08c23f63f9d6ed4b0c7d80e1b894fcb3fd7669d6b9cd79f3fc9ba66b05f49ef1e4fc026074346de14248000a1250883dc16b5bf58135c5fa6e01bcdf7b6b5d5c284c7f8a102114c51e04b182357489348b41421049e142d41ef810d805348a98d27f22be139add9fb9d8d6c75d1145e475920005140fef31961e9878eb952bfc64b4f027c447dd30ad25d75e87a94626a4d1daac49f0085632f2260f05a90a187536035dbdb2073c29661fd28ef458b26d0c622add7142b15acfa42930fe4a33678bff9d58f9d667c3f453c1aa8b8092e4e468e278ba0fca92fb3e7663367533a8363c91ab9b9135be2723ceb4064b12a3efef09b8b21ebee52d2ad9c0fb8d4c94670f49429ec3cd0f2fb94906eae0862d40e558317cf014ff394d4b5955e4637c753529f903feb1f1166a5edde2faf7ab38fa738f5cbe1801e56b9fc28ae4186a4a55dcb299a54b44ba5b78c01c1edd733c07bf282804c9a76497902a7058c8af4308ee2cac92d672b553cb5f0a95ef2ba72069253e2388932f53d77732c00bc1f3429dd2c3dd65e05930c9ffe21fc138805fcb5d36da3fb018b45b723b35520d90ece7526b2d827940bfb0b14a824bc96705b00cef985e1627ea7e6e1cd1134c9862f9a58271942295fdcf216e613efcf5627d161755d62430cf15c156107e1af131b64605dde3d555ea2a4fbe8c1215307a71f3703de9875bccaaa925d28f91efb13c49e3bc6c280871fb8d3aa00cfd6da020d291d24a34db59176ad0e29b2c5934c3af733894025fbdeb4b3ce2fd2e6a3c951a33ec36b7316bea597216315649f55969b3eac04e1326df959a09dae07ef34c72f917f375f96138709a5b5a7db28b73cdbb66f4cb44a4eaa41ea904982b120b4410aa0d3f5d00011fbe00ab14d90815e34d5478bc79654d082b4a992d8c6d4bd96aefaad40b90279ee4770d7f88ebada768641066a9e35be25eab331855f7a2468f002863485371343d9afb55a003a82f9beb107251e6a03f05e54f29d936fcc2ea34f5e8b94f457cf969a307d91f856ebf19f3fe05f4dca449c70638783ac4080ca4700a28aac50b20b89933134157cacf36e80882c924c3db909be7fceb2ceccc7d49836d288d844121302a16cbe36db57b1cff8f0fe01da6d3fb9c35caa86ed74b546df5562962b2c9ec7bae520f4e309c014882cad83a1685a602e170d5c98538bba128095c7962599351514b581f97fe8582ec9fde796ad509a30f8cd686957d6c5e";
        int cacheint[5088];
        for(int i=0; i < 5088;i++)
              if(skstr[i]  - 'a'>=  0 )
                 cacheint[i] = 10 + skstr[i] - 'a';
              else
                 cacheint[i] = skstr[i] - '0';
         
        for(int i=0; i < 2544 ;i++)
            sk[i] = cacheint[2*i] * 16 + cacheint[2*i+1]; 
           
           */
        //////////
        
        	
        
       //for(int i=0; i < 10;i++)
            //printf("%d\n",sk[i]);
        if ( (ret_val = crypto_sign(sm, &smlen, m, mlen, sk,pk,diedai)) != 0) {
            printf("crypto_sign returned <%d>\n", ret_val);
            return KAT_CRYPTO_FAILURE;
        }
        fprintf(fp_rsp, "smlen = %llu\n", smlen);
        fprintBstr(fp_rsp, "sm = ", sm, smlen);
        fprintf(fp_rsp, "\n");
        
        //////
        //printf("haha");
        if ( (ret_val = crypto_sign_open(m1, &mlen1, sm, smlen, pk)) != 0) {
            printf("crypto_sign_open returned <%d>\n", ret_val);
            printf("验证失败1");
            return KAT_CRYPTO_FAILURE;
        }
        else{
        printf("验证成功");
        }
        
        if ( mlen != mlen1 ) {
        	 printf("验证失败2");
            printf("crypto_sign_open returned bad 'mlen': Got <%llu>, expected <%llu>\n", mlen1, mlen);
            return KAT_CRYPTO_FAILURE;
        }
        else{
        printf("验证成功");
        }
        
        if ( memcmp(m, m1, mlen) ) {
         printf("验证失败3");
            printf("crypto_sign_open returned bad 'm' value\n");
            return KAT_CRYPTO_FAILURE;
        }
        else{
        printf("验证成功");
        }
        
        free(m);
        free(m1);
        free(sm);

    } while ( !done );
    
    fclose(fp_req);
    //fclose(fp_rsp);
    fclose(fp_rsp);
    fclose(fp_mtxt);
    fclose(fp_pk);
    //fclose(fp_sk);

    return KAT_SUCCESS;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
FindMarker(FILE *infile, const char *marker)
{
	char	line[MAX_MARKER_LEN];
	int		i, len;
	int curr_line;

	len = (int)strlen(marker);
	if ( len > MAX_MARKER_LEN-1 )
		len = MAX_MARKER_LEN-1;

	for ( i=0; i<len; i++ )
	  {
	    curr_line = fgetc(infile);
	    line[i] = curr_line;
	    if (curr_line == EOF )
	      return 0;
	  }
	line[len] = '\0';

	while ( 1 ) {
		if ( !strncmp(line, marker, len) )
			return 1;

		for ( i=0; i<len-1; i++ )
			line[i] = line[i+1];
		curr_line = fgetc(infile);
		line[len-1] = curr_line;
		if (curr_line == EOF )
		    return 0;
		line[len] = '\0';
	}

	// shouldn't get here
	return 0;
}

//
// ALLOW TO READ HEXADECIMAL ENTRY (KEYS, DATA, TEXT, etc.)
//
int
ReadHex(FILE *infile, unsigned char *A, int Length, char *str)
{
	int			i, ch, started;
	unsigned char	ich;

	if ( Length == 0 ) {
		A[0] = 0x00;
		return 1;
	}
	memset(A, 0x00, Length);
	started = 0;
	if ( FindMarker(infile, str) )
		while ( (ch = fgetc(infile)) != EOF ) {
			if ( !isxdigit(ch) ) {
				if ( !started ) {
					if ( ch == '\n' )
						break;
					else
						continue;
				}
				else
					break;
			}
			started = 1;
			if ( (ch >= '0') && (ch <= '9') )
				ich = ch - '0';
			else if ( (ch >= 'A') && (ch <= 'F') )
				ich = ch - 'A' + 10;
			else if ( (ch >= 'a') && (ch <= 'f') )
				ich = ch - 'a' + 10;
            else // shouldn't ever get here
                ich = 0;
			
			for ( i=0; i<Length-1; i++ )
				A[i] = (A[i] << 4) | (A[i+1] >> 4);
			A[Length-1] = (A[Length-1] << 4) | ich;
		}
	else
		return 0;

	return 1;
}

void
fprintBstr(FILE *fp, char *S, unsigned char *A, unsigned long long L)
{
	unsigned long long  i;

	fprintf(fp, "%s", S);

	for ( i=0; i<L; i++ )
		fprintf(fp, "%02X", A[i]);

	if ( L == 0 )
		fprintf(fp, "00");

	fprintf(fp, "\n");
}


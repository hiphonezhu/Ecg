// test.cpp : 定义控制台应用程序的入口点。
//
#include "head_ecg.h"
//checked by Huo
void my_filter(double const *src,double *dst,int len)
{	
		if(src == NULL || dst == NULL || len<201){
			//puts("my_filter pointer is invalid!\n");
			//exit(0);
			return;
		}
		double sum = 0;
		int i, j;		
		
		//2-35 bandpass filter: N = 200, Wn = [2/500 35/500];b = fir1(N, Wn);a = 1;
		/*double b[] = {-0.000241564441461938,	-0.000187552437319965,	-0.000135571517632132,	-8.74954240310426e-05,
			-4.53073573541483e-05,	-1.10995042526124e-05,	1.29529692756053e-05,	2.46492261373239e-05,
			2.18540652201831e-05,	2.62227847483367e-06,	-3.46488223067190e-05,	-9.10474788443667e-05,
			-0.000166968434127325,	-0.000261941815242181,	-0.000374486783338695,	-0.000502007302693992,
			-0.000640746494229281,	-0.000785813688438205,	-0.000931294528863289,	-0.00107044946077386,
			-0.00119599993679867,	-0.00130049504105997,	-0.00137674440805166,	-0.00141829677150400,
			-0.00141993771780824,	-0.00137817571749969,	-0.00129168269521107,	-0.00116165461835263,
			-0.000992059070216335,	-0.000789740621638223,	-0.000564360973564489,	-0.000328159100663849,
			-9.55266198742450e-05,	0.000117595165968933,	0.000294478260323873,	0.000418500964247554,
			0.000474129922779651,	0.000447940964770676,	0.000329621449754494,	0.000112892713681680,
			-0.000203709539702433,	-0.000616256123367848,	-0.00111509904321078,	-0.00168484212543340,
			-0.00230463609746504,	-0.00294881023571426,	-0.00358783433899375,	-0.00418958539725361,
			-0.00472087395058340,	-0.00514916688670796,	-0.00544442742287961,	-0.00558098031544469,
			-0.00553930186767868,	-0.00530763080920006,	-0.00488329810706276,	-0.00427368147043467,
			-0.00349670365372111,	-0.00258081225727907,	-0.00156440187088860,	-0.000494666117234275,
			0.000574103800241366,	0.00158272747902829,	0.00246977472733438,	0.00317453297479995,
			0.00364017628282138,	0.00381699134637412,	0.00366550404834559,	0.00315934560070126,
			0.00228770067174118,	0.00105719135734544,	-0.000506929802254381,	-0.00236037795396040,
			-0.00444029256136438,	-0.00666658217945073,	-0.00894414614010540,	-0.0111659197569196,
			-0.0132166482599260,	-0.0149772560993776,	-0.0163296445067368,	-0.0171617230884741,
			-0.0173724622980685,	-0.0168767440683092,	-0.0156097884454740,	-0.0135309450275169,
			-0.0106266591452567,	-0.00691245331044457,	-0.00243380328096833,	0.00273416647353292,
			0.00848819307320144,	0.0146995640532189,		0.0212179051079989,		0.0278759372900728,	
			0.0344950292150537,	0.0408913318911464,	0.0468822547805144,	0.0522930230794382,	0.0569630489661191,
			0.0607518541700823,	0.0635442975685125,	0.0652548889581505,	0.0658310075028817,	0.0652548889581505,
			0.0635442975685125,	0.0607518541700823,	0.0569630489661191,	0.0522930230794382,	0.0468822547805144,
			0.0408913318911464,	0.0344950292150537,	0.0278759372900728,	0.0212179051079989,	0.0146995640532189,
			0.00848819307320144,	0.00273416647353292,	-0.00243380328096833,	-0.00691245331044457,
			-0.0106266591452567,	-0.0135309450275169,	-0.0156097884454740,	-0.0168767440683092,
			-0.0173724622980685,	-0.0171617230884741,	-0.0163296445067368,	-0.0149772560993776,
			-0.0132166482599260,	-0.0111659197569196,	-0.00894414614010540,	-0.00666658217945073,
			-0.00444029256136438,	-0.00236037795396040,	-0.000506929802254381,	0.00105719135734544,
			0.00228770067174118,	0.00315934560070126,	0.00366550404834559,	0.00381699134637412,
			0.00364017628282138,	0.00317453297479995,	0.00246977472733438,	0.00158272747902829,
			0.000574103800241366,	-0.000494666117234275,	-0.00156440187088860,	-0.00258081225727907,
			-0.00349670365372111,	-0.00427368147043467,	-0.00488329810706276,	-0.00530763080920006,
			-0.00553930186767868,	-0.00558098031544469,	-0.00544442742287961,	-0.00514916688670796,
			-0.00472087395058340,	-0.00418958539725361,	-0.00358783433899375,	-0.00294881023571426,
			-0.00230463609746504,	-0.00168484212543340,	-0.00111509904321078,	-0.000616256123367848,
			-0.000203709539702433,	0.000112892713681680,	0.000329621449754494,	0.000447940964770676,
			0.000474129922779651,	0.000418500964247554,	0.000294478260323873,	0.000117595165968933,
			-9.55266198742450e-05,	-0.000328159100663849,	-0.000564360973564489,	-0.000789740621638223,
			-0.000992059070216335,	-0.00116165461835263,	-0.00129168269521107,	-0.00137817571749969,
			-0.00141993771780824,	-0.00141829677150400,	-0.00137674440805166,	-0.00130049504105997,
			-0.00119599993679867,	-0.00107044946077386,	-0.000931294528863289,	-0.000785813688438205,
			-0.000640746494229281,	-0.000502007302693992,	-0.000374486783338695,	-0.000261941815242181,
			-0.000166968434127325,	-9.10474788443667e-05,	-3.46488223067190e-05,	2.62227847483367e-06,
			2.18540652201831e-05,	2.46492261373239e-05,	1.29529692756053e-05,	-1.10995042526124e-05,
			-4.53073573541483e-05,	-8.74954240310426e-05,	-0.000135571517632132,	-0.000187552437319965,
			-0.000241564441461938};*/
			double b[] = {-2.49939870689846e-19,	-6.42670110592360e-05,	-0.000126833377254920,	-0.000184633240486872,	
				-0.000234548351952457,	-0.000273478101958888,	-0.000298449482449997,	-0.000306771591638274,	-0.000296232329902181,
				-0.000265327256792922,	-0.000213503048842499,	-0.000141391531522019,	-5.10057262510003e-05,	5.41325107414032e-05,
				0.000168962360534509,	0.000286975791118926,	0.000400447494845365,	0.000500808386513992,	0.000579154980041613,
				0.000626872831567505,	0.000636338275127471,	0.000601650228861446,	0.000519334246342653,	0.000388955424061570,
				0.000213576192850239,	-6.70872606797806e-19,	-0.000241247426496937,	-0.000496231492031623,	-0.000748228513573709,
				-0.000978639745396982,	-0.00116816219245839,	-0.00129815383037096,	-0.00135210844881791,	-0.00131713752003599,
				-0.00118534513241762,	-0.000954978620034798,	-0.000631243044098671,	-0.000226682490712754,	0.000238945118054209,
				0.000739341434844129,	0.00124289343742443,	0.00171441436360098,	0.00211732060293436,	0.00241612557874509,
				0.00257909743649307,	0.00258090166246110,	0.00240503517007988,	0.00204585684498851,	0.00151003213651511,
				0.000817236157334425,	-1.68709412715646e-18,	-0.000897363343599875,	-0.00182075686839449,	-0.00270915963246305,
				-0.00349822186227775,	-0.00412440646697335,	-0.00452943557987484,	-0.00466476096163301,	-0.00449575392418084,
				-0.00400530655602134,	-0.00319655295127927,	-0.00209445701934297,	-0.000746070996215034,	0.000780656709746723,
				0.00239955823493203,	0.00401034611412499,	0.00550397757381676,	0.00676903169525384,	0.00769876577559599,
				0.00819845186008093,	0.00819255096590246,	0.00763126492847945,	0.00649601651903026,	0.00480344821716343,
				0.00260759762691062,	-2.70331564751511e-18,	-0.00289241905015963,	-0.00591167100560782,	-0.00887512928615579,
				-0.0115837969890017,	-0.0138320410219482,	-0.0154183117158493,	-0.0161562872764043,	-0.0158858331591251,
				-0.0144831516676451,	-0.0118695188034352,	-0.00801806344813574,	-0.00295813590315619,	0.00322306593878704,
				0.0103818004522189,	0.0183220449900812,	0.0268025817645752,	0.0355466106793485,	0.0442534459023328,	0.0526117284346342,
				0.0603134925526133,	0.0670683657654135,	0.0726171637276426,	0.0767441649053693,	0.0792874137655850,	0.0801465024594331,
				0.0792874137655850,	0.0767441649053693,	0.0726171637276426,	0.0670683657654135,	0.0603134925526133,	0.0526117284346342,
				0.0442534459023328,	0.0355466106793485,	0.0268025817645752,	0.0183220449900812,	0.0103818004522189,	0.00322306593878704,
				-0.00295813590315619,	-0.00801806344813574,	-0.0118695188034352,	-0.0144831516676451,	-0.0158858331591251,
				-0.0161562872764043,	-0.0154183117158493,	-0.0138320410219482,	-0.0115837969890017,	-0.00887512928615579,
				-0.00591167100560782,	-0.00289241905015963,	-2.70331564751511e-18,	0.00260759762691062,	0.00480344821716343,
				0.00649601651903026,	0.00763126492847945,	0.00819255096590246,	0.00819845186008093,	0.00769876577559599,
				0.00676903169525384,	0.00550397757381676,	0.00401034611412499,	0.00239955823493203,	0.000780656709746723,
				-0.000746070996215034,	-0.00209445701934297,	-0.00319655295127927,	-0.00400530655602134,	-0.00449575392418084,
				-0.00466476096163301,	-0.00452943557987484,	-0.00412440646697335,	-0.00349822186227775,	-0.00270915963246305,
				-0.00182075686839449,	-0.000897363343599875,	-1.68709412715646e-18,	0.000817236157334425,	0.00151003213651511,
				0.00204585684498851,	0.00240503517007988,	0.00258090166246110,	0.00257909743649307,	0.00241612557874509,
				0.00211732060293436,	0.00171441436360098,	0.00124289343742443,	0.000739341434844129,	0.000238945118054209,
				-0.000226682490712754,	-0.000631243044098671,	-0.000954978620034798,	-0.00118534513241762,	-0.00131713752003599,
				-0.00135210844881791,	-0.00129815383037096,	-0.00116816219245839,	-0.000978639745396982,	-0.000748228513573709,
				-0.000496231492031623,	-0.000241247426496937,	-6.70872606797806e-19,	0.000213576192850239,	0.000388955424061570,
				0.000519334246342653,	0.000601650228861446,	0.000636338275127471,	0.000626872831567505,	0.000579154980041613,
				0.000500808386513992,	0.000400447494845365,	0.000286975791118926,	0.000168962360534509,	5.41325107414032e-05,
				-5.10057262510003e-05,	-0.000141391531522019,	-0.000213503048842499,	-0.000265327256792922,	-0.000296232329902181,
				-0.000306771591638274,	-0.000298449482449997,	-0.000273478101958888,	-0.000234548351952457,	-0.000184633240486872,
				-0.000126833377254920,	-6.42670110592360e-05,	-2.49939870689846e-19}; //40Hz lowpass filter;2012.12.28
//		double *data_bp=(double *)calloc(len, sizeof(double));	
		for (i=0; i<200; i++)
			dst[i] = src[i]; 
		for (i=200; i<len; i++) {
			for(j=0; j<201; j++) {
				sum += b[j] * src[i-j];
			}
			dst[i] = sum;
			sum = 0;
		}
		
}


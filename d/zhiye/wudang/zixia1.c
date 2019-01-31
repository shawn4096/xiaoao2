// /area/jiangbei/wudang/zixia.c 紫霄宫
// By River@SJ

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIM"紫霄宫"NOR);
        set("long", @LONG
规模宏大，气势磅礴的紫霄宫，座落在武当山展旗峰下。这里群峰山岭环
绕，松林翠柏幽深，环境优雅，气候宜人，历来被视为“紫霄福地”。紫霄宫
初建于宋宣和年间。宋徽宗赵佶一次做梦，梦见了“火神”，有一方士为他圆
梦，说要派水神到南方压镇，才能无忧。于是选中了七十二福地之一的武当山，
在展旗峰下为水神玄武建造了这座宫殿，并赐额“紫霄元圣宫”。 
LONG
        );

        set("exits", ([
                "out" : __DIR__"zxgdamen",
                "southup" : __DIR__"nanyan",
        ]));

        set("no_clean_up", 0);

        set("objects",([
                CLASS_D("wudang")+ "/wanqing" : 1,
                __DIR__"npc/daotong" :2,
        ]));

       // set("outdoors", "武当");

        setup();
}
/*
void init()
{
	object me=this_player();
	if (me->query_temp("mwd/step6"))
	{
		me->start_busy(3);
		call_out("do_find",2+random(3),me);
	}

}
int do_find(object me)
{
		object kongxiang;
		message_vision(HIG"\n\n$N心中焦虑，快步如飞，但看四周的小道士们似乎都在各自忙碌，似乎那种灾难还没有发生，心中不由大定。\n\n"
							+"正在$N行走间，忽然看到前方一位少林僧人正在匆匆奔走，神色似乎甚是慌张。\n"NOR,me);
	    me->delete_temp("mwd/step6");
		
		kongxiang=new("d/wudang/taiji/kongxiang");
		kongxiang->move(this_object());
		kongxiang->greeting();
		
		me->set_temp("mwd/step7",1);
		call_out("find_yudaiyan",3,me,kongxiang);
		return 1;
}
int find_yudaiyan(object me,object kongxiang)
{
	message_vision(HIC"\n\n$N心中疑惑，心想这一路走来，看来是少林来此通报张真人的人员，不过这空相看起来好像甚是慌张的样子。\n\n"
							+"不多久，俞岱岩在小道童的搀扶下，缓缓走来，和空相谈了会，神色甚是紧张，吩咐小道童道，抬我去见祖师爷。\n"NOR,me);
	call_out("zhang_come",3,me,kongxiang);	
	return 1;
}
int zhang_come(object me,object kongxiang)
{

	object zsf;
	object room;
		room=load_object("d/wudang/houyuan");
	message_vision(HIC"\n\n半盏茶光景，一位须眉皆白的老道人缓步走来，正是名震武林的开山祖师张三丰！。\n\n"NOR,me);
	if (objectp(zsf=present("zhang sanfeng",room)))
	{
		zsf->move(this_object());
	}else {

		zsf=new("kungfu/class/wudang/zhang");
		zsf->move(this_object());
		//zsf->command("chat ....");

	}

	call_out("kx_kill",2,me,kongxiang,zsf);

}

int kx_kill(object me,object kongxiang,object zsf)
{
	
	message_vision(HIC"\n\n空相一见张三丰来到，扑通一声跪倒，嚎啕大哭。\n\n"NOR,me);
	kongxiang->greet2();
	message_vision(HIY"\n\n张三丰眼见空相如此难过，也长长叹了一口气道，“你先起来，我们再商议商议。”说罢就想将空相搀扶起来。\n"NOR,me);
	message_vision(HIY"\n\n那知此时，风云突变，空相忽然变得面目狰狞，一掌拍向张三丰的小腹！！”\n"NOR,me);
	kongxiang->kill_ob(zsf);
	zsf->kill_ob(kongxiang);
	zsf->receive_wound("qi",2000+random(1000),kongxiang);
	zsf->apply_condition("neishang",10);
	me->delete_temp("mwd/step7");
	me->set_temp("mwd/step8",1);
	add_action("do_heal","heal");
	return 1;
}*/
/*
int do_heal(string arg)
{
	object me=this_player();
	object zsf;
	zsf=present("zhang sanfeng",this_object());
	if (!zsf) return 0;
	if (!arg||arg!="zhang sanfeng")
	{
		return notify_fail("你要为谁疗伤？");
	}
	message_vision(HIC"\n\n$N纵身而起，将手搭在$n的背后，运功为$n疗伤。\n"NOR,me,zsf);
	message_vision(HIY"\n\n\n在$N的全力运转之下，$n伤势大为好转，但随即又吐了一口鲜血，$n深知方才这一掌着实受伤不轻。\n"NOR,me,zsf);
	message_vision(HIR"\n\n$n抬头看了一眼$N，轻笑道，没想到我武当派居然还有如此高手，你是谁的门下？\n"NOR,me,zsf);
	message_vision(HIG"\n\n$n说道，你这一身功夫甚是了得，看来我武当要大兴了，哈哈哈哈！？\n"NOR,me,zsf);
	
	message_vision(HIC"\n\n俞岱岩默然不答，心知山上除了师父和自己之外，其余三四代弟子的武功都不足道，出面御敌，\n"
						+"只有徒然送死，今日之事，惟有自己舍却一命，和敌人敷衍周旋，让师父避地养伤，日后再复大仇，\n"
						+"于是朗声道：“灵虚，你去跟那些人说，我便出来相见，让他们在三清殿等着。”灵虚答应着去了。"NOR,me);
　　
	message_vision(YEL"\n\n张三丰和俞岱岩师徒相处日久，心意相通，听他这么说，已知其意，说道：“岱岩，生死胜负，无足介怀，\n"
						+"武当派的绝学却不可因此中断。我坐关十八月，得悟武学精要，一套太极拳和太极剑，此刻便传了你罢。\n"
						+"俞岱岩一呆，心想自己残废已久，那还能学什么拳法剑术？何况此时强敌已经入观，怎有余暇传习武功\n"
						+"只叫了声：“师父！”便说不下去了。\n"NOR,me);
	
	message_vision(WHT"\n\n张三丰淡淡一笑，说道：“我武当开派以来，行侠江湖，多行仁义之事，以大数而言，决不该自此而绝。\n"
						+"我这套太极拳和太极剑，跟自来武学之道全然不同，讲究以静制动、后发制人。你师父年过百龄纵使不遇强敌，。\n"
						+"又能有几年好活？所喜者能于垂暮之年，创制这套武功出来。远桥、莲舟、松溪、梨亭、声谷都不在身边，\n"
						+"第三四代弟子之中。除青书外并无杰出人材，何况他也不在山上。岱岩你身负传我生平绝艺的重任。武当派\n"
						+"一日的荣辱，有何足道？只须这套太极拳能传至后代，我武当派大名必能垂之千古。”说到这里，神采飞扬，\n"
						+"豪气弥增，竟似浑没将压境的强敌放在心上。俞岱岩唯唯答应，已明白师父要自己忍辱负重，以接传本派绝技为第一要义。\n"NOR,me);
	
	message_vision(CYN"\n\n张三丰缓缓站起身来，双手下垂，手背向外，手指微舒，两足分开平行，接着两臂慢慢提起至胸前，左臂半环\n"
						+"掌与面对成阴掌，右掌翻过成阳掌，说道：“这是太极拳的起手式。”跟着一招一式的演了下去,又口中叫着招式的\n"
						+"名称：揽雀尾、单鞭、提手上式、白鹤亮翅，搂膝拗步、进步搬拦锤、如封似闭、十字手、抱虎归山\n"
						+"$N初时还道太师父故意将姿势演得特别缓慢，使俞岱岩可以看得清楚，但看到第七招‘手挥琵琶’之时，只见他左掌阳、右掌阴\n"
						+"目光凝视左手手臂，双掌，慢慢合拢，竟是凝重如山，却又轻灵似羽。张无忌陡然之间省悟：“这是以慢打快、以静制动的上乘武学\n"
						+"想不到世间竟会有如此高明的功夫。$N武功本就极高，一经领会，越看越入神，但见张三丰双手圆转，每一招都含着太极式的阴阳变化，\n"
						+"精微奥妙，实是开辟了武学中从所未有的新天地。。\n"NOR,me);
	
	message_vision(HIW"\n\n张三丰道：“这拳劲首要在似松非松，将展未展，劲断意不断……”正要往下解说，只听得前面三清殿上远远传来\n"
						+"一个苍老悠长的声音：“张三丰老道既然缩头不出，咱们把他徒子徒孙先行宰了。”另一个粗豪的声音道：“好啊！\n"
						+"先一把火烧了这道观再说。”又有一个尖锐的声音道：“烧死老道，那是便宜了他。咱们擒住了他，\n"
						+"绑到各处门派中游行示众，让大家瞧瞧这武学泰斗老而不死的模样。”\n"NOR,me);
	
	call_out("zhao_come",2+random(3),me,zsf);
	return 1;
}*/
/*
int zhao_come(object me,object zsf)
{
	object zhao,he,lu,laoda,laoer,laosan;
	if (!objectp(zhao=present("zhao min",this_object())))
	{
		zhao=new("d/city/kedian/zhao");
		zhao->move(this_object());
	}
	if (!objectp(he=present("he biweng",this_object())))
	{
		he=new("d/city/kedian/hebw");
		he->move(this_object());
	}
	if (!objectp(lu=present("lu zhangke",this_object())))
	{
		lu=new("d/city/kedian/luzk");
		lu->move(this_object());
	}
	//阿大，阿二，阿三
	if (!objectp(laosan=present("a san",this_object())))
	{
		laosan=new("d/wudang/taiji/asan");
		laosan->move(this_object());
	}
	if (!objectp(laoer=present("a er",this_object())))
	{
		laoer=new("d/wudang/taiji/aer");
		laoer->move(this_object());
	}
	if (!objectp(laoer=present("a da",this_object())))
	{
		laoda=new("d/wudang/taiji/ada");
		laoda->move(this_object());
	}
	zhao->greet_zhang();
	laosan->greet_zhang();
	
	message_vision(HIG"\n\n阿三见张三丰居然飘然下场，心下倒生了三分怯意，但转念又想：“今日我便和这老道拼个两败俱伤，\n"
						+"那也是耸动武林的盛举了。”当下屏息凝神，双目盯住在张三丰脸上，内息暗暗转动，周身骨骼劈劈拍拍，！\n"
						+"不绝发出轻微的爆响之声。众人又均相顾一愕，知道这是佛门正宗的最上武功，自外而内，不带半分邪气，乃\n"
						+"是金刚伏魔神通。张三丰见到他这等神情，也是悚然一惊：“此人来历不小啊！不知我这太极拳是否对付得了？”\n"NOR,me);
	message_vision(HIC"\n\n张三丰年近百岁，又受刚相偷袭受伤，不知道能否抵抗的住这位高手？"+HIR"你是否愿意代替张三丰出战（douquan）？\n"NOR,me);

	add_action("do_bishi1","douquan");
	return 1;

}*/
//第一场战斗金刚伏魔神通，大力金刚指，太极拳
/*
int do_bishi1()
{
	object me=this_player();
	object asan;
	asan=present("a san",this_object());
	if (!asan)
	{
		asan=new("d/wudang/taiji/asan");
		asan->move(this_object());
	}
	message_vision(HIY"$N诚心要在$n面前显示武当派的威风，运功朗声说道，请祖师歇息片刻，这等小毛贼，徒儿打法他就是了。\n"
						+"也好让他见识见识我武当派的武功，省的他坐井观天，不知中原豪杰。\n"NOR,me,asan);
    message_vision(HIY"张三丰见你出场，知道你内功了得，于是微微笑道道。“也好，既然这位金刚伏魔神功的英雄想见识见识”\n"
						+"我武当的神技，那就把我这新近参悟的太极拳的奥秘说与你听听，看你是否能融会贯通。\n"NOR,me,asan);
	asan->kill_ob(me);
	me->kill_ob(asan);

//	check_fight1(me,asan);

}

*/

//第二场战斗，内功比拼，太极神功

//第三场战斗，斗剑
#include <ansi.h>
inherit ROOM;

int do_tiao(string arg);
int do_look(string arg);
int yjj_s1(object me);
int yjj_s2(object me);
int yjj_s3(object me);
int yjj_s4(object me);
int yjj_s5(object me);
int yjj_s6(object me);

void create()
{
    set("short", "佛像之上");
       set("long", @LONG
一尊巨大的佛像头上，借助佛像可以遮挡身形，对下面的情况看的
异常清楚，佛像上落满了尘土，似乎并没有人打扫过。
LONG
       );
       
       set("no_fight",1);
       set("indoors","少林");
           /*  set("objects", ([
                "/d/shaolin/npc/yuan-gen.c" : 1,
       ]));*/

       set("coor/x",30);
       set("coor/y",200);
       set("coor/z",110);
       setup();

}

void init()
{
        add_action("do_tiao", "tiao");
        add_action("do_tiao", "jump");
		add_action("do_look", "kan");
	
}
int do_tiao(string arg)
{   
        object me;
        //int costj, costq,times;
        me = this_player();
        if (me->is_busy())
         {
			write("你现在正忙着呢!\n");
			return 1;
		}
        if (me->is_fighting())
         {
			write("你正在战斗中,无法专心干活!\n");
			return 1;
			}
        if ( !arg || arg != "down" )
          {    message_vision("$N要往哪里跳？\n",me);
                 return 1;
             }
      
        message_vision("$N轻轻一跳，飘然落地。\n", me);
        me->move("/d/shaolin/cjlou1.c"); 
     
          return 1;

}

int do_look(string arg)
{
      object me;
	  me=this_player();
	  
	  if (!arg || arg != "down")
	     return notify_fail("你要往哪儿看？");
      if (!me->query_temp("yjj/consider"))
         return notify_fail("你要干啥？");
	  me->delete_temp("yjj/cosider");
	  me->set_temp("yjj/lookdown",1);
	  message_vision(CYN"\n\n\n$N从佛像后窥看，见进来的六人都是中年僧人，心想：“我此刻窜向后殿，这六僧如均武功平平，那便不致发见，\n"
	                   +"但只要其中有一人内功深湛，耳目聪明，就能知觉。且静候片刻再说。”忽听得右首一僧道：“师兄，这菩提院中空荡荡地，\n"
					   +"有什么经书？师父为什么叫咱们来看守？说什么防敌人偷盗？”左首一僧微微一笑，道：“这是菩提院的密秘，多说无益。”\n"
					   +"右首的僧人道：“哼，我瞧你也未必知道。”左首的僧人受激不过，说道：“我怎不知道？‘一梦如是’……”他说了这半句话，\n"
					   +"蓦地惊觉，突然住口。右首的僧人问道：“什么叫做‘一梦如是’？”坐在第二个蒲团上的僧人道：“止清师弟，你平时从来\n"
					   +"不多嘴多舌，怎地今天问个不休？你要知道菩提院的密秘，去问你自己师父吧。”\n"NOR,me);
    
    call_out("yjj_s1",3,me);

	return 1;
}
int yjj_s1(object me)
{             	 
	message_vision(HIG"\n\n\n\n待了片刻，那名叫止清的僧人便不再问，过了一会，道：“我到后面方便去。”说着站起身来。他自右首走向左边侧门，\n"
	                    +"经过自左数来第五名僧人的背后时，忽然右脚一起，便踢中了那僧后心“悬枢穴”。悬枢穴在人身第十三脊椎之下，\n"
						+"那僧在蒲团上盘膝而坐，悬枢穴正在蒲团边缘，被止清足尖踢中，身子缓缓向右倒去。这止清出足极快，却又悄无声音，\n"
						+"跟着便去踢那第四僧的“悬枢穴”，接着又踢第三僧，霎时之间，接连踢倒三僧。\n"NOR,me);
    call_out("yjj_s2",5,me);
	return 1;

}

int yjj_s2(object me)
{
	message_vision(HIY"\n\n\n$N在佛像之后看得明白，心下大奇，不知这些少林僧何以忽起内哄。只见那止清伸足又踢左首第二僧，足尖刚碰上他穴道，\n"
	                    +"那被他踢中穴道的三僧之中，有两僧从蒲团上跌了下来，脑袋撞到殿上砖地，砰砰有声。左首那僧吃了一惊，跃起身来察看，\n"
						+"瞥眼见到止清出足将他身后的僧人踢倒，更是惊骇，叫道：“止清，你干什么？”止清指着外面道：“你瞧，是谁来了？\n"
						+"那僧人掉头向外看去，止清飞起右脚，往他后心疾踢。那僧人情知不敌，大声呼叫：“有奸细。有奸细……”止清跨步上前，\n"
						+"左拳击中他的胸口，那僧人登时晕倒。\n"NOR,me);
	call_out("yjj_s3",4,me);
	return 1;

}
int yjj_s3(object me)
{
	message_vision(CYN"\n\n\n止清奔到铜镜之前，伸出右手食指，在镜上那首经偈第一行第一个“一”字上一掀。乔峰从镜中见他跟着又在\n"
	                    +"第二行的“梦”这耻掀了一下，心想：“那僧人说秘密是‘一梦如是’，镜上共有四个‘如’字，不知该掀那一个？\n"
						+"但见止清伸指在第三行的第一个‘如’字上一掀，又在第四行的‘是’字上一掀。他手指未离镜面，只听得轧轧声响，铜镜已缓缓翻起。\n"NOR,me);
	call_out("yjj_s4",5,me);
	return 1;

}
int yjj_s4(object me)
{
	message_vision(RED"\n\n\n这时进来三僧，玄慈双手合什，说道：“菩提院中所藏经书，乃本寺前辈高僧所著阐扬佛法、渡化世人的大乘经论，倘若佛门弟子得了去，\n"
	                    +"念诵钻研，自然颇有神益。但如世俗之人得去，不加尊重，实是罪过不小。各位师弟师侄，自行回归本院安息，有职司者照常奉行。\n"
						+"群僧遵嘱散去，只止湛、止渊等，还是对着止清唠叨不休。玄寂向他们瞪了一眼，止湛等吃了一惊，不敢再说什么，和止清并肩而出。\n"NOR,me);
	call_out("yjj_s5",5,me);
	return 1;

}
int yjj_s5(object me)
{
	message_vision(HIW"\n\n\n\n待得群僧退去，殿上只留下玄慈、玄难、玄寂三僧，坐在佛像前蒲团之上。玄慈突然说道：阿弥陀佛，罪过罪过！这八字一出口\n"
	                    +"三僧忽地飞身而起，转到了佛像身后，从三个不同方位齐向$N所在的佛像位置出掌拍来。\n"	NOR,me);
	call_out("yjj_s6",2,me);
	return 1;

}
int yjj_s6(object me)
{
	message_vision(HIY"\n\n\n$N心想自己乃是蒙面而来，这几位师伯师叔并不知道自己的情况，为今之计，唯有先打败他们在说，\n"
	                    +"否则的确很难说的清。想到这，再也顾不得藏身，奋身而起，从佛像上跳了下来，迎了上去。\n"	NOR,me);
	me->move("/d/shaolin/cjlou1");
	return 1;

}


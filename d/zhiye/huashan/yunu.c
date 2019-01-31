// Room: /d/huashan/yunu.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
int yue_say(object me,object feng,object cheng,object cong,object yue,object ning);
void create()
{
	set("short", "玉女峰");
	set("long", @LONG
这里是华山的中峰，玉女峰。玉女峰地势略为平缓，不似其它四峰那般险
峻，江湖上赫赫有名的华山剑派就在此处。西边有所小小的庙宇，那就是玉女
祠了。南面稀稀落落有十几间房子，那里是华山派的地方，闲杂游客最好别往
那去。
LONG
	);
	set("exits", ([
		"northdown" : __DIR__"zhenyue",
		"northwest" : __DIR__"xiaolu1",
		"east" : __DIR__"yunuci",
		"south" : __DIR__"shanlu1",
		"west" : __DIR__"pubu",
	]));
	set("objects", ([
		NPC_D("youke") : 1,
		NPC_D("caiyaoren") : 1,
	]));
	set("outdoors", "华山" );
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir=="south" ){
        if(me->query("can_ride")) {  return 0;  }

	    if(me->query_temp("ride_horse"))
		return notify_fail("这位" + RANK_D->query_respect(me) + "还是请先下马，再进去吧！\n");
        }
        return ::valid_leave(me, dir);
}

void init()
{
        object me,feng,cheng;
		object cong,yue,ning;
               
        me = this_player();
      
	 
       if (me->query_temp("jianzong/asklu")){
		     tell_object(environment(me),HIC"封不平道：‘岳不群，当年你师父行使阴谋诡计，霸占了华山一派，这笔旧帐，今日可得算算。\n"
		                 +"我也不要叫你“岳师兄”，哼哼，算帐之后，你便跪在地下哀求我再叫一声，也难求得动我呢。\n"NOR);
              message_vision(HIY"突然间人影一闪，厅堂中飘出一个人来，银光闪烁，铮铮有声，已和鲁连荣斗在一起，正是岳夫人宁中则。\n"
		                 +"她出厅，拔剑，挡架，还击，一气呵成，姿式又复美妙之极，虽是极快，旁人瞧在眼中却不见其快，但见其美。\n"NOR,me);
		  if (!present("feng buping",environment(me)))
          {
			feng=new("/d/huashan/npc/sword/fengbuping.c");
			feng->move("/d/huashan/yunu");
			
          }else feng=present("feng buping",environment(me));
		 if (!present("chong buqi",environment(me)))
          {
			cong=new("/d/huashan/npc/sword/chongbuqi.c");
			cong->move("/d/huashan/yunu");
			cong->set_temp("jiali",60);
         }else cong=present("chong buqi",environment(me));
        if (!present("cheng buyu",environment(me)))
         {
			cheng=new("/d/huashan/npc/sword/chengbuyu.c");
			cheng->move("/d/huashan/yunu");
         }else cheng=present("cheng buyu",environment(me));
		if (!present("yue buqun",environment(me)))
         {
			yue=new("/d/huashan/npc/yuebuqun.c");
			yue->move("/d/huashan/yunu");
			//yue->add_temp("apply/attack",-100);
			//yue->add_temp("apply/damage",-70);
         }else yue=present("yue buqun",environment(me));
		 if (!present("ning zhongze",environment(me)))
         {
			ning=new("/d/huashan/npc/ningzhongze.c");
			ning->move("/d/huashan/yunu");
			ning->set("jiali",50);
         }else ning=present("ning zhongze",environment(me));
		 
		 cong->fight_ob(ning);
		 ning->fight_ob(cong);
		 yue->fight_ob(cheng);
		 cheng->fight_ob(yue);
		 
		//yue->command("say haha");
		call_out("yue_say", 7, me,feng,cheng,cong,yue,ning);
		return;
	} 
}

int yue_say(object me,object feng,object cheng,object cong,object yue,object ning)
{  
	
	message_vision(HIY"\n\n\n岳不群道：“大家是自己人，有话不妨慢慢的说，何必动手？”缓步走过来，顺手从劳德诺腰边抽出长剑\n"
		                            +"一递一翻，将丛不弃和岳夫人两柄长剑压住。丛不弃运劲于臂，向上力抬，不料竟然纹丝不动，脸上一红\n"
									+"又再运气。岳不群笑道：“我五岳剑派同气连枝，便如自家人一般，从师兄不必和他们一般见识。”\n"
									NOR,me);
	message_vision(HIR"\n\n\n$N眼见对方人多，方才一战虽然被师傅岳不群强行压制下来，但封不平并没有动手，尚不知道\n"+
		               "这批来人的真正实力，并且旁边的嵩山、衡山等派的来人也在束手旁观，不知道他们的真正意图。\n"NOR,me);
    if (objectp(feng)) destruct(feng);
	if (objectp(cheng)) destruct(cheng);
	if (objectp(cong)) destruct(cong);
	if (objectp(yue))  destruct(yue);
	if (objectp(ning)) destruct(ning);
	call_out("leave_all",5,me);
	return 1;

}
int leave_all(object me)
{
	
	tell_object(environment(me),CYN"\n\n你眼见众人陆续走散，想起岳不群所提及的恐怖事情，心中极为忐忑。\n"
	                               +"剑宗的剑法确实犀利，从不弃与师娘一战，已经看出端倪，这剑宗的剑术精妙异常。\n"
								   +"自己是师从气宗还是剑宗这将一件极为艰难的选择。\n"NOR);
    me->delete_temp("jianzong/asklu");
	me->set_temp("jianzong/bijian",1);
	return 1;


}
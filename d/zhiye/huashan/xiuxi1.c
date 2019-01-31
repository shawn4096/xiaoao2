// Room: /d/huashan/xiuxi1.c
// Date: Look 99/03/25
#include <ansi.h>
inherit ROOM;
//inherit NPC;
int do_liaoyang();
int do_kaoyan(string arg);
void create()
{
        set("short", "女休息室");
        set("long", @LONG
这是间整洁的厢房，因门窗常闭着，光线很昏暗。房里别无他物，只有中
间放着一张收拾得舒舒服服的大床，看着就让人想睡觉。
LONG
        );

        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits",([
        	"north" : __DIR__"celang3",
	]));

        set("indoors", "华山" );
        set("coor/x",70);
        set("coor/y",-40);
        set("coor/z",80);
		//add_action("do_liaoyuan", "liaoyang");
        setup();
}
void init()
{
	add_action("do_liaoyang", "liaoyang");
}

int do_liaoyang()
{
	
        object me = this_player();
        //if (me->query("eff_jing")= me->query("max_jing")|| me->query("eff_qi")= me->query("max_qi"))
       // 		return notify_fail("你又在偷懒？还不赶紧去练功！\n");
        if (me->is_busy())
                return notify_fail("你正忙着呢，无法静下心来养伤。\n");
        if (me->is_fighting())
                return notify_fail("你正在战斗中，如何静下心来养伤？\n");
        if (me->query("quest/huashan/zixia3")&& random(10)<= 6)
        {
			write(HIC"\n你正在安心疗养过程中,忽然岳灵珊兴冲冲地跑了进来，神神秘秘地塞给你一本书，嫣然一笑，对你说道，‘好好养病’。\n"NOR);
			write(HIY"\n你拿起来一看居然是本门至高武学秘籍【紫霞功】，顿时明白小师妹的一番心意，不禁心中百感交集！\n"NOR);
			write(HIR"\n你翻开第一页，只见上面写道，\n"NOR
			+MAG"\n天下武功，以练气为正。浩然正气，原为天授，惟常人不善养之，反以性伐气。武夫之患，\n"
			+"在性暴、性骄、性酷、性贼。暴则神扰而气乱，骄则真离而气浮，酷则丧仁而气失，贼则心狠而气促。\n"
			+"此四事者，皆是截气之刀锯……舍尔四性，返诸柔善，制汝暴酷，养汝正气，\n"
			+"鸣天鼓，饮玉浆，荡华池，叩金梁，据而行之，当有小成。\n"NOR);
			message_vision(HIY"\n人生难负美人恩，你手拿华山第一秘籍【紫霞秘籍】，思前想后，面临人生重大考验。"NOR
				+HIR"（学）"NOR+HIY"还是"NOR+HIR"（不学）？\n"NOR,me);
			add_action("do_kaoyan","answer");
			add_action("do_kaoyan","huida");
			//call_out("aoqi",5,me);
			return 1;
			
		 }
		write(HIY"你半躺在床上，正在安心养伤, 神情萧然。\n"NOR);
		me->start_busy(1);
        return 1;
}

int do_kaoyan(string arg)
{
   object me=this_player();
   if (arg == "学")
   {
    message_vision(HIC"\n就在你聚精会神准备研读这华山第一秘籍的时候，忽然一道蒙面人影闪过，一掌拍向你的胸膛!\n"NOR
	+HIR"\n你哇地吐出一口鲜血，顿时昏迷倒地。那人抢过你手中的秘籍扬长而去。\n"NOR,me);
	me->unconcious();
	me->delete_temp("quest/huashan/zixia3");
	//write("");
	return 1;
   }
   if (arg=="不学")
   {
   	
     write(HIC"\n你决定不学！既然师傅没有让我学，我即便偷学必将为人所不齿。大丈夫顶天立地，何故受人怜悯？\n"NOR);
     write(HIR"\n你心中傲气发作，将那武林中人梦寐以求的[紫霞秘籍]随手一扔，傲气发作，蹒跚着步走出屋外。\n"NOR);
	 me->move(__DIR__"zhengqi");
	 me->delete_temp("quest/huashan/zixia3");
	 me->set_temp("quest/huashan/zixia4",1);
	return 1;
   }
   write("\n你要回答什么？\n");
   return 1;
}

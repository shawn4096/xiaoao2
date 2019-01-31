// mhs		迷魂散
// 转为谢烟客准备 嘿嘿
//by kingso 2010 08 侠客行系列

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM"迷魂散"NOR, ({ "mihun san","san" }) );
        set("long",HIM"这是一包迷魂散，其药效强劲，无味让人防不胜防。只需要撒(sa)一点点就能让人昏睡一整天。\n"NOR);
        set("unit", "包");
        set("weight", 90);
        set("no_sell",1);
        set("no_give",1);
        set("no_get",1);
        set("value", 0);
}

void init()
{
	add_action("do_sa","sa");
}

int do_sa(string arg)
{
	object me=this_player() , ob , bb;

	if (!arg) return notify_fail("你要撒谁？\n");

	ob = present(arg, environment(me));
	if (!ob || !living(ob)) return notify_fail("你要撒谁？\n");

	if (!wizardp(me) && ob->query("gender")!="男性" )
		return notify_fail("有没有搞错呀，这么珍贵的东西要用到关键的地方！\n");
	
	if ((userp(ob) || ob->query("id")!="xie yanke"))
		return notify_fail("你不能随便使用这个！\n");
	
	if (ob->query("id")=="xie yanke")
		ob->kill_ob(me);
             // ob->unconcious();
              me->add("侠客行/jiejiu3", 1);
	message_vision(HIM"$N"HIM"向谢烟客走了过去，热情的叫道：谢伯伯~！当接近时，冷不丁用指甲向$n轻轻弹了点粉沫。\n"
			MAG"谢烟客听到这一叫唤，一愣神，心想你是谁啊？我们认识？忽然$n脚步踉跄摇摇欲坠！\n"NOR,me, ob);
         CHANNEL_D->do_channel(ob, "chat", "强提一口真气,破口大骂道：好!"+ me->name(1)+ "你个小贼，居然敢用这下流手段谋害于我，你给我等着~~！\n");  
	       message_vision("\n说罢，谢烟客凭着这强提上来的一口真气，施展绝世轻功一跃而起，向远方逃去。\n", ob);

	destruct(ob);
	return 1;
}

// NPC: /d/huashan/npc/monkey.c
// Date: Look 99/03/25
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("猴子", ({ "hou zi" , "monkey", "hou" }));
	set("long","一个机灵的小猴子。浑身毛皮精光华亮，手中抱着一个坛子，正在叽叽喳喳的叫着。\n");

	set("race", "野兽");
	set("age", 3);
	set("attitude", "friendly");

	set("max_ging", 800);
	set("max_qi", 800);

	set("str", 10);
	set("cor", 50);

	set("limbs", ({ "头部", "身体", "尾巴" }) );
	set("verbs", ({ "bite" }) );
	set("houerjiu",1);
	set_temp("apply/attack", 100);
	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);
	set("combat_exp", 100000);
	setup();
}


int accept_object(object me, object obj)
{
	
	me->start_busy(2);
	if (me->query_temp("quest/hs/houerjiu/askchong")&& obj->query("id")=="shan yeguo")
	{
		//me->set_temp("quest/hs/houerjiu/giveguo",1);
		obj->move(this_object());
		write(HIY"小猴子拿起山野果就啃，高兴滴蹦了起来，似乎对你的好感大增。\n"NOR);
		command("eat guo");
		command("eat guo");
		command("eat guo");
		if (time()-me->query("quest/hs/houerjiu/time")<86400)
		{
			message_vision("小猴儿拿眼白了$n一眼，显然是想起方才已经给$n一坛了。\n",me);
			return 1;
		}
		if (this_object()->query("houerjiu")>0)
			call_out("over",2,me);
		destruct(obj);
		me->delete_temp("quest/huashan/askchong");		
		return 1;
	}

}
int over(object me)
{
	object hou;
	hou=new("d/huashan/npc/obj/houerjiu");
	if (random(10)<3 && me->query("kar")>20)
	{
		message_vision(HIC"$N吃的高兴，见$n又递给自己一个果子，急忙将手中坛子递给了$n。\n"NOR,this_object(),me);
		me->set("quest/hs/houerjiu/time",time());
		this_object()->add("houerjiu",-1);
		hou->move(me);
	}else {
	   message_vision("小猴儿冲$N龇牙咧嘴一笑，甚是高兴。\n",me);
	}
	return 1;

}
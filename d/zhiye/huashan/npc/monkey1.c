// NPC: /d/huashan/npc/monkey.c
// Date: Look 99/03/25
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "hou zi" , "monkey", "hou" }));
	set("long","һ�������С���ӡ�����ëƤ���⻪�������б���һ��̳�ӣ�����ߴߴ�����Ľ��š�\n");

	set("race", "Ұ��");
	set("age", 3);
	set("attitude", "friendly");

	set("max_ging", 800);
	set("max_qi", 800);

	set("str", 10);
	set("cor", 50);

	set("limbs", ({ "ͷ��", "����", "β��" }) );
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
		write(HIY"С��������ɽҰ���ͿУ����˵α����������ƺ�����ĺøд�����\n"NOR);
		command("eat guo");
		command("eat guo");
		command("eat guo");
		if (time()-me->query("quest/hs/houerjiu/time")<86400)
		{
			message_vision("С������۰���$nһ�ۣ���Ȼ�����𷽲��Ѿ���$nһ̳�ˡ�\n",me);
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
		message_vision(HIC"$N�Եĸ��ˣ���$n�ֵݸ��Լ�һ�����ӣ���æ������̳�ӵݸ���$n��\n"NOR,this_object(),me);
		me->set("quest/hs/houerjiu/time",time());
		this_object()->add("houerjiu",-1);
		hou->move(me);
	}else {
	   message_vision("С�����$N��������һЦ�����Ǹ��ˡ�\n",me);
	}
	return 1;

}
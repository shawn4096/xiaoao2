// NPC: /d/meizhuang/npc/shilingwei.c
// By action@SJ 2009/1/11

#include <ansi.h>
inherit NPC;
string ask_quest();
string ask_pomo();
void create()
{
	object key;
	set_name("������", ({ "danqing sheng", "sheng" }));
	set("nickname", GRN"÷ׯ��ׯ��"NOR);

	set("gender", "����");
	set("age", 46);
	set("no_quest", 1);
	set("no_bark", 1);
	set("long",
      "������÷ׯ��λׯ�����е��ĵĵ�������\n"
      "����һ���ɸɾ�������ɫ���ۡ�\n"
      "����������Ѯ�������ݳ���������⡣�񵭳�ͣ���Ĭ���ԡ�\n");

	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 4000);
	set("max_jingli", 4000);
	set("max_neili", 5000);
	set("neili", 8000);
	set("combat_exp", 4500000);
	set("attitude", "peaceful");

	set_skill("hand", 180);
	set_skill("art", 180);
	set_skill("medicine", 180);
	set_skill("literate", 350);
	set_skill("force", 350);
	set_skill("parry", 350);
	set_skill("huanmo-wubu", 350);
	set_skill("sword", 180);
	set_skill("tianmo-gong", 350);
	set_skill("pomopima-jian", 350);

	map_skill("force", "tianmo-gong");
	map_skill("dodge", "huanmo-wubu");
	map_skill("sword", "pomopima-jian");
	map_skill("parry", "pomopima-jian");
	
	set("inquiry", ([
         "����" : (: ask_quest :),
		 "��ī���齣" : (: ask_pomo :),
        ]));
	
	set("chat_chance", 1);
	set("chat_msg", ({
		"����������˵�������˭�ܽ���Ϫɽ����ͼ�����������Ҿ͸�����һ�������ܡ�����\n",
	}));

        if (clonep()){
           key = unew(("d/meizhuang/obj/hongyu-yaoshi"));
           if(!key)key=new(("d/meizhuang/obj/hongyu-yaoshi"));
           key->move(this_object());
           carry_object(ARMOR_D("cloth"))->wear();
           carry_object(BINGQI_D("changjian"))->wield();
     }
	setup();

}  

string ask_quest()
{
	object me=this_player();
  object who=this_object();
  object ob = present("hongyu yaoshi", this_object());
	
	if(me->query("quest/xxdf/pass"))
		return "�㲻���Ѿ��ɹ�ѧ�����Ǵ������㻹Ҫȥ������\n";
		
	if(me->query_temp("quest/xxdf/start"))
		return "�Ҳ��ǽ���ȥ�����Ǳ�ȥ�������𣬻�����ȥ��\n";
		
		if(!me->query_temp("quest/xxdf/startmz"))
		return "����˭�����������ʲô��\n";
		
		if (present("hongyu yaoshi", me))
		return "�ף���ɫԿ�ײ�����������ô��";
		
	me->delete_temp("startmz");
	if (present("hongyu yaoshi",this_object())) {
			ob->set("owner", me);
			ob->move(me);
      me->set_temp("quest/xxdf/start",1);
      call_out("die",60);
      return("��Ѻ���Կ�׸��㣬��ȥ�����Ǳ�ȥ���������ɣ���");
	}
else {
      call_out("die",60);
      message_vision("\nֻ����������һ���׶���������У���\n", me);
       return("�군�ˣ�Կ�ײ����ˣ����϶����������ҵģ��Ҳ�������˵�գ����׶���������У�");
}
}
// ask pomo
string ask_pomo()
{
    object me=this_player();
    if (me->query("family/family_name")!="�������")
       return "�㲻������̵��ӣ�������������������\n";
   if (!me->query_skill("qixian-wuxingjian")) return "�㶼�����������ν���\n";
	if (!me->query_temp("givehua"))
	   return "Ϫɽ����ͼ�漣���Ķ��أ���̫ϲ��������ˡ�\n";
	
	command("laugh "+me->query("id"));
	command("say �����ڴ����������һ���������н������������ڣ���������ƽ�����֮��������֮����Ҳ�治�����ˡ�\n");
	command("say �Ƿ�����������Ȥ�͵������Ĵ�������˵������Ҳ�ܿ�������\n");
	command("sing ");
	me->set_temp("qxwxj/pomoask",1);
	return "����ܺȵ�ƣ�Ч�����á�\n";

}


int accept_object(object who, object ob)
{
        object me;
        me = this_object();
		
        //mapping fam;
        if (!who->query("family") || who->query("family/family_name") !="�������"){
             command("thank "+ (string)who->query("id"));
             command("say ���뱾��������������֪Ϊ������˺���\n");
             return 0;
        }
     /*   if (!this_player()->query_temp("meizhuangshuaiyitie")){
             command("say �㻹����ȥ��������ͺ����ȥ���ʰɣ�");
             return 0;
        }*/
        
        if ((string)ob->query("id") == "xinglv tu" && this_player()->query_temp("meizhuangshuaiyitie")){
            command("haha "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            command("say ����Ұ��������£��Һܸ��ˣ����Ҿ͸�����һ�����ܰɣ�\n");
            who->set_temp("quest/xxdf/startmz",1);
			
            who->delete_temp("meizhuangshuaiyitie");
            return 1;
        }
		else if ((string)ob->query("id") == "xinglv tu")
		{
			command("say �⣬�����⾹Ȼ�Ǵ�˵�е�Ϫɽ����ͼ��\n");
			command("say �������ôһ�ݴ���������Ϊ��,�Ͱ�����ô���������Ľ�������������ɡ�\n");
            who->set_temp("givehua",1);
			destruct(ob);
			return 1;

		}
        command("? "+ (string)who->query("id"));
        return 0;
}

void unconcious()
 {
         remove_all_killer();
         remove_all_enemy();
         say("������һ���ߺ���ɱ������Ͳ�Ҫ���ٵõ��������ˣ���\n");
        reincarnate();
         set("eff_qi", query("max_qi"));
         set("qi", query("max_qi"));
         set("eff_jing", query("max_jing"));
         set("jing", query("max_jing"));
         set("jingli", query("eff_jingli"));
         clear_conditions_by_type("poison");
}

 void die()
{
::die();
}
// NPC: /d/meizhuang/npc/huangzhonggong.c
// By action@SJ 2009/1/11

#include <ansi.h>
inherit NPC;
string ask_xingluo();
void create()
{
	set_name("�ڰ���", ({ "heibai zi", "zi" }));
	set("nickname", HIW"÷ׯ��ׯ��"NOR);

	set("gender", "����");
	set("age", 54);
	//set("no_quest", 1);
	set("no_bark", 1);
	set("long",
      "������÷ׯ��λׯ�����еڶ��ĺڰ��ӡ�\n"
      "��һ���ɸɾ����ĺڰ����ĳ��ۡ�\n"
      "����������Ѯ����ĸߴ�˫���������, һ����֪��һλ�ڼҵĸ��֡�\n");
	set("qi", 34000);
	set("max_qi", 34000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 4000);
	set("max_jingli", 4000);
	set("max_neili", 15000);
	set("neili", 15000);
	set("combat_exp", 9200000);
	set("attitude", "peaceful");
	//set_skill("xuantian-zhi", 180);
	set_skill("art", 180);
	set_skill("medicine", 180);
	set_skill("literate", 180);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("huanmo-wubu", 450);
	set_skill("finger", 450);
	set_skill("tianmo-gong", 450);
	set_skill("throwing", 450);
	set_skill("mantian-huayu", 450);
	set_skill("hand", 450);
	set_skill("tianmo-shou", 450);

	map_skill("force", "tianmo-gong");
	map_skill("dodge", "huanmo-wubu");
	map_skill("hand", "tianmo-shou");
	map_skill("throwing", "mantian-huayu");
	map_skill("parry", "mantian-huayu");
	prepare_skill("hand", "tianmo-shou");

	set_temp("apply/damage", 40);
	set("chat_chance", 1);
	set("chat_msg", ({
		"�ڰ����૵�����ŻѪ�ס��������µ�һ���ף�������ܡ�����\n",
	}));
	set("inquiry", ([
                 "�����岼����" : (: ask_xingluo :),
		        // "�������" : (: ask_huayu :),
        ]));
	setup();
	carry_object(ARMOR_D("cloth"))->wear();
	carry_object(BINGQI_D("weiqizi"))->wield();
}      

int accept_object(object who, object ob)
{
        object me;
        mapping fam;
        me = this_object();
     
	 if (!(fam = this_player()->query("family")) || fam["family_name"] !="�������"){
             command("thank "+ (string)who->query("id"));
             command("say ���뱾��������������֪Ϊ������˺���");
             return 0;
        }
     
       /*
        if (!this_player()->query_temp("meizhuangguangling")){
             command("say �㻹����ȥ���Ҵ����ӹ�ȥ���ʰɣ�");
             return 0;
        } */ 
        
        //if (fam["generation"] == 3)
        if ((string)ob->query("id") == "ouxue pu"&& this_player()->query_temp("meizhuangguangling")){
            command("haha "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            command("say ����Ұ��������£��Һܸ��ˣ���ȥ���ҵ�����ͺ�������԰ɣ��������ܸ���һЩ��ʾ��");
            who->set_temp("meizhuangouxuepu",1);
			
            who->delete_temp("meizhuangguangling");
			command("say ������Ȼ�������ҵ�������ף��ҾͰ���������͸����ˡ�\n");
			new("clone/weapon/weiqizi")->move(who);
            return 1;
            }
		else if ((string)ob->query("id") == "ouxue pu")
		{
			command("say �⣬�����⾹Ȼ�Ǵ�˵�е�ŻѪ�ף�\n");
			command("say �������ôһ�ݴ���������Ϊ��,�Ͱ�����ô���������������岼����������ɡ�\n");
            who->set_temp("qipugived",1);
			destruct(ob);
			return 1;
		}
        command("? "+ (string)who->query("id"));
        return 0;
}

void destroying(object obj)
{
        if(! obj) return;
        destruct(obj);
}

string ask_xingluo()
{
     int i,j;
	 object me=this_player();
	
	if (!me->query_temp("qipugived"))
	    return "������ô�����ģ���������ʲô��ϵ����Ϊ��Ҫ�����㣿\n"+"�ҵ�ŻѪ�װ�,�������Ķ��أ�\n";
     if (me->query("family/family_name")!="�������")
		return "�㲢������̵ĵ��ӣ��������������\n";
	
     if (time()-me->query("quest/hmy/mthy/xingluo/time")<86400)
		return "������Ҳ̫�ڿ��ˡ�\n";

	 if (me->query_skill("mantian-huayu",1)<350
		// ||me->query_skill("hand",1)<350
		// ||me->query_skill("tianmo-shou",1)<350
		 ||me->query_skill("throwing",1)<350)
	    return "������컨�������似����350���޷�������˵��������ϣ���ȥ����Ŭ����\n";
		
	 if (me->query("quest/hmy/mthy/xingluo/pass"))
		return "���Ѿ��⿪������⣬���˷�ɶʱ�䣿\n";
	 command("say ���֡������岼�������ַ��������Ҷ�����ĵã�����ʹ�õĺá�һ�е��˶�����������֮�¡�\n");
	 command("say ��������ҵ�Χ���ӣ���������һ��¥��\n");
	 command("whisper "+me->query("id")+" �������ӵģ��������ˡ���������\n");
	 j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	 if (i<5&&me->query("kar")>22) {
		
        command("chat* laugh "+me->query("id"));
        command("say ������������������ӣ��Ҵ��������������һ���������֡�\n");
		command("chat* congra "+me->query("id"));
	
		log_file("quest/xingluoqibu",sprintf("%s(%s) �ܺڰ��ӵ�ָ�㣬�ɹ����������岼��������Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/xingluo/fail"),me->query("combat_exp"),me));
	   
	    me->set("quest/hmy/mthy/xingluo/pass",1);	  	   
		return "��ϲ��⿪���컨��֮�������岼�����ܣ�\n";
      }
	  else {
       
		log_file("quest/xingluoqibu",sprintf("%s(%s) ���������岼����ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),me->query("kar"),me->query("quest/hmy/mthy/xingluo/fail"),me->query("combat_exp"),me));
	   
	    me->add("quest/hmy/mthy/xingluo/fail",1);
		me->set("quest/hmy/mthy/xingluo/time",time());
		return "�������컨��֮�������岼������ʧ��!\n";

	  }

}


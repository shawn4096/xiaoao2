// NPC: /d/meizhuang/npc/huang.c
// By action@SJ 2009/1/11

#include <ansi.h>
inherit NPC;
string ask_wuxian();
void create()
{
	object ob;

	set_name("���ӹ�", ({ "huangzhong gong", "huang", "gong" }));
	set("nickname", HIR"÷ׯ��ׯ��"NOR);

	set("gender", "����");
	set("age", 65);
	set("no_quest", 1);
	set("no_bark", 1);
	set("long",
      "������÷ׯ��λׯ�����е�һ�Ļ��ӹ���\n"
      "��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
      "����������Ѯ������еȣ����ݺͰ����ס�\n");
	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 4000);
	set("max_jing", 4000);
	set("jingli", 4000);
	set("max_jingli", 4000);
	set("max_neili", 5000);
	set("neili", 8000);
	set("combat_exp", 3200000);
	set("attitude", "peaceful");

	set_skill("art", 180);
	set_skill("medicine", 120);
	set_skill("literate", 160);
	set_skill("force", 450);
	set_skill("parry", 450);
	set_skill("huanmo-wubu", 450);
	set_skill("sword", 450);
	set_skill("tianmo-gong", 450);
	set_skill("qixian-wuxingjian", 450);
	set_skill("strike", 450);
	set_skill("tianmo-zhang", 450);

	map_skill("force", "tianmo-gong");
	map_skill("dodge", "huanmo-wubu");
	map_skill("sword", "qixian-wuxingjian");
	map_skill("parry", "qixian-wuxingjian");
	map_skill("strike", "tianmo-zhang");
	set("inquiry", ([
         
		 "��������" : (: ask_wuxian :),
        ]));
	set("chat_chance", 1);
	set("chat_msg", ({
		"���ӹ�̾�˿�������˭�ܽ�������ɢ��Ū������ѽ������\n",
	}));

	set_temp("apply/damage", 260);

	setup();
        if (clonep()) {
                ob = unew(BINGQI_D("sword/yaoqin"));
                if (!ob) ob = unew(BINGQI_D("yuxiao2"));
                ob->move(this_object());
                ob->wield();
                carry_object(ARMOR_D("cloth"))->wear();
        }
}

int accept_object(object who, object ob)
{
        object me;
       // mapping fam;
        me = this_object();

       if (!who->query("family") || who->query("family/family_name") !="�������"){
             command("thank "+ (string)who->query("id"));
             command("say ���뱾��������������֪Ϊ������˺���\n");
             return 0;
        }
       /* 
		if (!this_player()->query_temp("mz_entrance")){
             command("say ������ô�����ģ�");
             return 0;
        }*/
        
       // if (fam["generation"] == 3)
        if ((string)ob->query("id") == "guangling san"&& who->query_temp("mz_entrance")){
            command("haha "+(string)who->query("id"));
            call_out("destroying", 1, ob);
            command("say ����Ұ��������£��Һܸ��ˣ���ȥ���ҵĶ��ܺڰ������԰ɣ��������ܸ���һЩ��ʾ��");
            who->set_temp("meizhuangguangling",1);
			
            who->delete_temp("mz_entrance");
            return 1;
            }
         else if ((string)ob->query("id") == "guangling san")
         {
			 command("������˴�����ң����Ǻ��գ�������Ϊ����ֻ�ܽ��Ҷ�����ĵô��ڸ��㡣\n");
			 who->set_temp("glsgived",1);
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

string ask_wuxian()
{
    int i,j;
	object me=this_player();
    if (me->query("family/family_name")!="�������")
       return "�㲻������̵��ӣ������������������\n";
	if (!me->query_temp("glsgived"))
	   return "����ɢ�˾��������������������������ղ�����\n";
	if (!me->query_skill("qixian-wuxingjian")) return "�㶼�����������ν���\n";
	
	if (me->query("quest/hmy/qxwxj/wuxian/pass"))
	   return "���Ѿ������˽��������ν�����������\n";
    if (time()-me->query("quest/hmy/qxwxj/wuxian/time")<86400)
       return "������Ҳ̫�ڿ���ˣ�\n";
    
	command("smile "+me->query("id"));
	command("say ��Ȼ�����Ǳ����������������ܶ��������������ܷ���ܵ��ˣ���Ҫ�����������ˡ�\n");
	command("say ��ν������������ָ�������̡��ǡ��硢������������󣬿��Խ���������������\n");
	command("say ���Ź���������ν���ר�������������������ޱȡ�\n ");
	
	j=20;
	if(me->query("m-card-vip")) j =  18;
	if(me->query("y-card-vip")) j =  15;
	if(me->query("buyvip"))     j =  10;
	  i=random(j);
	if (me->query("kar")<31
		&& random(me->query("kar"))>=22
		&& me->query("int")>=25
		&& i<6)
	    {
          message_vision(HIY"$N���Ż��ӹ��Ľ��⣬�������ְ�������ɽ��һ��������һ������\n"+
						"��Ȼ�䣬����ӿ����˲����ͨ����Ѩλ������ͨ�����Ҷ�Ȼ������\n"NOR,me);
	      message_vision(HIC"$N��ϲ�㣬��������ӹ������ν����������˵ľ�����\n"NOR,me);
	  
	   log_file("quest/qxwxjwuxian",sprintf("%s(%s) �ӻ��ӹ����������������������ɣ������˵еľ�������Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/wuxian/fail"),me->query("combat_exp"),me));
	   
	   me->set("quest/hmy/qxwxj/wuxian/pass",1);
	   me->improve_skill("qixian-wuxingjian",20);
       message_vision(HIC"����������ν������ˣ�\n"NOR,me);
	   me->delete_temp("glsgived");
	   me->start_busy(1);
	   return "";
	  }
	   else {
		message_vision(HIY"\n �����˵�������Ҫ���ߵ����������ԣ���������ʧ�ܣ��´�������\n"NOR,me);
	    log_file("quest/qxwxjwuxian",sprintf("%s(%s) �����������ν����������ľ���ʧ�ܡ���Դ��%d��ʧ�ܣ�%d������ֵ��%d��\n",
			me->name(1), me->query("id"),j,me->query("quest/hmy/qxwxj/wuxian/fail"),me->query("combat_exp"),me));
		me->add("quest/hmy/qxwxj/wuxian/fail",1);
		me->set("quest/hmy/qxwxj/wuxian/time",time());
		me->delete_temp("glsgived");
		me->start_busy(1);
        return "";
	   }
	// return "���Ҽ��Ƿ�����,�����뷢��Ⱥ�����֡�\n";
}
